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
typedef  int u16 ;
struct bcma_device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CLKCTLST ; 
 int BCMA_CLKCTLST_EXTRESREQ ; 
 int BCMA_CLKCTLST_EXTRESST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bcma_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bcma_mask32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void bcma_core_pll_ctl(struct bcma_device *core, u32 req, u32 status, bool on)
{
	u16 i;

	WARN_ON(req & ~BCMA_CLKCTLST_EXTRESREQ);
	WARN_ON(status & ~BCMA_CLKCTLST_EXTRESST);

	if (on) {
		bcma_set32(core, BCMA_CLKCTLST, req);
		for (i = 0; i < 10000; i++) {
			if ((bcma_read32(core, BCMA_CLKCTLST) & status) ==
			    status) {
				i = 0;
				break;
			}
			udelay(10);
		}
		if (i)
			bcma_err(core->bus, "PLL enable timeout\n");
	} else {
		/*
		 * Mask the PLL but don't wait for it to be disabled. PLL may be
		 * shared between cores and will be still up if there is another
		 * core using it.
		 */
		bcma_mask32(core, BCMA_CLKCTLST, ~req);
		bcma_read32(core, BCMA_CLKCTLST);
	}
}