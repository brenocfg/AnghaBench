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
struct emac_sgmii {scalar_t__ base; } ;
struct emac_adapter {struct emac_sgmii phy; } ;

/* Variables and functions */
 int AN_ENABLE ; 
 scalar_t__ EMAC_SGMII_PHY_AUTONEG_CFG2 ; 
 int FORCE_AN_RX_CFG ; 
 int FORCE_AN_TX_CFG ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void emac_sgmii_link_init(struct emac_adapter *adpt)
{
	struct emac_sgmii *phy = &adpt->phy;
	u32 val;

	/* Always use autonegotiation. It works no matter how the external
	 * PHY is configured.
	 */
	val = readl(phy->base + EMAC_SGMII_PHY_AUTONEG_CFG2);
	val &= ~(FORCE_AN_RX_CFG | FORCE_AN_TX_CFG);
	val |= AN_ENABLE;
	writel(val, phy->base + EMAC_SGMII_PHY_AUTONEG_CFG2);
}