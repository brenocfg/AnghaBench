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
 int GEF_WDC_ENABLED_SHIFT ; 
 int gef_wdt_count ; 
 int /*<<< orphan*/  gef_wdt_regs ; 
 int /*<<< orphan*/  gef_wdt_spinlock ; 
 int ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gef_wdt_toggle_wdc(int enabled_predicate, int field_shift)
{
	u32 data;
	u32 enabled;
	int ret = 0;

	spin_lock(&gef_wdt_spinlock);
	data = ioread32be(gef_wdt_regs);
	enabled = (data >> GEF_WDC_ENABLED_SHIFT) & 1;

	/* only toggle the requested field if enabled state matches predicate */
	if ((enabled ^ enabled_predicate) == 0) {
		/* We write a 1, then a 2 -- to the appropriate field */
		data = (1 << field_shift) | gef_wdt_count;
		iowrite32be(data, gef_wdt_regs);

		data = (2 << field_shift) | gef_wdt_count;
		iowrite32be(data, gef_wdt_regs);
		ret = 1;
	}
	spin_unlock(&gef_wdt_spinlock);

	return ret;
}