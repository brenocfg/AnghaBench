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
struct meson_gxbb_wdt {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ GXBB_WDT_TCNT_REG ; 
 unsigned long GXBB_WDT_TCNT_SETUP_MASK ; 
 int /*<<< orphan*/  meson_gxbb_wdt_ping (struct watchdog_device*) ; 
 struct meson_gxbb_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int meson_gxbb_wdt_set_timeout(struct watchdog_device *wdt_dev,
				      unsigned int timeout)
{
	struct meson_gxbb_wdt *data = watchdog_get_drvdata(wdt_dev);
	unsigned long tcnt = timeout * 1000;

	if (tcnt > GXBB_WDT_TCNT_SETUP_MASK)
		tcnt = GXBB_WDT_TCNT_SETUP_MASK;

	wdt_dev->timeout = timeout;

	meson_gxbb_wdt_ping(wdt_dev);

	writel(tcnt, data->reg_base + GXBB_WDT_TCNT_REG);

	return 0;
}