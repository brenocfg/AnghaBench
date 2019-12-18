#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct atmel_pwm_chip {TYPE_2__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  period; int /*<<< orphan*/  duty; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_pwm_ch_writel (struct atmel_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct atmel_pwm_chip* to_atmel_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void atmel_pwm_set_cprd_cdty(struct pwm_chip *chip,
				    struct pwm_device *pwm,
				    unsigned long cprd, unsigned long cdty)
{
	struct atmel_pwm_chip *atmel_pwm = to_atmel_pwm_chip(chip);

	atmel_pwm_ch_writel(atmel_pwm, pwm->hwpwm,
			    atmel_pwm->data->regs.duty, cdty);
	atmel_pwm_ch_writel(atmel_pwm, pwm->hwpwm,
			    atmel_pwm->data->regs.period, cprd);
}