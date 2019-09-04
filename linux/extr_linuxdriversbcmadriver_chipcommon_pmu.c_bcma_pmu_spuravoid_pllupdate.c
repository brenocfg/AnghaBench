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
typedef  int u32 ;
struct bcma_drv_cc {TYPE_1__* core; } ;
struct TYPE_4__ {int id; } ;
struct bcma_bus {TYPE_2__ chipinfo; } ;
struct TYPE_3__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int BCMA_CC_PMU1_PLL0_PC0_P1DIV_MASK ; 
 int BCMA_CC_PMU1_PLL0_PC0_P1DIV_SHIFT ; 
 int BCMA_CC_PMU1_PLL0_PC2_NDIV_INT_MASK ; 
 int BCMA_CC_PMU1_PLL0_PC2_NDIV_INT_SHIFT ; 
 int /*<<< orphan*/  BCMA_CC_PMU_CTL ; 
 int BCMA_CC_PMU_CTL_NOILPONW ; 
 int BCMA_CC_PMU_CTL_PLL_UPD ; 
 int /*<<< orphan*/  BCMA_CC_PMU_PLLCTL_ADDR ; 
 int /*<<< orphan*/  BCMA_CC_PMU_PLLCTL_DATA ; 
 int BCMA_CC_PMU_PLL_CTL0 ; 
 int BCMA_CC_PMU_PLL_CTL1 ; 
 int BCMA_CC_PMU_PLL_CTL2 ; 
 int BCMA_CC_PMU_PLL_CTL3 ; 
 int BCMA_CC_PMU_PLL_CTL4 ; 
 int BCMA_CC_PMU_PLL_CTL5 ; 
#define  BCMA_CHIP_ID_BCM43131 143 
#define  BCMA_CHIP_ID_BCM43217 142 
#define  BCMA_CHIP_ID_BCM43224 141 
#define  BCMA_CHIP_ID_BCM43225 140 
#define  BCMA_CHIP_ID_BCM43227 139 
#define  BCMA_CHIP_ID_BCM43228 138 
#define  BCMA_CHIP_ID_BCM4331 137 
#define  BCMA_CHIP_ID_BCM43421 136 
#define  BCMA_CHIP_ID_BCM43428 135 
#define  BCMA_CHIP_ID_BCM43431 134 
#define  BCMA_CHIP_ID_BCM4716 133 
#define  BCMA_CHIP_ID_BCM47162 132 
#define  BCMA_CHIP_ID_BCM4748 131 
#define  BCMA_CHIP_ID_BCM4749 130 
#define  BCMA_CHIP_ID_BCM5357 129 
#define  BCMA_CHIP_ID_BCM53572 128 
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*,int const) ; 
 int bcma_pmu_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_pmu_spuravoid_pll_write (struct bcma_drv_cc*,int,int) ; 
 int /*<<< orphan*/  bcma_pmu_write32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int) ; 

