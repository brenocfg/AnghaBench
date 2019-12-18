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
struct list_head {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ENOENT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  acpi_dev_free_resource_list (struct list_head*) ; 
 int acpi_dev_get_resources (struct acpi_device*,struct list_head*,int /*<<< orphan*/ ,int*) ; 
 int acpi_dev_gpio_irq_get (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_acpi_add_resource ; 

int i2c_acpi_get_irq(struct i2c_client *client)
{
	struct acpi_device *adev = ACPI_COMPANION(&client->dev);
	struct list_head resource_list;
	int irq = -ENOENT;
	int ret;

	INIT_LIST_HEAD(&resource_list);

	ret = acpi_dev_get_resources(adev, &resource_list,
				     i2c_acpi_add_resource, &irq);
	if (ret < 0)
		return ret;

	acpi_dev_free_resource_list(&resource_list);

	if (irq == -ENOENT)
		irq = acpi_dev_gpio_irq_get(adev, 0);

	return irq;
}