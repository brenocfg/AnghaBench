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
struct moxart_wdt_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_COUNT ; 
 scalar_t__ REG_ENABLE ; 
 scalar_t__ REG_MODE ; 
 struct moxart_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int moxart_wdt_restart(struct watchdog_device *wdt_dev,
			      unsigned long action, void *data)
{
	struct moxart_wdt_dev *moxart_wdt = watchdog_get_drvdata(wdt_dev);

	writel(1, moxart_wdt->base + REG_COUNT);
	writel(0x5ab9, moxart_wdt->base + REG_MODE);
	writel(0x03, moxart_wdt->base + REG_ENABLE);

	return 0;
}