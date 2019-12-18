#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int npwm; struct pwm_device* pwms; } ;
struct tegra_pwm_chip {TYPE_1__ chip; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;
struct pwm_device {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct tegra_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_is_enabled (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_writel (struct tegra_pwm_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int pwmchip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_pwm_remove(struct platform_device *pdev)
{
	struct tegra_pwm_chip *pc = platform_get_drvdata(pdev);
	unsigned int i;
	int err;

	if (WARN_ON(!pc))
		return -ENODEV;

	err = clk_prepare_enable(pc->clk);
	if (err < 0)
		return err;

	for (i = 0; i < pc->chip.npwm; i++) {
		struct pwm_device *pwm = &pc->chip.pwms[i];

		if (!pwm_is_enabled(pwm))
			if (clk_prepare_enable(pc->clk) < 0)
				continue;

		pwm_writel(pc, i, 0);

		clk_disable_unprepare(pc->clk);
	}

	reset_control_assert(pc->rst);
	clk_disable_unprepare(pc->clk);

	return pwmchip_remove(&pc->chip);
}