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
struct pwm_imx27_chip {int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_per; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct pwm_imx27_chip* to_pwm_imx27_chip (struct pwm_chip*) ; 

__attribute__((used)) static void pwm_imx27_clk_disable_unprepare(struct pwm_chip *chip)
{
	struct pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);

	clk_disable_unprepare(imx->clk_per);
	clk_disable_unprepare(imx->clk_ipg);
}