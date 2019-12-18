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
typedef  unsigned int u32 ;
struct watchdog_device {unsigned int timeout; } ;
struct imx7ulp_wdt_device {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int UNLOCK ; 
 unsigned int WDOG_CLOCK_RATE ; 
 scalar_t__ WDOG_CNT ; 
 scalar_t__ WDOG_TOVAL ; 
 struct imx7ulp_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int imx7ulp_wdt_set_timeout(struct watchdog_device *wdog,
				   unsigned int timeout)
{
	struct imx7ulp_wdt_device *wdt = watchdog_get_drvdata(wdog);
	u32 val = WDOG_CLOCK_RATE * timeout;

	writel(UNLOCK, wdt->base + WDOG_CNT);
	writel(val, wdt->base + WDOG_TOVAL);

	wdog->timeout = timeout;

	return 0;
}