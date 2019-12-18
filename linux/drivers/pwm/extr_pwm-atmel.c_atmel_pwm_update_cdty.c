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
typedef  unsigned long u32 ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct atmel_pwm_chip {TYPE_2__* data; } ;
struct TYPE_3__ {scalar_t__ duty_upd; scalar_t__ period_upd; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;

/* Variables and functions */
 scalar_t__ PWM_CMR ; 
 unsigned long PWM_CMR_UPD_CDTY ; 
 unsigned long atmel_pwm_ch_readl (struct atmel_pwm_chip*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atmel_pwm_ch_writel (struct atmel_pwm_chip*,int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 struct atmel_pwm_chip* to_atmel_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void atmel_pwm_update_cdty(struct pwm_chip *chip, struct pwm_device *pwm,
				  unsigned long cdty)
{
	struct atmel_pwm_chip *atmel_pwm = to_atmel_pwm_chip(chip);
	u32 val;

	if (atmel_pwm->data->regs.duty_upd ==
	    atmel_pwm->data->regs.period_upd) {
		val = atmel_pwm_ch_readl(atmel_pwm, pwm->hwpwm, PWM_CMR);
		val &= ~PWM_CMR_UPD_CDTY;
		atmel_pwm_ch_writel(atmel_pwm, pwm->hwpwm, PWM_CMR, val);
	}

	atmel_pwm_ch_writel(atmel_pwm, pwm->hwpwm,
			    atmel_pwm->data->regs.duty_upd, cdty);
}