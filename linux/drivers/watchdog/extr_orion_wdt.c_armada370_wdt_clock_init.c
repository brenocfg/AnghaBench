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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct orion_watchdog {int clk_rate; int /*<<< orphan*/  clk; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TIMER_CTRL ; 
 int WDT_A370_RATIO ; 
 int /*<<< orphan*/  WDT_A370_RATIO_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDT_A370_RATIO_SHIFT ; 
 int /*<<< orphan*/  atomic_io_modify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada370_wdt_clock_init(struct platform_device *pdev,
				    struct orion_watchdog *dev)
{
	int ret;

	dev->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(dev->clk))
		return PTR_ERR(dev->clk);
	ret = clk_prepare_enable(dev->clk);
	if (ret) {
		clk_put(dev->clk);
		return ret;
	}

	/* Setup watchdog input clock */
	atomic_io_modify(dev->reg + TIMER_CTRL,
			WDT_A370_RATIO_MASK(WDT_A370_RATIO_SHIFT),
			WDT_A370_RATIO_MASK(WDT_A370_RATIO_SHIFT));

	dev->clk_rate = clk_get_rate(dev->clk) / WDT_A370_RATIO;
	return 0;
}