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
struct device {int dummy; } ;
struct acpi_gpio_mapping {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int acpi_dev_add_driver_gpios (int /*<<< orphan*/ ,struct acpi_gpio_mapping const*) ; 
 int /*<<< orphan*/  devm_acpi_dev_release_driver_gpios ; 
 int /*<<< orphan*/  devres_add (struct device*,void*) ; 
 void* devres_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (void*) ; 

int devm_acpi_dev_add_driver_gpios(struct device *dev,
				   const struct acpi_gpio_mapping *gpios)
{
	void *res;
	int ret;

	res = devres_alloc(devm_acpi_dev_release_driver_gpios, 0, GFP_KERNEL);
	if (!res)
		return -ENOMEM;

	ret = acpi_dev_add_driver_gpios(ACPI_COMPANION(dev), gpios);
	if (ret) {
		devres_free(res);
		return ret;
	}
	devres_add(dev, res);
	return 0;
}