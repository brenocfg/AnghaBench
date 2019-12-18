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
struct pdc_wdt_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PDC_WDT_TICKLE1 ; 
 int /*<<< orphan*/  PDC_WDT_TICKLE1_MAGIC ; 
 scalar_t__ PDC_WDT_TICKLE2 ; 
 int /*<<< orphan*/  PDC_WDT_TICKLE2_MAGIC ; 
 struct pdc_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pdc_wdt_keepalive(struct watchdog_device *wdt_dev)
{
	struct pdc_wdt_dev *wdt = watchdog_get_drvdata(wdt_dev);

	writel(PDC_WDT_TICKLE1_MAGIC, wdt->base + PDC_WDT_TICKLE1);
	writel(PDC_WDT_TICKLE2_MAGIC, wdt->base + PDC_WDT_TICKLE2);

	return 0;
}