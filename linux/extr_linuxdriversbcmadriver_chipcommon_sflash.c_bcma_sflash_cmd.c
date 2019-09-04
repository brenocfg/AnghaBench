#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bcma_drv_cc {TYPE_1__* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_FLASHCTL ; 
 int BCMA_CC_FLASHCTL_BUSY ; 
 int BCMA_CC_FLASHCTL_START ; 
 int bcma_cc_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_cc_write32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void bcma_sflash_cmd(struct bcma_drv_cc *cc, u32 opcode)
{
	int i;
	bcma_cc_write32(cc, BCMA_CC_FLASHCTL,
			BCMA_CC_FLASHCTL_START | opcode);
	for (i = 0; i < 1000; i++) {
		if (!(bcma_cc_read32(cc, BCMA_CC_FLASHCTL) &
		      BCMA_CC_FLASHCTL_BUSY))
			return;
		cpu_relax();
	}
	bcma_err(cc->core->bus, "SFLASH control command failed (timeout)!\n");
}