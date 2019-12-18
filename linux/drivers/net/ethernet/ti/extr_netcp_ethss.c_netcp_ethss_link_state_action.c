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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {scalar_t__ speed; } ;
struct net_device {int dummy; } ;
struct gbe_slave {scalar_t__ link_interface; int /*<<< orphan*/  port_num; scalar_t__ open; int /*<<< orphan*/  mac_control; struct phy_device* phy; } ;
struct gbe_priv {int /*<<< orphan*/  ale; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_PORT_STATE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_DISABLE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_FORWARD ; 
 int /*<<< orphan*/  GBE_REG_ADDR (struct gbe_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACSL_GIG_MODE ; 
 int /*<<< orphan*/  MACSL_XGIG_MODE ; 
 scalar_t__ RGMII_LINK_MAC_PHY ; 
 scalar_t__ SGMII_LINK_MAC_PHY ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_10000 ; 
 scalar_t__ XGMII_LINK_MAC_PHY ; 
 int /*<<< orphan*/  cpsw_ale_control_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_regs ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netcp_ethss_link_state_action(struct gbe_priv *gbe_dev,
					  struct net_device *ndev,
					  struct gbe_slave *slave,
					  int up)
{
	struct phy_device *phy = slave->phy;
	u32 mac_control = 0;

	if (up) {
		mac_control = slave->mac_control;
		if (phy && (phy->speed == SPEED_1000)) {
			mac_control |= MACSL_GIG_MODE;
			mac_control &= ~MACSL_XGIG_MODE;
		} else if (phy && (phy->speed == SPEED_10000)) {
			mac_control |= MACSL_XGIG_MODE;
			mac_control &= ~MACSL_GIG_MODE;
		}

		writel(mac_control, GBE_REG_ADDR(slave, emac_regs,
						 mac_control));

		cpsw_ale_control_set(gbe_dev->ale, slave->port_num,
				     ALE_PORT_STATE,
				     ALE_PORT_STATE_FORWARD);

		if (ndev && slave->open &&
		    ((slave->link_interface != SGMII_LINK_MAC_PHY) &&
		    (slave->link_interface != RGMII_LINK_MAC_PHY) &&
		    (slave->link_interface != XGMII_LINK_MAC_PHY)))
			netif_carrier_on(ndev);
	} else {
		writel(mac_control, GBE_REG_ADDR(slave, emac_regs,
						 mac_control));
		cpsw_ale_control_set(gbe_dev->ale, slave->port_num,
				     ALE_PORT_STATE,
				     ALE_PORT_STATE_DISABLE);
		if (ndev &&
		    ((slave->link_interface != SGMII_LINK_MAC_PHY) &&
		    (slave->link_interface != RGMII_LINK_MAC_PHY) &&
		    (slave->link_interface != XGMII_LINK_MAC_PHY)))
			netif_carrier_off(ndev);
	}

	if (phy)
		phy_print_status(phy);
}