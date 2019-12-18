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
struct lm3601x_led {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
struct led_classdev_flash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3601X_ENABLE_REG ; 
 int LM3601X_MODE_STROBE ; 
 struct lm3601x_led* fled_cdev_to_led (struct led_classdev_flash*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lm3601x_strobe_get(struct led_classdev_flash *fled_cdev, bool *state)
{
	struct lm3601x_led *led = fled_cdev_to_led(fled_cdev);
	int strobe_state;
	int ret;

	mutex_lock(&led->lock);

	ret = regmap_read(led->regmap, LM3601X_ENABLE_REG, &strobe_state);
	if (ret < 0)
		goto out;

	*state = strobe_state & LM3601X_MODE_STROBE;

out:
	mutex_unlock(&led->lock);
	return ret;
}