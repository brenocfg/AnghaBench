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

/* Variables and functions */
 int MV64x60_WDC_ENABLED_SHIFT ; 
 scalar_t__ MV64x60_WDT_WDC_OFFSET ; 
 int mv64x60_wdt_count ; 
 scalar_t__ mv64x60_wdt_regs ; 
 int /*<<< orphan*/  mv64x60_wdt_spinlock ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mv64x60_wdt_toggle_wdc(int enabled_predicate, int field_shift)
{
	u32 data;
	u32 enabled;
	int ret = 0;

	spin_lock(&mv64x60_wdt_spinlock);
	data = readl(mv64x60_wdt_regs + MV64x60_WDT_WDC_OFFSET);
	enabled = (data >> MV64x60_WDC_ENABLED_SHIFT) & 1;

	/* only toggle the requested field if enabled state matches predicate */
	if ((enabled ^ enabled_predicate) == 0) {
		/* We write a 1, then a 2 -- to the appropriate field */
		data = (1 << field_shift) | mv64x60_wdt_count;
		writel(data, mv64x60_wdt_regs + MV64x60_WDT_WDC_OFFSET);

		data = (2 << field_shift) | mv64x60_wdt_count;
		writel(data, mv64x60_wdt_regs + MV64x60_WDT_WDC_OFFSET);
		ret = 1;
	}
	spin_unlock(&mv64x60_wdt_spinlock);

	return ret;
}