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
struct zx2967_wdt {int dummy; } ;
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __zx2967_wdt_stop (struct zx2967_wdt*) ; 
 struct zx2967_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int zx2967_wdt_stop(struct watchdog_device *wdd)
{
	struct zx2967_wdt *wdt = watchdog_get_drvdata(wdd);

	__zx2967_wdt_stop(wdt);

	return 0;
}