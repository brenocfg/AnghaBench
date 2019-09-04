#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct bcma_drv_pcie2 {TYPE_2__* core; } ;
struct TYPE_3__ {int rev; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */

__attribute__((used)) static void pciedev_crwlpciegen2(struct bcma_drv_pcie2 *pcie2)
{
	u8 core_rev = pcie2->core->id.rev;
	bool pciewar160, pciewar162;

	pciewar160 = core_rev == 7 || core_rev == 9 || core_rev == 11;
	pciewar162 = core_rev == 5 || core_rev == 7 || core_rev == 8 ||
		     core_rev == 9 || core_rev == 11;

	if (!pciewar160 && !pciewar162)
		return;

/* TODO */
#if 0
	pcie2_set32(pcie2, BCMA_CORE_PCIE2_CLK_CONTROL,
		    PCIE_DISABLE_L1CLK_GATING);
#if 0
	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR,
		      PCIEGEN2_COE_PVT_TL_CTRL_0);
	pcie2_mask32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA,
		     ~(1 << COE_PVT_TL_CTRL_0_PM_DIS_L1_REENTRY_BIT));
#endif
#endif
}