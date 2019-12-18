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
struct pwm_omap_dmtimer_chip {int /*<<< orphan*/  mutex; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_omap_dmtimer_start (struct pwm_omap_dmtimer_chip*) ; 
 struct pwm_omap_dmtimer_chip* to_pwm_omap_dmtimer_chip (struct pwm_chip*) ; 

__attribute__((used)) static int pwm_omap_dmtimer_enable(struct pwm_chip *chip,
				   struct pwm_device *pwm)
{
	struct pwm_omap_dmtimer_chip *omap = to_pwm_omap_dmtimer_chip(chip);

	mutex_lock(&omap->mutex);
	pwm_omap_dmtimer_start(omap);
	mutex_unlock(&omap->mutex);

	return 0;
}