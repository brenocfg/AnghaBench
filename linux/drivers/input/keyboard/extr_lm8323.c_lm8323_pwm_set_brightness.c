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
struct lm8323_pwm {int desired_brightness; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; struct lm8323_chip* chip; } ;
struct lm8323_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  pm_suspend; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 struct lm8323_pwm* cdev_to_pwm (struct led_classdev*) ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lm8323_pwm_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lm8323_pwm_set_brightness(struct led_classdev *led_cdev,
				      enum led_brightness brightness)
{
	struct lm8323_pwm *pwm = cdev_to_pwm(led_cdev);
	struct lm8323_chip *lm = pwm->chip;

	mutex_lock(&pwm->lock);
	pwm->desired_brightness = brightness;
	mutex_unlock(&pwm->lock);

	if (in_interrupt()) {
		schedule_work(&pwm->work);
	} else {
		/*
		 * Schedule PWM work as usual unless we are going into suspend
		 */
		mutex_lock(&lm->lock);
		if (likely(!lm->pm_suspend))
			schedule_work(&pwm->work);
		else
			lm8323_pwm_work(&pwm->work);
		mutex_unlock(&lm->lock);
	}
}