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
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct lp3943_pwm_map {int dummy; } ;
struct lp3943_pwm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP3943_GPIO_OUT_HIGH ; 
 int /*<<< orphan*/  lp3943_pwm_set_mode (struct lp3943_pwm*,struct lp3943_pwm_map*,int /*<<< orphan*/ ) ; 
 struct lp3943_pwm_map* pwm_get_chip_data (struct pwm_device*) ; 
 struct lp3943_pwm* to_lp3943_pwm (struct pwm_chip*) ; 

__attribute__((used)) static void lp3943_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct lp3943_pwm *lp3943_pwm = to_lp3943_pwm(chip);
	struct lp3943_pwm_map *pwm_map = pwm_get_chip_data(pwm);

	/*
	 * LP3943 outputs are open-drain, so the pin should be configured
	 * when the PWM is disabled.
	 */

	lp3943_pwm_set_mode(lp3943_pwm, pwm_map, LP3943_GPIO_OUT_HIGH);
}