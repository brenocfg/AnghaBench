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

/* Variables and functions */
 scalar_t__ EP93XX_PWMx_ENABLE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct ep93xx_pwm* to_ep93xx_pwm (struct pwm_chip*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void ep93xx_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct ep93xx_pwm *ep93xx_pwm = to_ep93xx_pwm(chip);

	writew(0x0, ep93xx_pwm->base + EP93XX_PWMx_ENABLE);
	clk_disable(ep93xx_pwm->clk);
}