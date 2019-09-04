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
typedef  int u32 ;
struct bcma_drv_cc {TYPE_1__* core; } ;
struct TYPE_4__ {int id; } ;
struct bcma_bus {TYPE_2__ chipinfo; } ;
struct TYPE_3__ {struct bcma_bus* bus; } ;

/* Variables and functions */
#define  BCMA_CHIP_ID_BCM43142 128 
 int /*<<< orphan*/  bcma_pmu2_pll_init0 (struct bcma_drv_cc*,int) ; 
 int bcma_pmu_xtalfreq (struct bcma_drv_cc*) ; 

__attribute__((used)) static void bcma_pmu_pll_init(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;
	u32 xtalfreq = bcma_pmu_xtalfreq(cc);

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM43142:
		if (xtalfreq == 0)
			xtalfreq = 20000;
		bcma_pmu2_pll_init0(cc, xtalfreq);
		break;
	}
}