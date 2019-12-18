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
struct secocec_data {int irq; struct device* dev; } ;
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct gpio_desc* devm_gpiod_get (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gpiod_to_irq (struct gpio_desc*) ; 

__attribute__((used)) static int secocec_acpi_probe(struct secocec_data *sdev)
{
	struct device *dev = sdev->dev;
	struct gpio_desc *gpio;
	int irq = 0;

	gpio = devm_gpiod_get(dev, NULL, GPIOF_IN);
	if (IS_ERR(gpio)) {
		dev_err(dev, "Cannot request interrupt gpio");
		return PTR_ERR(gpio);
	}

	irq = gpiod_to_irq(gpio);
	if (irq < 0) {
		dev_err(dev, "Cannot find valid irq");
		return -ENODEV;
	}
	dev_dbg(dev, "irq-gpio is bound to IRQ %d", irq);

	sdev->irq = irq;

	return 0;
}