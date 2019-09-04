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
struct gpio_device {unsigned int ngpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  chrdev; struct gpio_desc* descs; int /*<<< orphan*/ * data; int /*<<< orphan*/ * chip; } ;
struct gpio_desc {int /*<<< orphan*/  flags; } ;
struct gpio_chip {struct gpio_device* gpiodev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_REQUESTED ; 
 int /*<<< orphan*/  acpi_gpiochip_remove (struct gpio_chip*) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  gpiochip_free_hogs (struct gpio_chip*) ; 
 int /*<<< orphan*/  gpiochip_free_valid_mask (struct gpio_chip*) ; 
 int /*<<< orphan*/  gpiochip_irqchip_remove (struct gpio_chip*) ; 
 int /*<<< orphan*/  gpiochip_remove_pin_ranges (struct gpio_chip*) ; 
 int /*<<< orphan*/  gpiochip_sysfs_unregister (struct gpio_device*) ; 
 int /*<<< orphan*/  of_gpiochip_remove (struct gpio_chip*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gpiochip_remove(struct gpio_chip *chip)
{
	struct gpio_device *gdev = chip->gpiodev;
	struct gpio_desc *desc;
	unsigned long	flags;
	unsigned	i;
	bool		requested = false;

	/* FIXME: should the legacy sysfs handling be moved to gpio_device? */
	gpiochip_sysfs_unregister(gdev);
	gpiochip_free_hogs(chip);
	/* Numb the device, cancelling all outstanding operations */
	gdev->chip = NULL;
	gpiochip_irqchip_remove(chip);
	acpi_gpiochip_remove(chip);
	gpiochip_remove_pin_ranges(chip);
	of_gpiochip_remove(chip);
	gpiochip_free_valid_mask(chip);
	/*
	 * We accept no more calls into the driver from this point, so
	 * NULL the driver data pointer
	 */
	gdev->data = NULL;

	spin_lock_irqsave(&gpio_lock, flags);
	for (i = 0; i < gdev->ngpio; i++) {
		desc = &gdev->descs[i];
		if (test_bit(FLAG_REQUESTED, &desc->flags))
			requested = true;
	}
	spin_unlock_irqrestore(&gpio_lock, flags);

	if (requested)
		dev_crit(&gdev->dev,
			 "REMOVING GPIOCHIP WITH GPIOS STILL REQUESTED\n");

	/*
	 * The gpiochip side puts its use of the device to rest here:
	 * if there are no userspace clients, the chardev and device will
	 * be removed, else it will be dangling until the last user is
	 * gone.
	 */
	cdev_device_del(&gdev->chrdev, &gdev->dev);
	put_device(&gdev->dev);
}