#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct hid_sensor_hub_device {struct hid_device* hdev; } ;
struct hid_sensor_custom {int sensor_field_count; TYPE_4__* fields; TYPE_4__* report_state; TYPE_4__* power_state; TYPE_2__* pdev; struct hid_sensor_hub_device* hsdev; } ;
struct hid_device {int /*<<< orphan*/ * report_enum; } ;
struct TYPE_13__ {char* name; int mode; } ;
struct device_attribute {TYPE_6__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct TYPE_14__ {char* name; int mode; } ;
struct TYPE_12__ {char* name; TYPE_6__** attrs; } ;
struct TYPE_10__ {scalar_t__ attrib_id; } ;
struct TYPE_11__ {char* group_name; TYPE_3__ attribute; TYPE_5__ hid_custom_attribute_group; TYPE_6__** attrs; int /*<<< orphan*/ * attr_name; struct device_attribute* sd_attrs; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CUSTOM_NAME_LENGTH ; 
 int HID_CUSTOM_TOTAL_ATTRS ; 
 int HID_OUTPUT_REPORT ; 
 int HID_REPORT_TYPES ; 
 scalar_t__ HID_USAGE_SENSOR_PROP_REPORT_STATE ; 
 scalar_t__ HID_USAGE_SENSOR_PROY_POWER_STATE ; 
 int S_IWUSR ; 
 TYPE_7__* hid_custom_attrs ; 
 int hid_sensor_custom_add_fields (struct hid_sensor_custom*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  show_value ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  store_value ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_6__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static int hid_sensor_custom_add_attributes(struct hid_sensor_custom
								*sensor_inst)
{
	struct hid_sensor_hub_device *hsdev = sensor_inst->hsdev;
	struct hid_device *hdev = hsdev->hdev;
	int ret = -1;
	int i, j;

	for (j = 0; j < HID_REPORT_TYPES; ++j) {
		if (j == HID_OUTPUT_REPORT)
			continue;

		ret = hid_sensor_custom_add_fields(sensor_inst,
						   &hdev->report_enum[j], j);
		if (ret)
			return ret;

	}

	/* Create sysfs attributes */
	for (i = 0; i < sensor_inst->sensor_field_count; ++i) {
		j = 0;
		while (j < HID_CUSTOM_TOTAL_ATTRS &&
		       hid_custom_attrs[j].name) {
			struct device_attribute *device_attr;

			device_attr = &sensor_inst->fields[i].sd_attrs[j];

			snprintf((char *)&sensor_inst->fields[i].attr_name[j],
				 HID_CUSTOM_NAME_LENGTH, "%s-%s",
				 sensor_inst->fields[i].group_name,
				 hid_custom_attrs[j].name);
			sysfs_attr_init(&device_attr->attr);
			device_attr->attr.name =
				(char *)&sensor_inst->fields[i].attr_name[j];
			device_attr->attr.mode = hid_custom_attrs[j].mode;
			device_attr->show = show_value;
			if (hid_custom_attrs[j].mode & S_IWUSR)
				device_attr->store = store_value;
			sensor_inst->fields[i].attrs[j] = &device_attr->attr;
			++j;
		}
		sensor_inst->fields[i].attrs[j] = NULL;
		sensor_inst->fields[i].hid_custom_attribute_group.attrs =
						sensor_inst->fields[i].attrs;
		sensor_inst->fields[i].hid_custom_attribute_group.name =
					sensor_inst->fields[i].group_name;
		ret = sysfs_create_group(&sensor_inst->pdev->dev.kobj,
					 &sensor_inst->fields[i].
					 hid_custom_attribute_group);
		if (ret)
			break;

		/* For power or report field store indexes */
		if (sensor_inst->fields[i].attribute.attrib_id ==
					HID_USAGE_SENSOR_PROY_POWER_STATE)
			sensor_inst->power_state = &sensor_inst->fields[i];
		else if (sensor_inst->fields[i].attribute.attrib_id ==
					HID_USAGE_SENSOR_PROP_REPORT_STATE)
			sensor_inst->report_state = &sensor_inst->fields[i];
	}

	return ret;
}