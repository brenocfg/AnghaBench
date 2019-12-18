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
struct sprd_wdt {int /*<<< orphan*/  enable; int /*<<< orphan*/  rtc_enable; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SPRD_WDT_CTRL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_wdt_lock (scalar_t__) ; 
 int /*<<< orphan*/  sprd_wdt_unlock (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sprd_wdt_disable(void *_data)
{
	struct sprd_wdt *wdt = _data;

	sprd_wdt_unlock(wdt->base);
	writel_relaxed(0x0, wdt->base + SPRD_WDT_CTRL);
	sprd_wdt_lock(wdt->base);

	clk_disable_unprepare(wdt->rtc_enable);
	clk_disable_unprepare(wdt->enable);
}