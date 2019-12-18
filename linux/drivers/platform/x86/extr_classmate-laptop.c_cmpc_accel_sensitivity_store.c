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
struct input_dev {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cmpc_accel {unsigned long sensitivity; } ;
struct acpi_device {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cmpc_accel_set_sensitivity (int /*<<< orphan*/ ,unsigned long) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int strnlen (char const*,size_t) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t cmpc_accel_sensitivity_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct acpi_device *acpi;
	struct input_dev *inputdev;
	struct cmpc_accel *accel;
	unsigned long sensitivity;
	int r;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	r = kstrtoul(buf, 0, &sensitivity);
	if (r)
		return r;

	accel->sensitivity = sensitivity;
	cmpc_accel_set_sensitivity(acpi->handle, sensitivity);

	return strnlen(buf, count);
}