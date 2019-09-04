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
struct bcma_drv_pcie2 {int reqsize; TYPE_1__* core; } ;
struct bcma_chipinfo {int id; int rev; } ;
struct bcma_bus {struct bcma_chipinfo chipinfo; } ;
struct TYPE_2__ {struct bcma_bus* bus; } ;

/* Variables and functions */
#define  BCMA_CHIP_ID_BCM4352 129 
#define  BCMA_CHIP_ID_BCM4360 128 
 int /*<<< orphan*/  BCMA_CORE_PCIE2_SPROM (int) ; 
 int /*<<< orphan*/  bcma_core_pcie2_cfg_write (struct bcma_drv_pcie2*,int,int) ; 
 int /*<<< orphan*/  bcma_core_pcie2_hw_ltr_war (struct bcma_drv_pcie2*) ; 
 int /*<<< orphan*/  bcma_core_pcie2_war_delay_perst_enab (struct bcma_drv_pcie2*,int) ; 
 int pcie2_read32 (struct bcma_drv_pcie2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciedev_crwlpciegen2 (struct bcma_drv_pcie2*) ; 
 int /*<<< orphan*/  pciedev_crwlpciegen2_180 (struct bcma_drv_pcie2*) ; 
 int /*<<< orphan*/  pciedev_crwlpciegen2_182 (struct bcma_drv_pcie2*) ; 
 int /*<<< orphan*/  pciedev_reg_pm_clk_period (struct bcma_drv_pcie2*) ; 

void bcma_core_pcie2_init(struct bcma_drv_pcie2 *pcie2)
{
	struct bcma_bus *bus = pcie2->core->bus;
	struct bcma_chipinfo *ci = &bus->chipinfo;
	u32 tmp;

	tmp = pcie2_read32(pcie2, BCMA_CORE_PCIE2_SPROM(54));
	if ((tmp & 0xe) >> 1 == 2)
		bcma_core_pcie2_cfg_write(pcie2, 0x4e0, 0x17);

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4360:
	case BCMA_CHIP_ID_BCM4352:
		pcie2->reqsize = 1024;
		break;
	default:
		pcie2->reqsize = 128;
		break;
	}

	if (ci->id == BCMA_CHIP_ID_BCM4360 && ci->rev > 3)
		bcma_core_pcie2_war_delay_perst_enab(pcie2, true);
	bcma_core_pcie2_hw_ltr_war(pcie2);
	pciedev_crwlpciegen2(pcie2);
	pciedev_reg_pm_clk_period(pcie2);
	pciedev_crwlpciegen2_180(pcie2);
	pciedev_crwlpciegen2_182(pcie2);
}