void bcma_pmu_spuravoid_pllupdate(struct bcma_drv_cc *cc, int spuravoid)
{
	u32 tmp = 0;
	u8 phypll_offset = 0;
	u8 bcm5357_bcm43236_p1div[] = {0x1, 0x5, 0x5};
	u8 bcm5357_bcm43236_ndiv[] = {0x30, 0xf6, 0xfc};
	struct bcma_bus *bus = cc->core->bus;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM4749:
	case BCMA_CHIP_ID_BCM53572:
		/* 5357[ab]0, 43236[ab]0, and 6362b0 */

		/* BCM5357 needs to touch PLL1_PLLCTL[02],
		   so offset PLL0_PLLCTL[02] by 6 */
		phypll_offset = (bus->chipinfo.id == BCMA_CHIP_ID_BCM5357 ||
		       bus->chipinfo.id == BCMA_CHIP_ID_BCM4749 ||
		       bus->chipinfo.id == BCMA_CHIP_ID_BCM53572) ? 6 : 0;

		/* RMW only the P1 divider */
		bcma_pmu_write32(cc, BCMA_CC_PMU_PLLCTL_ADDR,
				BCMA_CC_PMU_PLL_CTL0 + phypll_offset);
		tmp = bcma_pmu_read32(cc, BCMA_CC_PMU_PLLCTL_DATA);
		tmp &= (~(BCMA_CC_PMU1_PLL0_PC0_P1DIV_MASK));
		tmp |= (bcm5357_bcm43236_p1div[spuravoid] << BCMA_CC_PMU1_PLL0_PC0_P1DIV_SHIFT);
		bcma_pmu_write32(cc, BCMA_CC_PMU_PLLCTL_DATA, tmp);

		/* RMW only the int feedback divider */
		bcma_pmu_write32(cc, BCMA_CC_PMU_PLLCTL_ADDR,
				BCMA_CC_PMU_PLL_CTL2 + phypll_offset);
		tmp = bcma_pmu_read32(cc, BCMA_CC_PMU_PLLCTL_DATA);
		tmp &= ~(BCMA_CC_PMU1_PLL0_PC2_NDIV_INT_MASK);
		tmp |= (bcm5357_bcm43236_ndiv[spuravoid]) << BCMA_CC_PMU1_PLL0_PC2_NDIV_INT_SHIFT;
		bcma_pmu_write32(cc, BCMA_CC_PMU_PLLCTL_DATA, tmp);

		tmp = BCMA_CC_PMU_CTL_PLL_UPD;
		break;

	case BCMA_CHIP_ID_BCM4331:
	case BCMA_CHIP_ID_BCM43431:
		if (spuravoid == 2) {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11500014);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x0FC00a08);
		} else if (spuravoid == 1) {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11500014);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x0F600a08);
		} else {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11100014);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03000a08);
		}
		tmp = BCMA_CC_PMU_CTL_PLL_UPD;
		break;

	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43225:
	case BCMA_CHIP_ID_BCM43421:
		if (spuravoid == 1) {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11500010);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x000C0C06);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x0F600a08);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x2001E920);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		} else {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11100010);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x000c0c06);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03000a08);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x200005c0);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		}
		tmp = BCMA_CC_PMU_CTL_PLL_UPD;
		break;

	case BCMA_CHIP_ID_BCM4716:
	case BCMA_CHIP_ID_BCM4748:
	case BCMA_CHIP_ID_BCM47162:
		if (spuravoid == 1) {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11500060);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x080C0C06);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x0F600000);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x2001E924);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		} else {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11100060);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x080c0c06);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03000000);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x200005c0);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		}

		tmp = BCMA_CC_PMU_CTL_PLL_UPD | BCMA_CC_PMU_CTL_NOILPONW;
		break;

	case BCMA_CHIP_ID_BCM43131:
	case BCMA_CHIP_ID_BCM43217:
	case BCMA_CHIP_ID_BCM43227:
	case BCMA_CHIP_ID_BCM43228:
	case BCMA_CHIP_ID_BCM43428:
		/* LCNXN */
		/* PLL Settings for spur avoidance on/off mode,
		   no on2 support for 43228A0 */
		if (spuravoid == 1) {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x01100014);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x040C0C06);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03140A08);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00333333);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x202C2820);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		} else {
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11100014);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x040c0c06);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03000a08);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x200005c0);
			bcma_pmu_spuravoid_pll_write(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		}
		tmp = BCMA_CC_PMU_CTL_PLL_UPD;
		break;
	default:
		bcma_err(bus, "Unknown spuravoidance settings for chip 0x%04X, not changing PLL\n",
			 bus->chipinfo.id);
		break;
	}

	tmp |= bcma_pmu_read32(cc, BCMA_CC_PMU_CTL);
	bcma_pmu_write32(cc, BCMA_CC_PMU_CTL, tmp);
}