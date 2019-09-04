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
struct gpio_desc {int dummy; } ;
struct dmi_system_id {int /*<<< orphan*/  ident; } ;
struct bcm_device {scalar_t__ clk; scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  set_shutdown; int /*<<< orphan*/  set_device_wakeup; struct gpio_desc* shutdown; struct gpio_desc* device_wakeup; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  bcm_apple_get_resources (struct bcm_device*) ; 
 int /*<<< orphan*/  bcm_broken_irq_dmi_table ; 
 int /*<<< orphan*/  bcm_gpio_set_device_wakeup ; 
 int /*<<< orphan*/  bcm_gpio_set_shutdown ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct dmi_system_id* dmi_first_match (int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_to_irq (struct gpio_desc*) ; 
 scalar_t__ x86_apple_machine ; 

__attribute__((used)) static int bcm_get_resources(struct bcm_device *dev)
{
	const struct dmi_system_id *dmi_id;

	dev->name = dev_name(dev->dev);

	if (x86_apple_machine && !bcm_apple_get_resources(dev))
		return 0;

	dev->clk = devm_clk_get(dev->dev, NULL);

	/* Handle deferred probing */
	if (dev->clk == ERR_PTR(-EPROBE_DEFER))
		return PTR_ERR(dev->clk);

	dev->device_wakeup = devm_gpiod_get_optional(dev->dev, "device-wakeup",
						     GPIOD_OUT_LOW);
	if (IS_ERR(dev->device_wakeup))
		return PTR_ERR(dev->device_wakeup);

	dev->shutdown = devm_gpiod_get_optional(dev->dev, "shutdown",
						GPIOD_OUT_LOW);
	if (IS_ERR(dev->shutdown))
		return PTR_ERR(dev->shutdown);

	dev->set_device_wakeup = bcm_gpio_set_device_wakeup;
	dev->set_shutdown = bcm_gpio_set_shutdown;

	/* IRQ can be declared in ACPI table as Interrupt or GpioInt */
	if (dev->irq <= 0) {
		struct gpio_desc *gpio;

		gpio = devm_gpiod_get_optional(dev->dev, "host-wakeup",
					       GPIOD_IN);
		if (IS_ERR(gpio))
			return PTR_ERR(gpio);

		dev->irq = gpiod_to_irq(gpio);
	}

	dmi_id = dmi_first_match(bcm_broken_irq_dmi_table);
	if (dmi_id) {
		dev_info(dev->dev, "%s: Has a broken IRQ config, disabling IRQ support / runtime-pm\n",
			 dmi_id->ident);
		dev->irq = 0;
	}

	dev_dbg(dev->dev, "BCM irq: %d\n", dev->irq);
	return 0;
}