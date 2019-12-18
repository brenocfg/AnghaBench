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
struct pm8916_wdt {int /*<<< orphan*/  wdev; scalar_t__ baseaddr; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PMIC_WD_BARK_STS_BIT ; 
 scalar_t__ PON_INT_RT_STS ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  watchdog_notify_pretimeout (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pm8916_wdt_isr(int irq, void *arg)
{
	struct pm8916_wdt *wdt = arg;
	int err, sts;

	err = regmap_read(wdt->regmap, wdt->baseaddr + PON_INT_RT_STS, &sts);
	if (err)
		return IRQ_HANDLED;

	if (sts & PMIC_WD_BARK_STS_BIT)
		watchdog_notify_pretimeout(&wdt->wdev);

	return IRQ_HANDLED;
}