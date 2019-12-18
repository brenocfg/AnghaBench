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
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct net_device {struct phy_device* phydev; } ;
struct TYPE_4__ {void* eth_tp_mdix; void* eth_tp_mdix_ctrl; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;

/* Variables and functions */
 void* ETH_TP_MDI ; 
 void* ETH_TP_MDI_AUTO ; 
 void* ETH_TP_MDI_INVALID ; 
 void* ETH_TP_MDI_X ; 
 int /*<<< orphan*/  HNS_PHY_CSC_REG ; 
 int /*<<< orphan*/  HNS_PHY_CSS_REG ; 
 int /*<<< orphan*/  HNS_PHY_PAGE_COPPER ; 
 int /*<<< orphan*/  HNS_PHY_PAGE_MDIX ; 
 int /*<<< orphan*/  HNS_PHY_PAGE_REG ; 
 int /*<<< orphan*/  PHY_MDIX_CTRL_M ; 
 int /*<<< orphan*/  PHY_MDIX_CTRL_S ; 
 int /*<<< orphan*/  PHY_MDIX_STATUS_B ; 
 int /*<<< orphan*/  PHY_SPEED_DUP_RESOLVE_B ; 
 int hnae_get_bit (int,int /*<<< orphan*/ ) ; 
 int hnae_get_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_get_mdix_mode(struct net_device *net_dev,
			      struct ethtool_link_ksettings *cmd)
{
	int mdix_ctrl, mdix, retval, is_resolved;
	struct phy_device *phy_dev = net_dev->phydev;

	if (!phy_dev || !phy_dev->mdio.bus) {
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_INVALID;
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
		return;
	}

	phy_write(phy_dev, HNS_PHY_PAGE_REG, HNS_PHY_PAGE_MDIX);

	retval = phy_read(phy_dev, HNS_PHY_CSC_REG);
	mdix_ctrl = hnae_get_field(retval, PHY_MDIX_CTRL_M, PHY_MDIX_CTRL_S);

	retval = phy_read(phy_dev, HNS_PHY_CSS_REG);
	mdix = hnae_get_bit(retval, PHY_MDIX_STATUS_B);
	is_resolved = hnae_get_bit(retval, PHY_SPEED_DUP_RESOLVE_B);

	phy_write(phy_dev, HNS_PHY_PAGE_REG, HNS_PHY_PAGE_COPPER);

	switch (mdix_ctrl) {
	case 0x0:
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI;
		break;
	case 0x1:
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_X;
		break;
	case 0x3:
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_AUTO;
		break;
	default:
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_INVALID;
		break;
	}

	if (!is_resolved)
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
	else if (mdix)
		cmd->base.eth_tp_mdix = ETH_TP_MDI_X;
	else
		cmd->base.eth_tp_mdix = ETH_TP_MDI;
}