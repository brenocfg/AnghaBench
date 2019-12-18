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
struct watchdog_device {int dummy; } ;
struct sp805_wdt {scalar_t__ base; } ;

/* Variables and functions */
 int INT_ENABLE ; 
 int RESET_ENABLE ; 
 scalar_t__ WDTCONTROL ; 
 scalar_t__ WDTLOAD ; 
 struct sp805_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int
wdt_restart(struct watchdog_device *wdd, unsigned long mode, void *cmd)
{
	struct sp805_wdt *wdt = watchdog_get_drvdata(wdd);

	writel_relaxed(0, wdt->base + WDTCONTROL);
	writel_relaxed(0, wdt->base + WDTLOAD);
	writel_relaxed(INT_ENABLE | RESET_ENABLE, wdt->base + WDTCONTROL);

	return 0;
}