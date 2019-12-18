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
struct ocelot_port {int /*<<< orphan*/  phy; int /*<<< orphan*/  phy_mode; scalar_t__ serdes; int /*<<< orphan*/  chip_port; struct ocelot* ocelot; } ;
struct ocelot {int dummy; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_PORT_PORT_CFG ; 
 int ANA_PORT_PORT_CFG_LEARNAUTO ; 
 int ANA_PORT_PORT_CFG_PORTID_VAL (int /*<<< orphan*/ ) ; 
 int ANA_PORT_PORT_CFG_RECV_ENA ; 
 int /*<<< orphan*/  PHY_MODE_ETHERNET ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocelot_port_adjust_link ; 
 int /*<<< orphan*/  ocelot_write_gix (struct ocelot*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_info (int /*<<< orphan*/ ) ; 
 int phy_connect_direct (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int phy_set_mode_ext (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_port_open(struct net_device *dev)
{
	struct ocelot_port *port = netdev_priv(dev);
	struct ocelot *ocelot = port->ocelot;
	int err;

	/* Enable receiving frames on the port, and activate auto-learning of
	 * MAC addresses.
	 */
	ocelot_write_gix(ocelot, ANA_PORT_PORT_CFG_LEARNAUTO |
			 ANA_PORT_PORT_CFG_RECV_ENA |
			 ANA_PORT_PORT_CFG_PORTID_VAL(port->chip_port),
			 ANA_PORT_PORT_CFG, port->chip_port);

	if (port->serdes) {
		err = phy_set_mode_ext(port->serdes, PHY_MODE_ETHERNET,
				       port->phy_mode);
		if (err) {
			netdev_err(dev, "Could not set mode of SerDes\n");
			return err;
		}
	}

	err = phy_connect_direct(dev, port->phy, &ocelot_port_adjust_link,
				 port->phy_mode);
	if (err) {
		netdev_err(dev, "Could not attach to PHY\n");
		return err;
	}

	dev->phydev = port->phy;

	phy_attached_info(port->phy);
	phy_start(port->phy);
	return 0;
}