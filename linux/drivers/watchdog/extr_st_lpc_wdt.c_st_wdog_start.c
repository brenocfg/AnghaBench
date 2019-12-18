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
struct st_wdog {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LPC_WDT_OFF ; 
 struct st_wdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int st_wdog_start(struct watchdog_device *wdd)
{
	struct st_wdog *st_wdog = watchdog_get_drvdata(wdd);

	writel_relaxed(1, st_wdog->base + LPC_WDT_OFF);

	return 0;
}