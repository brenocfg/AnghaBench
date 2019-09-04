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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_eth {int /*<<< orphan*/  dev; TYPE_1__* soc; int /*<<< orphan*/  ethsys; int /*<<< orphan*/  sgmiisys; } ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHSYS_SYSCFG0 ; 
 int MTK_DUAL_GMAC_SHARED_SGMII ; 
 int MTK_GMAC1_ESW ; 
 int MTK_GMAC1_SGMII ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MTK_MAC_MISC ; 
 int /*<<< orphan*/  SGMII_AN_RESTART ; 
 int /*<<< orphan*/  SGMII_LINK_TIMER_DEFAULT ; 
 int /*<<< orphan*/  SGMII_PHYA_PWD ; 
 int /*<<< orphan*/  SGMII_REMOTE_FAULT_DIS ; 
 int /*<<< orphan*/  SGMSYS_PCS_CONTROL_1 ; 
 int /*<<< orphan*/  SGMSYS_PCS_LINK_TIMER ; 
 int /*<<< orphan*/  SGMSYS_QPHY_PWR_STATE_CTRL ; 
 int /*<<< orphan*/  SGMSYS_SGMII_MODE ; 
 int /*<<< orphan*/  SYSCFG0_SGMII_GMAC1 ; 
 int /*<<< orphan*/  SYSCFG0_SGMII_GMAC2 ; 
 int /*<<< orphan*/  SYSCFG0_SGMII_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_gmac_sgmii_hw_setup(struct mtk_eth *eth, int mac_id)
{
	u32 val;

	/* Setup the link timer and QPHY power up inside SGMIISYS */
	regmap_write(eth->sgmiisys, SGMSYS_PCS_LINK_TIMER,
		     SGMII_LINK_TIMER_DEFAULT);

	regmap_read(eth->sgmiisys, SGMSYS_SGMII_MODE, &val);
	val |= SGMII_REMOTE_FAULT_DIS;
	regmap_write(eth->sgmiisys, SGMSYS_SGMII_MODE, val);

	regmap_read(eth->sgmiisys, SGMSYS_PCS_CONTROL_1, &val);
	val |= SGMII_AN_RESTART;
	regmap_write(eth->sgmiisys, SGMSYS_PCS_CONTROL_1, val);

	regmap_read(eth->sgmiisys, SGMSYS_QPHY_PWR_STATE_CTRL, &val);
	val &= ~SGMII_PHYA_PWD;
	regmap_write(eth->sgmiisys, SGMSYS_QPHY_PWR_STATE_CTRL, val);

	/* Determine MUX for which GMAC uses the SGMII interface */
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_DUAL_GMAC_SHARED_SGMII)) {
		regmap_read(eth->ethsys, ETHSYS_SYSCFG0, &val);
		val &= ~SYSCFG0_SGMII_MASK;
		val |= !mac_id ? SYSCFG0_SGMII_GMAC1 : SYSCFG0_SGMII_GMAC2;
		regmap_write(eth->ethsys, ETHSYS_SYSCFG0, val);

		dev_info(eth->dev, "setup shared sgmii for gmac=%d\n",
			 mac_id);
	}

	/* Setup the GMAC1 going through SGMII path when SoC also support
	 * ESW on GMAC1
	 */
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_GMAC1_ESW | MTK_GMAC1_SGMII) &&
	    !mac_id) {
		mtk_w32(eth, 0, MTK_MAC_MISC);
		dev_info(eth->dev, "setup gmac1 going through sgmii");
	}
}