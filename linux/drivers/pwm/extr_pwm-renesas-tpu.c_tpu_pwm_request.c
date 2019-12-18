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
struct tpu_pwm_device {scalar_t__ channel; int timer_on; scalar_t__ duty; scalar_t__ period; scalar_t__ prescaler; int /*<<< orphan*/  polarity; struct tpu_device* tpu; } ;
struct tpu_device {int dummy; } ;
struct pwm_device {scalar_t__ hwpwm; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PWM_POLARITY_NORMAL ; 
 scalar_t__ TPU_CHANNEL_MAX ; 
 struct tpu_pwm_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_set_chip_data (struct pwm_device*,struct tpu_pwm_device*) ; 
 struct tpu_device* to_tpu_device (struct pwm_chip*) ; 

__attribute__((used)) static int tpu_pwm_request(struct pwm_chip *chip, struct pwm_device *_pwm)
{
	struct tpu_device *tpu = to_tpu_device(chip);
	struct tpu_pwm_device *pwm;

	if (_pwm->hwpwm >= TPU_CHANNEL_MAX)
		return -EINVAL;

	pwm = kzalloc(sizeof(*pwm), GFP_KERNEL);
	if (pwm == NULL)
		return -ENOMEM;

	pwm->tpu = tpu;
	pwm->channel = _pwm->hwpwm;
	pwm->polarity = PWM_POLARITY_NORMAL;
	pwm->prescaler = 0;
	pwm->period = 0;
	pwm->duty = 0;

	pwm->timer_on = false;

	pwm_set_chip_data(_pwm, pwm);

	return 0;
}