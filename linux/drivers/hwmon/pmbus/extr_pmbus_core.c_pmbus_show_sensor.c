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
struct pmbus_sensor {scalar_t__ data; } ;
struct pmbus_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  pmbus_reg2data (struct pmbus_data*,struct pmbus_sensor*) ; 
 struct pmbus_data* pmbus_update_device (struct device*) ; 
 scalar_t__ snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct pmbus_sensor* to_pmbus_sensor (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pmbus_show_sensor(struct device *dev,
				 struct device_attribute *devattr, char *buf)
{
	struct pmbus_data *data = pmbus_update_device(dev);
	struct pmbus_sensor *sensor = to_pmbus_sensor(devattr);

	if (sensor->data < 0)
		return sensor->data;

	return snprintf(buf, PAGE_SIZE, "%ld\n", pmbus_reg2data(data, sensor));
}