#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_3__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ string; TYPE_1__ package; } ;
struct atk_data {int disable_ec; scalar_t__ old_interface; int /*<<< orphan*/  atk_handle; int /*<<< orphan*/  sensor_list; struct acpi_device* acpi_dev; } ;
struct acpi_device {struct atk_data* driver_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/  length; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  BOARD_ID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_evaluate_object_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atk_debugfs_init (struct atk_data*) ; 
 int /*<<< orphan*/  atk_ec_ctl (struct atk_data*,int /*<<< orphan*/ ) ; 
 int atk_enumerate_new_hwmon (struct atk_data*) ; 
 int atk_enumerate_old_hwmon (struct atk_data*) ; 
 int atk_init_attribute_groups (struct atk_data*) ; 
 int atk_probe_if (struct atk_data*) ; 
 int atk_register_hwmon (struct atk_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct atk_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atk_add(struct acpi_device *device)
{
	acpi_status ret;
	int err;
	struct acpi_buffer buf;
	union acpi_object *obj;
	struct atk_data *data;

	dev_dbg(&device->dev, "adding...\n");

	data = devm_kzalloc(&device->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->acpi_dev = device;
	data->atk_handle = device->handle;
	INIT_LIST_HEAD(&data->sensor_list);
	data->disable_ec = false;

	buf.length = ACPI_ALLOCATE_BUFFER;
	ret = acpi_evaluate_object_typed(data->atk_handle, BOARD_ID, NULL,
			&buf, ACPI_TYPE_PACKAGE);
	if (ret != AE_OK) {
		dev_dbg(&device->dev, "atk: method MBIF not found\n");
	} else {
		obj = buf.pointer;
		if (obj->package.count >= 2) {
			union acpi_object *id = &obj->package.elements[1];
			if (id->type == ACPI_TYPE_STRING)
				dev_dbg(&device->dev, "board ID = %s\n",
					id->string.pointer);
		}
		ACPI_FREE(buf.pointer);
	}

	err = atk_probe_if(data);
	if (err) {
		dev_err(&device->dev, "No usable hwmon interface detected\n");
		goto out;
	}

	if (data->old_interface) {
		dev_dbg(&device->dev, "Using old hwmon interface\n");
		err = atk_enumerate_old_hwmon(data);
	} else {
		dev_dbg(&device->dev, "Using new hwmon interface\n");
		err = atk_enumerate_new_hwmon(data);
	}
	if (err < 0)
		goto out;
	if (err == 0) {
		dev_info(&device->dev,
			 "No usable sensor detected, bailing out\n");
		err = -ENODEV;
		goto out;
	}

	err = atk_init_attribute_groups(data);
	if (err)
		goto out;
	err = atk_register_hwmon(data);
	if (err)
		goto out;

	atk_debugfs_init(data);

	device->driver_data = data;
	return 0;
out:
	if (data->disable_ec)
		atk_ec_ctl(data, 0);
	return err;
}