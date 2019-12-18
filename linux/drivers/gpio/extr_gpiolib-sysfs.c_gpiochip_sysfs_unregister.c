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
struct gpio_device {struct gpio_desc* descs; int /*<<< orphan*/ * mockdev; struct gpio_chip* chip; } ;
struct gpio_desc {int /*<<< orphan*/  flags; } ;
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_SYSFS ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_free (struct gpio_desc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_lock ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gpiochip_sysfs_unregister(struct gpio_device *gdev)
{
	struct gpio_desc *desc;
	struct gpio_chip *chip = gdev->chip;
	unsigned int i;

	if (!gdev->mockdev)
		return;

	device_unregister(gdev->mockdev);

	/* prevent further gpiod exports */
	mutex_lock(&sysfs_lock);
	gdev->mockdev = NULL;
	mutex_unlock(&sysfs_lock);

	/* unregister gpiod class devices owned by sysfs */
	for (i = 0; i < chip->ngpio; i++) {
		desc = &gdev->descs[i];
		if (test_and_clear_bit(FLAG_SYSFS, &desc->flags))
			gpiod_free(desc);
	}
}