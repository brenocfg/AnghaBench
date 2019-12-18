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
struct net_device {int dummy; } ;
struct enetc_ndev_priv {TYPE_1__* si; } ;
struct enetc_hw {int dummy; } ;
struct TYPE_2__ {struct enetc_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_PM0_CMD_CFG ; 
 int ENETC_PM0_CMD_PHY_TX_EN ; 
 int ENETC_PM0_CMD_XGLP ; 
 int ENETC_PM0_IFM_RLP ; 
 int /*<<< orphan*/  ENETC_PM0_IF_MODE ; 
 int /*<<< orphan*/  ENETC_PM1_CMD_CFG ; 
 int ENETC_PMO_IFM_RG ; 
 int enetc_port_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_port_wr (struct enetc_hw*,int /*<<< orphan*/ ,int) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void enetc_set_loopback(struct net_device *ndev, bool en)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct enetc_hw *hw = &priv->si->hw;
	u32 reg;

	reg = enetc_port_rd(hw, ENETC_PM0_IF_MODE);
	if (reg & ENETC_PMO_IFM_RG) {
		/* RGMII mode */
		reg = (reg & ~ENETC_PM0_IFM_RLP) |
		      (en ? ENETC_PM0_IFM_RLP : 0);
		enetc_port_wr(hw, ENETC_PM0_IF_MODE, reg);
	} else {
		/* assume SGMII mode */
		reg = enetc_port_rd(hw, ENETC_PM0_CMD_CFG);
		reg = (reg & ~ENETC_PM0_CMD_XGLP) |
		      (en ? ENETC_PM0_CMD_XGLP : 0);
		reg = (reg & ~ENETC_PM0_CMD_PHY_TX_EN) |
		      (en ? ENETC_PM0_CMD_PHY_TX_EN : 0);
		enetc_port_wr(hw, ENETC_PM0_CMD_CFG, reg);
		enetc_port_wr(hw, ENETC_PM1_CMD_CFG, reg);
	}
}