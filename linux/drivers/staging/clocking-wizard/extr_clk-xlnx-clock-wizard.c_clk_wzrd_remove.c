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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct clk_wzrd {int /*<<< orphan*/  axi_clk; int /*<<< orphan*/  nb; int /*<<< orphan*/  clk_in1; scalar_t__ speed_grade; int /*<<< orphan*/ * clks_internal; int /*<<< orphan*/ * clkout; } ;

/* Variables and functions */
 int WZRD_NUM_OUTPUTS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 struct clk_wzrd* platform_get_drvdata (struct platform_device*) ; 
 int wzrd_clk_int_max ; 

__attribute__((used)) static int clk_wzrd_remove(struct platform_device *pdev)
{
	int i;
	struct clk_wzrd *clk_wzrd = platform_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	for (i = 0; i < WZRD_NUM_OUTPUTS; i++)
		clk_unregister(clk_wzrd->clkout[i]);
	for (i = 0; i < wzrd_clk_int_max; i++)
		clk_unregister(clk_wzrd->clks_internal[i]);

	if (clk_wzrd->speed_grade) {
		clk_notifier_unregister(clk_wzrd->axi_clk, &clk_wzrd->nb);
		clk_notifier_unregister(clk_wzrd->clk_in1, &clk_wzrd->nb);
	}

	clk_disable_unprepare(clk_wzrd->axi_clk);

	return 0;
}