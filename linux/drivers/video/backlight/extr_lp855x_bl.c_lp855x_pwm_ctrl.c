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
struct pwm_device {int dummy; } ;
struct lp855x {struct pwm_device* pwm; int /*<<< orphan*/  chipname; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_2__ {unsigned int period_ns; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pwm_device*) ; 
 struct pwm_device* devm_pwm_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_apply_args (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_config (struct pwm_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pwm_disable (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_enable (struct pwm_device*) ; 

__attribute__((used)) static void lp855x_pwm_ctrl(struct lp855x *lp, int br, int max_br)
{
	unsigned int period = lp->pdata->period_ns;
	unsigned int duty = br * period / max_br;
	struct pwm_device *pwm;

	/* request pwm device with the consumer name */
	if (!lp->pwm) {
		pwm = devm_pwm_get(lp->dev, lp->chipname);
		if (IS_ERR(pwm))
			return;

		lp->pwm = pwm;

		/*
		 * FIXME: pwm_apply_args() should be removed when switching to
		 * the atomic PWM API.
		 */
		pwm_apply_args(pwm);
	}

	pwm_config(lp->pwm, duty, period);
	if (duty)
		pwm_enable(lp->pwm);
	else
		pwm_disable(lp->pwm);
}