#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sensor_template {scalar_t__ set; int /*<<< orphan*/  index; int /*<<< orphan*/  show; int /*<<< orphan*/ * label; } ;
struct TYPE_5__ {int mode; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {TYPE_2__ attr; scalar_t__ store; int /*<<< orphan*/  show; } ;
struct sensor_device_attribute {TYPE_3__ dev_attr; int /*<<< orphan*/  index; } ;
struct device {int dummy; } ;
struct acpi_power_meter_resource {size_t num_sensors; struct sensor_device_attribute* sensors; TYPE_1__* acpi_dev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int device_create_file (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static int register_attrs(struct acpi_power_meter_resource *resource,
			  struct sensor_template *attrs)
{
	struct device *dev = &resource->acpi_dev->dev;
	struct sensor_device_attribute *sensors =
		&resource->sensors[resource->num_sensors];
	int res = 0;

	while (attrs->label) {
		sensors->dev_attr.attr.name = attrs->label;
		sensors->dev_attr.attr.mode = 0444;
		sensors->dev_attr.show = attrs->show;
		sensors->index = attrs->index;

		if (attrs->set) {
			sensors->dev_attr.attr.mode |= 0200;
			sensors->dev_attr.store = attrs->set;
		}

		sysfs_attr_init(&sensors->dev_attr.attr);
		res = device_create_file(dev, &sensors->dev_attr);
		if (res) {
			sensors->dev_attr.attr.name = NULL;
			goto error;
		}
		sensors++;
		resource->num_sensors++;
		attrs++;
	}

error:
	return res;
}