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
struct watchdog_device {int dummy; } ;
struct sp805_wdt {int load_val; int /*<<< orphan*/  lock; scalar_t__ base; TYPE_1__* adev; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int INT_ENABLE ; 
 int INT_MASK ; 
 int LOCK ; 
 int RESET_ENABLE ; 
 int UNLOCK ; 
 scalar_t__ WDTCONTROL ; 
 scalar_t__ WDTINTCLR ; 
 scalar_t__ WDTLOAD ; 
 scalar_t__ WDTLOCK ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sp805_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int wdt_config(struct watchdog_device *wdd, bool ping)
{
	struct sp805_wdt *wdt = watchdog_get_drvdata(wdd);
	int ret;

	if (!ping) {

		ret = clk_prepare_enable(wdt->clk);
		if (ret) {
			dev_err(&wdt->adev->dev, "clock enable fail");
			return ret;
		}
	}

	spin_lock(&wdt->lock);

	writel_relaxed(UNLOCK, wdt->base + WDTLOCK);
	writel_relaxed(wdt->load_val, wdt->base + WDTLOAD);
	writel_relaxed(INT_MASK, wdt->base + WDTINTCLR);

	if (!ping)
		writel_relaxed(INT_ENABLE | RESET_ENABLE, wdt->base +
				WDTCONTROL);

	writel_relaxed(LOCK, wdt->base + WDTLOCK);

	/* Flush posted writes. */
	readl_relaxed(wdt->base + WDTLOCK);
	spin_unlock(&wdt->lock);

	return 0;
}