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
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct lpc18xx_pwm_data {int /*<<< orphan*/  duty_event; } ;
struct lpc18xx_pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC18XX_PWM_EVCTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC18XX_PWM_OUTPUTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC18XX_PWM_OUTPUTSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_pwm_writel (struct lpc18xx_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpc18xx_pwm_data* pwm_get_chip_data (struct pwm_device*) ; 
 struct lpc18xx_pwm_chip* to_lpc18xx_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void lpc18xx_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	struct lpc18xx_pwm_data *lpc18xx_data = pwm_get_chip_data(pwm);

	lpc18xx_pwm_writel(lpc18xx_pwm,
			   LPC18XX_PWM_EVCTRL(lpc18xx_data->duty_event), 0);
	lpc18xx_pwm_writel(lpc18xx_pwm, LPC18XX_PWM_OUTPUTSET(pwm->hwpwm), 0);
	lpc18xx_pwm_writel(lpc18xx_pwm, LPC18XX_PWM_OUTPUTCL(pwm->hwpwm), 0);
}