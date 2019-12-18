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
struct ep93xx_pwm {int /*<<< orphan*/  clk; scalar_t__ base; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 scalar_t__ EP93XX_PWMx_INVERT ; 
 int PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 struct ep93xx_pwm* to_ep93xx_pwm (struct pwm_chip*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int ep93xx_pwm_polarity(struct pwm_chip *chip, struct pwm_device *pwm,
			       enum pwm_polarity polarity)
{
	struct ep93xx_pwm *ep93xx_pwm = to_ep93xx_pwm(chip);
	int ret;

	/*
	 * The clock needs to be enabled to access the PWM registers.
	 * Polarity can only be changed when the PWM is disabled.
	 */
	ret = clk_enable(ep93xx_pwm->clk);
	if (ret)
		return ret;

	if (polarity == PWM_POLARITY_INVERSED)
		writew(0x1, ep93xx_pwm->base + EP93XX_PWMx_INVERT);
	else
		writew(0x0, ep93xx_pwm->base + EP93XX_PWMx_INVERT);

	clk_disable(ep93xx_pwm->clk);

	return 0;
}