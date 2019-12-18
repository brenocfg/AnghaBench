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
struct pwm_mediatek_chip {int /*<<< orphan*/  clk_top; int /*<<< orphan*/  clk_main; int /*<<< orphan*/ * clk_pwms; } ;
struct pwm_device {size_t hwpwm; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct pwm_mediatek_chip* to_pwm_mediatek_chip (struct pwm_chip*) ; 

__attribute__((used)) static int pwm_mediatek_clk_enable(struct pwm_chip *chip,
				   struct pwm_device *pwm)
{
	struct pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	int ret;

	ret = clk_prepare_enable(pc->clk_top);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(pc->clk_main);
	if (ret < 0)
		goto disable_clk_top;

	ret = clk_prepare_enable(pc->clk_pwms[pwm->hwpwm]);
	if (ret < 0)
		goto disable_clk_main;

	return 0;

disable_clk_main:
	clk_disable_unprepare(pc->clk_main);
disable_clk_top:
	clk_disable_unprepare(pc->clk_top);

	return ret;
}