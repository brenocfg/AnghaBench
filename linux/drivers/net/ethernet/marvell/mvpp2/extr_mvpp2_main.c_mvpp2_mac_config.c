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
struct phylink_link_state {scalar_t__ interface; } ;
struct phylink_config {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct mvpp2_port {scalar_t__ phy_interface; scalar_t__ gop_id; int flags; TYPE_1__* priv; int /*<<< orphan*/  comphy; } ;
struct TYPE_2__ {scalar_t__ hw_version; } ;

/* Variables and functions */
 scalar_t__ MVPP21 ; 
 scalar_t__ MVPP22 ; 
 int MVPP2_F_LOOPBACK ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  mvpp22_gop_mask_irq (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp22_gop_unmask_irq (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp22_mode_reconfigure (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_gmac_config (struct mvpp2_port*,unsigned int,struct phylink_link_state const*) ; 
 scalar_t__ mvpp2_is_xlg (scalar_t__) ; 
 int /*<<< orphan*/  mvpp2_port_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_port_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_port_loopback_set (struct mvpp2_port*,struct phylink_link_state const*) ; 
 int /*<<< orphan*/  mvpp2_xlg_config (struct mvpp2_port*,unsigned int,struct phylink_link_state const*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 scalar_t__ phy_interface_mode_is_8023z (scalar_t__) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct net_device* to_net_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_mac_config(struct phylink_config *config, unsigned int mode,
			     const struct phylink_link_state *state)
{
	struct net_device *dev = to_net_dev(config->dev);
	struct mvpp2_port *port = netdev_priv(dev);
	bool change_interface = port->phy_interface != state->interface;

	/* Check for invalid configuration */
	if (mvpp2_is_xlg(state->interface) && port->gop_id != 0) {
		netdev_err(dev, "Invalid mode on %s\n", dev->name);
		return;
	}

	/* Make sure the port is disabled when reconfiguring the mode */
	mvpp2_port_disable(port);

	if (port->priv->hw_version == MVPP22 && change_interface) {
		mvpp22_gop_mask_irq(port);

		port->phy_interface = state->interface;

		/* Reconfigure the serdes lanes */
		phy_power_off(port->comphy);
		mvpp22_mode_reconfigure(port);
	}

	/* mac (re)configuration */
	if (mvpp2_is_xlg(state->interface))
		mvpp2_xlg_config(port, mode, state);
	else if (phy_interface_mode_is_rgmii(state->interface) ||
		 phy_interface_mode_is_8023z(state->interface) ||
		 state->interface == PHY_INTERFACE_MODE_SGMII)
		mvpp2_gmac_config(port, mode, state);

	if (port->priv->hw_version == MVPP21 && port->flags & MVPP2_F_LOOPBACK)
		mvpp2_port_loopback_set(port, state);

	if (port->priv->hw_version == MVPP22 && change_interface)
		mvpp22_gop_unmask_irq(port);

	mvpp2_port_enable(port);
}