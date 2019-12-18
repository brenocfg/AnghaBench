#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpiod_data {int /*<<< orphan*/  value_kn; int /*<<< orphan*/  irq; scalar_t__ irq_flags; struct gpio_desc* desc; } ;
struct gpio_desc {TYPE_1__* gdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 struct gpiod_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct gpiod_data*) ; 
 int /*<<< orphan*/  gpio_chip_hwgpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpiochip_unlock_as_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_sysfs_free_irq(struct device *dev)
{
	struct gpiod_data *data = dev_get_drvdata(dev);
	struct gpio_desc *desc = data->desc;

	data->irq_flags = 0;
	free_irq(data->irq, data);
	gpiochip_unlock_as_irq(desc->gdev->chip, gpio_chip_hwgpio(desc));
	sysfs_put(data->value_kn);
}