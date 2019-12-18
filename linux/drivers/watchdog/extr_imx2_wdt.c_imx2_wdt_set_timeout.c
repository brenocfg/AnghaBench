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
struct watchdog_device {unsigned int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX2_WDT_MAX_TIME ; 
 int /*<<< orphan*/  __imx2_wdt_set_timeout (struct watchdog_device*,unsigned int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx2_wdt_set_timeout(struct watchdog_device *wdog,
				unsigned int new_timeout)
{
	unsigned int actual;

	actual = min(new_timeout, IMX2_WDT_MAX_TIME);
	__imx2_wdt_set_timeout(wdog, actual);
	wdog->timeout = new_timeout;
	return 0;
}