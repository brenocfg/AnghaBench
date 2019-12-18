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
struct TYPE_4__ {int const count; union acpi_object* elements; } ;
union acpi_object {int /*<<< orphan*/  type; TYPE_2__ package; } ;
struct device {int dummy; } ;
struct atk_data {int old_interface; TYPE_1__* acpi_dev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int EINVAL ; 
 int /*<<< orphan*/  HWMON_PACK_ENABLE ; 
 int /*<<< orphan*/  HWMON_PACK_FLAGS ; 
 int /*<<< orphan*/  HWMON_PACK_LIMIT1 ; 
 int /*<<< orphan*/  HWMON_PACK_LIMIT2 ; 
 int /*<<< orphan*/  HWMON_PACK_NAME ; 
 size_t HWMON_PACK_UNK1 ; 
 size_t HWMON_PACK_UNK2 ; 
 int _HWMON_NEW_PACK_SIZE ; 
 int _HWMON_OLD_PACK_SIZE ; 
 union acpi_object* atk_get_pack_member (struct atk_data*,union acpi_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atk_print_sensor (struct atk_data*,union acpi_object*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int const,...) ; 

__attribute__((used)) static int validate_hwmon_pack(struct atk_data *data, union acpi_object *obj)
{
	struct device *dev = &data->acpi_dev->dev;
	union acpi_object *tmp;
	bool old_if = data->old_interface;
	int const expected_size = old_if ? _HWMON_OLD_PACK_SIZE :
					   _HWMON_NEW_PACK_SIZE;

	if (obj->type != ACPI_TYPE_PACKAGE) {
		dev_warn(dev, "Invalid type: %d\n", obj->type);
		return -EINVAL;
	}

	if (obj->package.count != expected_size) {
		dev_warn(dev, "Invalid package size: %d, expected: %d\n",
				obj->package.count, expected_size);
		return -EINVAL;
	}

	tmp = atk_get_pack_member(data, obj, HWMON_PACK_FLAGS);
	if (tmp->type != ACPI_TYPE_INTEGER) {
		dev_warn(dev, "Invalid type (flag): %d\n", tmp->type);
		return -EINVAL;
	}

	tmp = atk_get_pack_member(data, obj, HWMON_PACK_NAME);
	if (tmp->type != ACPI_TYPE_STRING) {
		dev_warn(dev, "Invalid type (name): %d\n", tmp->type);
		return -EINVAL;
	}

	/* Don't check... we don't know what they're useful for anyway */
#if 0
	tmp = &obj->package.elements[HWMON_PACK_UNK1];
	if (tmp->type != ACPI_TYPE_INTEGER) {
		dev_warn(dev, "Invalid type (unk1): %d\n", tmp->type);
		return -EINVAL;
	}

	tmp = &obj->package.elements[HWMON_PACK_UNK2];
	if (tmp->type != ACPI_TYPE_INTEGER) {
		dev_warn(dev, "Invalid type (unk2): %d\n", tmp->type);
		return -EINVAL;
	}
#endif

	tmp = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT1);
	if (tmp->type != ACPI_TYPE_INTEGER) {
		dev_warn(dev, "Invalid type (limit1): %d\n", tmp->type);
		return -EINVAL;
	}

	tmp = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT2);
	if (tmp->type != ACPI_TYPE_INTEGER) {
		dev_warn(dev, "Invalid type (limit2): %d\n", tmp->type);
		return -EINVAL;
	}

	tmp = atk_get_pack_member(data, obj, HWMON_PACK_ENABLE);
	if (tmp->type != ACPI_TYPE_INTEGER) {
		dev_warn(dev, "Invalid type (enable): %d\n", tmp->type);
		return -EINVAL;
	}

	atk_print_sensor(data, obj);

	return 0;
}