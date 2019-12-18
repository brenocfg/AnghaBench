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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device_by_acpi_dev (int /*<<< orphan*/ *,struct acpi_device*) ; 
 int /*<<< orphan*/  i2c_bus_type ; 
 struct i2c_client* i2c_verify_client (struct device*) ; 

__attribute__((used)) static struct i2c_client *i2c_acpi_find_client_by_adev(struct acpi_device *adev)
{
	struct device *dev;

	dev = bus_find_device_by_acpi_dev(&i2c_bus_type, adev);
	return dev ? i2c_verify_client(dev) : NULL;
}