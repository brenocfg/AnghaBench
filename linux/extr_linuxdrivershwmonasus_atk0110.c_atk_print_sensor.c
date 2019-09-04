#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  union acpi_object {int dummy; } acpi_object ;
struct atk_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void atk_print_sensor(struct atk_data *data, union acpi_object *obj)
{
#ifdef DEBUG
	struct device *dev = &data->acpi_dev->dev;
	union acpi_object *flags;
	union acpi_object *name;
	union acpi_object *limit1;
	union acpi_object *limit2;
	union acpi_object *enable;
	char const *what;

	flags = atk_get_pack_member(data, obj, HWMON_PACK_FLAGS);
	name = atk_get_pack_member(data, obj, HWMON_PACK_NAME);
	limit1 = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT1);
	limit2 = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT2);
	enable = atk_get_pack_member(data, obj, HWMON_PACK_ENABLE);

	what = atk_sensor_type(flags);

	dev_dbg(dev, "%s: %#llx %s [%llu-%llu] %s\n", what,
			flags->integer.value,
			name->string.pointer,
			limit1->integer.value, limit2->integer.value,
			enable->integer.value ? "enabled" : "disabled");
#endif
}