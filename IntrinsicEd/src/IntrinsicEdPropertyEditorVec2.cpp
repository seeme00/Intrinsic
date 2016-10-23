// Intrinsic
// Copyright (c) 2016 Benjamin Glatzel
//
// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// Precompiled header file
#include "stdafx.h"
#include "stdafx_editor.h"

// Ui
#include "ui_IntrinsicEdPropertyEditorVec2.h"

IntrinsicEdPropertyEditorVec2::IntrinsicEdPropertyEditorVec2(
    rapidjson::Document* p_Document, rapidjson::Value* p_CurrentProperties,
    rapidjson::Value* p_CurrentProperty, const char* p_PropertyName,
    QWidget* parent)
    : QWidget(parent), _properties(p_CurrentProperties),
      _property(p_CurrentProperty), _propertyName(p_PropertyName),
      _document(p_Document)
{
  _ui.setupUi(this);
  updateFromProperty();

  QObject::connect(_ui.x, SIGNAL(valueChanged(double)), this,
                   SLOT(onValueChanged()));
  QObject::connect(_ui.y, SIGNAL(valueChanged(double)), this,
                   SLOT(onValueChanged()));
}

IntrinsicEdPropertyEditorVec2::~IntrinsicEdPropertyEditorVec2() {}

void IntrinsicEdPropertyEditorVec2::updateFromProperty()
{
  _INTR_ASSERT(_property);
  const rapidjson::Value& prop = *_property;

  if (prop["readOnly"].GetBool())
  {
    _ui.x->setReadOnly(true);
    _ui.y->setReadOnly(true);
  }

  _ui.x->setValue(prop["valueX"].GetFloat());
  _ui.y->setValue(prop["valueY"].GetFloat());

  _ui.propertyTitle->setText(_propertyName.c_str());
}

void IntrinsicEdPropertyEditorVec2::onValueChanged()
{
  _INTR_ASSERT(_property);
  rapidjson::Value& prop = *_property;

  prop["valueX"].SetFloat((float)_ui.x->value());
  prop["valueY"].SetFloat((float)_ui.y->value());

  emit valueChanged(*_properties);
}