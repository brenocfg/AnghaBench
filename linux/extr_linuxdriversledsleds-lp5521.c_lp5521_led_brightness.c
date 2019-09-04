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
struct lp55xx_led {int /*<<< orphan*/  brightness; scalar_t__ chan_nr; struct lp55xx_chip* chip; } ;
struct lp55xx_chip {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ LP5521_REG_LED_PWM_BASE ; 
 int lp55xx_write (struct lp55xx_chip*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp5521_led_brightness(struct lp55xx_led *led)
{
	struct lp55xx_chip *chip = led->chip;
	int ret;

	mutex_lock(&chip->lock);
	ret = lp55xx_write(chip, LP5521_REG_LED_PWM_BASE + led->chan_nr,
		led->brightness);
	mutex_unlock(&chip->lock);

	return ret;
}