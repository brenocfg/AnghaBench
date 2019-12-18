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
typedef  int u32 ;
struct watchdog_device {int dummy; } ;
struct davinci_wdt_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PRD12 ; 
 scalar_t__ PRD34 ; 
 scalar_t__ TCR ; 
 scalar_t__ TGCR ; 
 scalar_t__ TIM12 ; 
 int TIM12RS_UNRESET ; 
 scalar_t__ TIM34 ; 
 int TIM34RS_UNRESET ; 
 int TIMMODE_64BIT_WDOG ; 
 int WDEN ; 
 int WDKEY_SEQ0 ; 
 int WDKEY_SEQ1 ; 
 scalar_t__ WDTCR ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct davinci_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int davinci_wdt_restart(struct watchdog_device *wdd,
			       unsigned long action, void *data)
{
	struct davinci_wdt_device *davinci_wdt = watchdog_get_drvdata(wdd);
	u32 tgcr, wdtcr;

	/* disable, internal clock source */
	iowrite32(0, davinci_wdt->base + TCR);

	/* reset timer, set mode to 64-bit watchdog, and unreset */
	tgcr = 0;
	iowrite32(tgcr, davinci_wdt->base + TGCR);
	tgcr = TIMMODE_64BIT_WDOG | TIM12RS_UNRESET | TIM34RS_UNRESET;
	iowrite32(tgcr, davinci_wdt->base + TGCR);

	/* clear counter and period regs */
	iowrite32(0, davinci_wdt->base + TIM12);
	iowrite32(0, davinci_wdt->base + TIM34);
	iowrite32(0, davinci_wdt->base + PRD12);
	iowrite32(0, davinci_wdt->base + PRD34);

	/* put watchdog in pre-active state */
	wdtcr = WDKEY_SEQ0 | WDEN;
	iowrite32(wdtcr, davinci_wdt->base + WDTCR);

	/* put watchdog in active state */
	wdtcr = WDKEY_SEQ1 | WDEN;
	iowrite32(wdtcr, davinci_wdt->base + WDTCR);

	/* write an invalid value to the WDKEY field to trigger a restart */
	wdtcr = 0x00004000;
	iowrite32(wdtcr, davinci_wdt->base + WDTCR);

	return 0;
}