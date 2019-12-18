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
 struct zx2967_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  zx2967_wdt_refresh (struct zx2967_wdt*) ; 

__attribute__((used)) static int zx2967_wdt_keepalive(struct watchdog_device *wdd)
{
	struct zx2967_wdt *wdt = watchdog_get_drvdata(wdd);

	zx2967_wdt_refresh(wdt);

	return 0;
}