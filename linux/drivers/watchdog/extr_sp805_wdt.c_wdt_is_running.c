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
typedef  int u32 ;
struct watchdog_device {int dummy; } ;
struct sp805_wdt {scalar_t__ base; } ;

/* Variables and functions */
 int ENABLE_MASK ; 
 scalar_t__ WDTCONTROL ; 
 int readl_relaxed (scalar_t__) ; 
 struct sp805_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static bool wdt_is_running(struct watchdog_device *wdd)
{
	struct sp805_wdt *wdt = watchdog_get_drvdata(wdd);
	u32 wdtcontrol = readl_relaxed(wdt->base + WDTCONTROL);

	return (wdtcontrol & ENABLE_MASK) == ENABLE_MASK;
}