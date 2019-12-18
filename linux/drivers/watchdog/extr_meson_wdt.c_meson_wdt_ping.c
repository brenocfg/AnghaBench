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
struct meson_wdt_dev {scalar_t__ wdt_base; } ;

/* Variables and functions */
 scalar_t__ MESON_WDT_RESET ; 
 struct meson_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_wdt_ping(struct watchdog_device *wdt_dev)
{
	struct meson_wdt_dev *meson_wdt = watchdog_get_drvdata(wdt_dev);

	writel(0, meson_wdt->wdt_base + MESON_WDT_RESET);

	return 0;
}