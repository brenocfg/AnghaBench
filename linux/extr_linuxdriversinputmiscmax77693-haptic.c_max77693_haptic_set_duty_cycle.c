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
struct pwm_args {int period; } ;
struct max77693_haptic {int pwm_duty; int /*<<< orphan*/  dev; int /*<<< orphan*/  pwm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int pwm_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pwm_get_args (int /*<<< orphan*/ ,struct pwm_args*) ; 

__attribute__((used)) static int max77693_haptic_set_duty_cycle(struct max77693_haptic *haptic)
{
	struct pwm_args pargs;
	int delta;
	int error;

	pwm_get_args(haptic->pwm_dev, &pargs);
	delta = (pargs.period + haptic->pwm_duty) / 2;
	error = pwm_config(haptic->pwm_dev, delta, pargs.period);
	if (error) {
		dev_err(haptic->dev, "failed to configure pwm: %d\n", error);
		return error;
	}

	return 0;
}