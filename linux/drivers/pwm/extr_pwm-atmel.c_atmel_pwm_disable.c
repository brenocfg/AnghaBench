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
struct pwm_device {int hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct atmel_pwm_chip {int updated_pwms; int /*<<< orphan*/  clk; int /*<<< orphan*/  isr_lock; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  PWM_DIS ; 
 int /*<<< orphan*/  PWM_ISR ; 
 int /*<<< orphan*/  PWM_SR ; 
 int atmel_pwm_readl (struct atmel_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_pwm_writel (struct atmel_pwm_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int,unsigned long) ; 
 struct atmel_pwm_chip* to_atmel_pwm_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void atmel_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm,
			      bool disable_clk)
{
	struct atmel_pwm_chip *atmel_pwm = to_atmel_pwm_chip(chip);
	unsigned long timeout = jiffies + 2 * HZ;

	/*
	 * Wait for at least a complete period to have passed before disabling a
	 * channel to be sure that CDTY has been updated
	 */
	mutex_lock(&atmel_pwm->isr_lock);
	atmel_pwm->updated_pwms |= atmel_pwm_readl(atmel_pwm, PWM_ISR);

	while (!(atmel_pwm->updated_pwms & (1 << pwm->hwpwm)) &&
	       time_before(jiffies, timeout)) {
		usleep_range(10, 100);
		atmel_pwm->updated_pwms |= atmel_pwm_readl(atmel_pwm, PWM_ISR);
	}

	mutex_unlock(&atmel_pwm->isr_lock);
	atmel_pwm_writel(atmel_pwm, PWM_DIS, 1 << pwm->hwpwm);

	/*
	 * Wait for the PWM channel disable operation to be effective before
	 * stopping the clock.
	 */
	timeout = jiffies + 2 * HZ;

	while ((atmel_pwm_readl(atmel_pwm, PWM_SR) & (1 << pwm->hwpwm)) &&
	       time_before(jiffies, timeout))
		usleep_range(10, 100);

	if (disable_clk)
		clk_disable(atmel_pwm->clk);
}