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
typedef  int /*<<< orphan*/  u32 ;
struct pwm_mediatek_chip {int /*<<< orphan*/  regs; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int pwm_mediatek_clk_enable (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct pwm_mediatek_chip* to_pwm_mediatek_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwm_mediatek_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	u32 value;
	int ret;

	ret = pwm_mediatek_clk_enable(chip, pwm);
	if (ret < 0)
		return ret;

	value = readl(pc->regs);
	value |= BIT(pwm->hwpwm);
	writel(value, pc->regs);

	return 0;
}