#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct gpio_device {struct device* mockdev; struct device dev; struct gpio_chip* chip; } ;
struct gpio_chip {int /*<<< orphan*/  base; struct device* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 struct device* device_create_with_groups (TYPE_1__*,struct device*,int /*<<< orphan*/ ,struct gpio_chip*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ gpio_class ; 
 int /*<<< orphan*/  gpiochip_groups ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_lock ; 

int gpiochip_sysfs_register(struct gpio_device *gdev)
{
	struct device	*dev;
	struct device	*parent;
	struct gpio_chip *chip = gdev->chip;

	/*
	 * Many systems add gpio chips for SOC support very early,
	 * before driver model support is available.  In those cases we
	 * register later, in gpiolib_sysfs_init() ... here we just
	 * verify that _some_ field of gpio_class got initialized.
	 */
	if (!gpio_class.p)
		return 0;

	/*
	 * For sysfs backward compatibility we need to preserve this
	 * preferred parenting to the gpio_chip parent field, if set.
	 */
	if (chip->parent)
		parent = chip->parent;
	else
		parent = &gdev->dev;

	/* use chip->base for the ID; it's already known to be unique */
	dev = device_create_with_groups(&gpio_class, parent,
					MKDEV(0, 0),
					chip, gpiochip_groups,
					"gpiochip%d", chip->base);
	if (IS_ERR(dev))
		return PTR_ERR(dev);

	mutex_lock(&sysfs_lock);
	gdev->mockdev = dev;
	mutex_unlock(&sysfs_lock);

	return 0;
}