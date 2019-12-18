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
typedef  int /*<<< orphan*/  u8 ;
struct lp55xx_led {unsigned long max_current; struct lp55xx_chip* chip; } ;
struct lp55xx_chip {int /*<<< orphan*/  lock; TYPE_1__* cfg; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_led_current ) (struct lp55xx_led*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t EINVAL ; 
 struct lp55xx_led* dev_to_lp55xx_led (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lp55xx_led*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t lp55xx_store_current(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t len)
{
	struct lp55xx_led *led = dev_to_lp55xx_led(dev);
	struct lp55xx_chip *chip = led->chip;
	unsigned long curr;

	if (kstrtoul(buf, 0, &curr))
		return -EINVAL;

	if (curr > led->max_current)
		return -EINVAL;

	if (!chip->cfg->set_led_current)
		return len;

	mutex_lock(&chip->lock);
	chip->cfg->set_led_current(led, (u8)curr);
	mutex_unlock(&chip->lock);

	return len;
}