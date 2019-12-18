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
struct gbe_slave {int port_num; scalar_t__ link_interface; scalar_t__ slave_num; int /*<<< orphan*/  phy; int /*<<< orphan*/  phy_node; void* phy_port_t; int /*<<< orphan*/  node; } ;
struct gbe_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  ale; int /*<<< orphan*/  rx_packet_max; } ;
struct gbe_intf {TYPE_1__* ndev; struct gbe_slave* slave; struct gbe_priv* gbe_dev; } ;
typedef  scalar_t__ phy_interface_t ;
struct TYPE_2__ {int /*<<< orphan*/  broadcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_MCAST_FWD_2 ; 
 int /*<<< orphan*/  ALE_PORT_STATE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_FORWARD ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GBE_REG_ADDR (struct gbe_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_TX_PRI_MAP_DEFAULT ; 
 int /*<<< orphan*/  IS_SS_ID_2U (struct gbe_priv*) ; 
 scalar_t__ IS_SS_ID_MU (struct gbe_priv*) ; 
 scalar_t__ IS_SS_ID_XGBE (struct gbe_priv*) ; 
 scalar_t__ PHY_INTERFACE_MODE_NA ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 void* PORT_FIBRE ; 
 void* PORT_MII ; 
 scalar_t__ RGMII_LINK_MAC_PHY ; 
 scalar_t__ SGMII_LINK_MAC_PHY ; 
 scalar_t__ XGMII_LINK_MAC_PHY ; 
 int /*<<< orphan*/  cpsw_ale_add_mcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_control_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 void gbe_adjust_link (struct net_device*) ; 
 int /*<<< orphan*/  gbe_port_config (struct gbe_priv*,struct gbe_slave*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbe_port_reset (struct gbe_slave*) ; 
 int /*<<< orphan*/  gbe_set_slave_mac (struct gbe_slave*,struct gbe_intf*) ; 
 int /*<<< orphan*/  gbe_sgmii_config (struct gbe_priv*,struct gbe_slave*) ; 
 int /*<<< orphan*/  gbe_sgmii_rtreset (struct gbe_priv*,struct gbe_slave*,int) ; 
 scalar_t__ of_get_phy_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_connect (TYPE_1__*,int /*<<< orphan*/ ,void (*) (struct net_device*),int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  phy_interface_mode_is_rgmii (scalar_t__) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_regs ; 
 int /*<<< orphan*/  rx_pri_map ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void xgbe_adjust_link (struct net_device*) ; 

__attribute__((used)) static int gbe_slave_open(struct gbe_intf *gbe_intf)
{
	struct gbe_priv *priv = gbe_intf->gbe_dev;
	struct gbe_slave *slave = gbe_intf->slave;
	phy_interface_t phy_mode;
	bool has_phy = false;

	void (*hndlr)(struct net_device *) = gbe_adjust_link;

	if (!IS_SS_ID_2U(priv))
		gbe_sgmii_config(priv, slave);
	gbe_port_reset(slave);
	if (!IS_SS_ID_2U(priv))
		gbe_sgmii_rtreset(priv, slave, false);
	gbe_port_config(priv, slave, priv->rx_packet_max);
	gbe_set_slave_mac(slave, gbe_intf);
	/* For NU & 2U switch, map the vlan priorities to zero
	 * as we only configure to use priority 0
	 */
	if (IS_SS_ID_MU(priv))
		writel(HOST_TX_PRI_MAP_DEFAULT,
		       GBE_REG_ADDR(slave, port_regs, rx_pri_map));

	/* enable forwarding */
	cpsw_ale_control_set(priv->ale, slave->port_num,
			     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);
	cpsw_ale_add_mcast(priv->ale, gbe_intf->ndev->broadcast,
			   1 << slave->port_num, 0, 0, ALE_MCAST_FWD_2);

	if (slave->link_interface == SGMII_LINK_MAC_PHY) {
		has_phy = true;
		phy_mode = PHY_INTERFACE_MODE_SGMII;
		slave->phy_port_t = PORT_MII;
	} else if (slave->link_interface == RGMII_LINK_MAC_PHY) {
		has_phy = true;
		phy_mode = of_get_phy_mode(slave->node);
		/* if phy-mode is not present, default to
		 * PHY_INTERFACE_MODE_RGMII
		 */
		if (phy_mode < 0)
			phy_mode = PHY_INTERFACE_MODE_RGMII;

		if (!phy_interface_mode_is_rgmii(phy_mode)) {
			dev_err(priv->dev,
				"Unsupported phy mode %d\n", phy_mode);
			return -EINVAL;
		}
		slave->phy_port_t = PORT_MII;
	} else if (slave->link_interface == XGMII_LINK_MAC_PHY) {
		has_phy = true;
		phy_mode = PHY_INTERFACE_MODE_NA;
		slave->phy_port_t = PORT_FIBRE;
	}

	if (has_phy) {
		if (IS_SS_ID_XGBE(priv))
			hndlr = xgbe_adjust_link;

		slave->phy = of_phy_connect(gbe_intf->ndev,
					    slave->phy_node,
					    hndlr, 0,
					    phy_mode);
		if (!slave->phy) {
			dev_err(priv->dev, "phy not found on slave %d\n",
				slave->slave_num);
			return -ENODEV;
		}
		dev_dbg(priv->dev, "phy found: id is: 0x%s\n",
			phydev_name(slave->phy));
		phy_start(slave->phy);
	}
	return 0;
}