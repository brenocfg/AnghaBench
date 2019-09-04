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
struct net_device {int /*<<< orphan*/  name; } ;
struct mvpp2_port {scalar_t__ gop_id; scalar_t__ phy_interface; int flags; TYPE_1__* priv; int /*<<< orphan*/  comphy; } ;
struct TYPE_2__ {scalar_t__ hw_version; } ;

/* Variables and functions */
 scalar_t__ MVPP21 ; 
 scalar_t__ MVPP22 ; 
 int MVPP2_F_LOOPBACK ; 
 scalar_t__ PHY_INTERFACE_MODE_1000BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_10GKR ; 
 scalar_t__ PHY_INTERFACE_MODE_2500BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  mvpp22_mode_reconfigure (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_gmac_config (struct mvpp2_port*,unsigned int,struct phylink_link_state const*) ; 
 int /*<<< orphan*/  mvpp2_port_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_port_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_port_loopback_set (struct mvpp2_port*,struct phylink_link_state const*) ; 
 int /*<<< orphan*/  mvpp2_xlg_config (struct mvpp2_port*,unsigned int,struct phylink_link_state const*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_mac_config(struct net_device *dev, unsigned int mode,
			     const struct phylink_link_state *state)
{
	struct mvpp2_port *port = netdev_priv(dev);

	/* Check for invalid configuration */
	if (state->interface == PHY_INTERFACE_MODE_10GKR && port->gop_id != 0) {
		netdev_err(dev, "Invalid mode on %s\n", dev->name);
		return;
	}

	/* Make sure the port is disabled when reconfiguring the mode */
	mvpp2_port_disable(port);

	if (port->priv->hw_version == MVPP22 &&
	    port->phy_interface != state->interface) {
		port->phy_interface = state->interface;

		/* Reconfigure the serdes lanes */
		phy_power_off(port->comphy);
		mvpp22_mode_reconfigure(port);
	}

	/* mac (re)configuration */
	if (state->interface == PHY_INTERFACE_MODE_10GKR)
		mvpp2_xlg_config(port, mode, state);
	else if (phy_interface_mode_is_rgmii(state->interface) ||
		 state->interface == PHY_INTERFACE_MODE_SGMII ||
		 state->interface == PHY_INTERFACE_MODE_1000BASEX ||
		 state->interface == PHY_INTERFACE_MODE_2500BASEX)
		mvpp2_gmac_config(port, mode, state);

	if (port->priv->hw_version == MVPP21 && port->flags & MVPP2_F_LOOPBACK)
		mvpp2_port_loopback_set(port, state);

	mvpp2_port_enable(port);
}