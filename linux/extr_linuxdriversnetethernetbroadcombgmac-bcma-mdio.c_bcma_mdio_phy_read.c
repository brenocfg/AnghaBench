#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_8__ {struct bcma_device* core; } ;
struct bgmac {TYPE_4__ bcma; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct bcma_device {int /*<<< orphan*/  dev; TYPE_3__* bus; TYPE_1__ id; } ;
struct TYPE_6__ {struct bcma_device* core; } ;
struct TYPE_7__ {TYPE_2__ drv_gmac_cmn; } ;

/* Variables and functions */
 scalar_t__ BCMA_CORE_4706_MAC_GBIT ; 
 scalar_t__ BCMA_GMAC_CMN_PA_ADDR_MASK ; 
 int BCMA_GMAC_CMN_PA_ADDR_SHIFT ; 
 int BCMA_GMAC_CMN_PA_DATA_MASK ; 
 scalar_t__ BCMA_GMAC_CMN_PA_REG_MASK ; 
 int BCMA_GMAC_CMN_PA_REG_SHIFT ; 
 int BCMA_GMAC_CMN_PA_START ; 
 scalar_t__ BCMA_GMAC_CMN_PA_WRITE ; 
 int BCMA_GMAC_CMN_PC_EPA_MASK ; 
 scalar_t__ BCMA_GMAC_CMN_PC_MCT_MASK ; 
 scalar_t__ BCMA_GMAC_CMN_PC_MCT_SHIFT ; 
 scalar_t__ BCMA_GMAC_CMN_PC_MTE ; 
 int BCMA_GMAC_CMN_PHY_ACCESS ; 
 int BCMA_GMAC_CMN_PHY_CTL ; 
 scalar_t__ BGMAC_PA_ADDR_MASK ; 
 int BGMAC_PA_ADDR_SHIFT ; 
 int BGMAC_PA_DATA_MASK ; 
 scalar_t__ BGMAC_PA_REG_MASK ; 
 int BGMAC_PA_REG_SHIFT ; 
 int BGMAC_PA_START ; 
 scalar_t__ BGMAC_PA_WRITE ; 
 int BGMAC_PC_EPA_MASK ; 
 scalar_t__ BGMAC_PC_MCT_MASK ; 
 scalar_t__ BGMAC_PC_MCT_SHIFT ; 
 scalar_t__ BGMAC_PC_MTE ; 
 int BGMAC_PHY_ACCESS ; 
 int BGMAC_PHY_CNTL ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  bcma_mdio_wait_value (struct bcma_device*,int,int,int /*<<< orphan*/ ,int) ; 
 int bcma_read32 (struct bcma_device*,int) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static u16 bcma_mdio_phy_read(struct bgmac *bgmac, u8 phyaddr, u8 reg)
{
	struct bcma_device *core;
	u16 phy_access_addr;
	u16 phy_ctl_addr;
	u32 tmp;

	BUILD_BUG_ON(BGMAC_PA_DATA_MASK != BCMA_GMAC_CMN_PA_DATA_MASK);
	BUILD_BUG_ON(BGMAC_PA_ADDR_MASK != BCMA_GMAC_CMN_PA_ADDR_MASK);
	BUILD_BUG_ON(BGMAC_PA_ADDR_SHIFT != BCMA_GMAC_CMN_PA_ADDR_SHIFT);
	BUILD_BUG_ON(BGMAC_PA_REG_MASK != BCMA_GMAC_CMN_PA_REG_MASK);
	BUILD_BUG_ON(BGMAC_PA_REG_SHIFT != BCMA_GMAC_CMN_PA_REG_SHIFT);
	BUILD_BUG_ON(BGMAC_PA_WRITE != BCMA_GMAC_CMN_PA_WRITE);
	BUILD_BUG_ON(BGMAC_PA_START != BCMA_GMAC_CMN_PA_START);
	BUILD_BUG_ON(BGMAC_PC_EPA_MASK != BCMA_GMAC_CMN_PC_EPA_MASK);
	BUILD_BUG_ON(BGMAC_PC_MCT_MASK != BCMA_GMAC_CMN_PC_MCT_MASK);
	BUILD_BUG_ON(BGMAC_PC_MCT_SHIFT != BCMA_GMAC_CMN_PC_MCT_SHIFT);
	BUILD_BUG_ON(BGMAC_PC_MTE != BCMA_GMAC_CMN_PC_MTE);

	if (bgmac->bcma.core->id.id == BCMA_CORE_4706_MAC_GBIT) {
		core = bgmac->bcma.core->bus->drv_gmac_cmn.core;
		phy_access_addr = BCMA_GMAC_CMN_PHY_ACCESS;
		phy_ctl_addr = BCMA_GMAC_CMN_PHY_CTL;
	} else {
		core = bgmac->bcma.core;
		phy_access_addr = BGMAC_PHY_ACCESS;
		phy_ctl_addr = BGMAC_PHY_CNTL;
	}

	tmp = bcma_read32(core, phy_ctl_addr);
	tmp &= ~BGMAC_PC_EPA_MASK;
	tmp |= phyaddr;
	bcma_write32(core, phy_ctl_addr, tmp);

	tmp = BGMAC_PA_START;
	tmp |= phyaddr << BGMAC_PA_ADDR_SHIFT;
	tmp |= reg << BGMAC_PA_REG_SHIFT;
	bcma_write32(core, phy_access_addr, tmp);

	if (!bcma_mdio_wait_value(core, phy_access_addr, BGMAC_PA_START, 0,
				  1000)) {
		dev_err(&core->dev, "Reading PHY %d register 0x%X failed\n",
			phyaddr, reg);
		return 0xffff;
	}

	return bcma_read32(core, phy_access_addr) & BGMAC_PA_DATA_MASK;
}