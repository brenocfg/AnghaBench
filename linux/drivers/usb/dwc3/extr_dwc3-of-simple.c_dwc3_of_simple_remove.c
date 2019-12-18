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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct dwc3_of_simple {int /*<<< orphan*/  resets; int /*<<< orphan*/  pulse_resets; scalar_t__ num_clocks; int /*<<< orphan*/  clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_bulk_disable_unprepare (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_bulk_put_all (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 struct dwc3_of_simple* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_of_simple_remove(struct platform_device *pdev)
{
	struct dwc3_of_simple	*simple = platform_get_drvdata(pdev);
	struct device		*dev = &pdev->dev;

	of_platform_depopulate(dev);

	clk_bulk_disable_unprepare(simple->num_clocks, simple->clks);
	clk_bulk_put_all(simple->num_clocks, simple->clks);
	simple->num_clocks = 0;

	if (!simple->pulse_resets)
		reset_control_assert(simple->resets);

	reset_control_put(simple->resets);

	pm_runtime_disable(dev);
	pm_runtime_put_noidle(dev);
	pm_runtime_set_suspended(dev);

	return 0;
}