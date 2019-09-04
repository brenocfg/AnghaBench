#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int rev; } ;
struct bcma_drv_cc {TYPE_2__ pmu; TYPE_1__* core; } ;
struct TYPE_6__ {int id; } ;
struct bcma_bus {TYPE_3__ chipinfo; } ;
struct TYPE_4__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_PMU4706_MAINPLL_PLL0 ; 
 int BCMA_CC_PMU4716_MAINPLL_PLL0 ; 
 int BCMA_CC_PMU5356_MAINPLL_PLL0 ; 
 int BCMA_CC_PMU5357_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BCMA_CC_PMU5_MAINPLL_CPU ; 
#define  BCMA_CHIP_ID_BCM4706 131 
#define  BCMA_CHIP_ID_BCM4749 130 
#define  BCMA_CHIP_ID_BCM5356 129 
#define  BCMA_CHIP_ID_BCM5357 128 
 int BCMA_CHIP_ID_BCM53572 ; 
 int bcma_pmu_get_bus_clock (struct bcma_drv_cc*) ; 
 int bcma_pmu_pll_clock (struct bcma_drv_cc*,int,int /*<<< orphan*/ ) ; 
 int bcma_pmu_pll_clock_bcm4706 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 bcma_pmu_get_cpu_clock(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM53572)
		return 300000000;

	/* New PMUs can have different clock for bus and CPU */
	if (cc->pmu.rev >= 5) {
		u32 pll;
		switch (bus->chipinfo.id) {
		case BCMA_CHIP_ID_BCM4706:
			return bcma_pmu_pll_clock_bcm4706(cc,
						BCMA_CC_PMU4706_MAINPLL_PLL0,
						BCMA_CC_PMU5_MAINPLL_CPU);
		case BCMA_CHIP_ID_BCM5356:
			pll = BCMA_CC_PMU5356_MAINPLL_PLL0;
			break;
		case BCMA_CHIP_ID_BCM5357:
		case BCMA_CHIP_ID_BCM4749:
			pll = BCMA_CC_PMU5357_MAINPLL_PLL0;
			break;
		default:
			pll = BCMA_CC_PMU4716_MAINPLL_PLL0;
			break;
		}

		return bcma_pmu_pll_clock(cc, pll, BCMA_CC_PMU5_MAINPLL_CPU);
	}

	/* On old PMUs CPU has the same clock as the bus */
	return bcma_pmu_get_bus_clock(cc);
}