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
typedef  scalar_t__ u32 ;
struct sprd_wdt {scalar_t__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ SPRD_WDT_CNT_HIGH_SHIFT ; 
 scalar_t__ SPRD_WDT_CNT_STEP ; 
 scalar_t__ SPRD_WDT_INT_RAW ; 
 scalar_t__ SPRD_WDT_IRQ_LOAD_HIGH ; 
 scalar_t__ SPRD_WDT_IRQ_LOAD_LOW ; 
 scalar_t__ SPRD_WDT_LD_BUSY_BIT ; 
 scalar_t__ SPRD_WDT_LOAD_HIGH ; 
 scalar_t__ SPRD_WDT_LOAD_LOW ; 
 scalar_t__ SPRD_WDT_LOAD_TIMEOUT ; 
 scalar_t__ SPRD_WDT_LOW_VALUE_MASK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sprd_wdt_lock (scalar_t__) ; 
 int /*<<< orphan*/  sprd_wdt_unlock (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sprd_wdt_load_value(struct sprd_wdt *wdt, u32 timeout,
			       u32 pretimeout)
{
	u32 val, delay_cnt = 0;
	u32 tmr_step = timeout * SPRD_WDT_CNT_STEP;
	u32 prtmr_step = pretimeout * SPRD_WDT_CNT_STEP;

	sprd_wdt_unlock(wdt->base);
	writel_relaxed((tmr_step >> SPRD_WDT_CNT_HIGH_SHIFT) &
		      SPRD_WDT_LOW_VALUE_MASK, wdt->base + SPRD_WDT_LOAD_HIGH);
	writel_relaxed((tmr_step & SPRD_WDT_LOW_VALUE_MASK),
		       wdt->base + SPRD_WDT_LOAD_LOW);
	writel_relaxed((prtmr_step >> SPRD_WDT_CNT_HIGH_SHIFT) &
			SPRD_WDT_LOW_VALUE_MASK,
		       wdt->base + SPRD_WDT_IRQ_LOAD_HIGH);
	writel_relaxed(prtmr_step & SPRD_WDT_LOW_VALUE_MASK,
		       wdt->base + SPRD_WDT_IRQ_LOAD_LOW);
	sprd_wdt_lock(wdt->base);

	/*
	 * Waiting the load value operation done,
	 * it needs two or three RTC clock cycles.
	 */
	do {
		val = readl_relaxed(wdt->base + SPRD_WDT_INT_RAW);
		if (!(val & SPRD_WDT_LD_BUSY_BIT))
			break;

		cpu_relax();
	} while (delay_cnt++ < SPRD_WDT_LOAD_TIMEOUT);

	if (delay_cnt >= SPRD_WDT_LOAD_TIMEOUT)
		return -EBUSY;
	return 0;
}