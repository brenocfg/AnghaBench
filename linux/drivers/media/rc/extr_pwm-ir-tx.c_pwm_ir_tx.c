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
struct rc_dev {struct pwm_ir* priv; } ;
struct pwm_ir {int carrier; int duty_cycle; struct pwm_device* pwm; } ;
struct pwm_device {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 long ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_config (struct pwm_device*,int,int) ; 
 int /*<<< orphan*/  pwm_disable (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_enable (struct pwm_device*) ; 
 int /*<<< orphan*/  usleep_range (long,long) ; 

__attribute__((used)) static int pwm_ir_tx(struct rc_dev *dev, unsigned int *txbuf,
		     unsigned int count)
{
	struct pwm_ir *pwm_ir = dev->priv;
	struct pwm_device *pwm = pwm_ir->pwm;
	int i, duty, period;
	ktime_t edge;
	long delta;

	period = DIV_ROUND_CLOSEST(NSEC_PER_SEC, pwm_ir->carrier);
	duty = DIV_ROUND_CLOSEST(pwm_ir->duty_cycle * period, 100);

	pwm_config(pwm, duty, period);

	edge = ktime_get();

	for (i = 0; i < count; i++) {
		if (i % 2) // space
			pwm_disable(pwm);
		else
			pwm_enable(pwm);

		edge = ktime_add_us(edge, txbuf[i]);
		delta = ktime_us_delta(edge, ktime_get());
		if (delta > 0)
			usleep_range(delta, delta + 10);
	}

	pwm_disable(pwm);

	return count;
}