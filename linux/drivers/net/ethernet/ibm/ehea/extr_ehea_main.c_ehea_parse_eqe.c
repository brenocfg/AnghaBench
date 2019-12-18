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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ehea_port {int full_duplex; int /*<<< orphan*/  phy_link; int /*<<< orphan*/  port_speed; struct net_device* netdev; } ;
struct ehea_adapter {int dummy; } ;

/* Variables and functions */
 int EHEA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  EHEA_EC_ADAPTER_MALFUNC 130 
#define  EHEA_EC_PORTSTATE_CHG 129 
#define  EHEA_EC_PORT_MALFUNC 128 
 int /*<<< orphan*/  EHEA_PHY_LINK_DOWN ; 
 int /*<<< orphan*/  EHEA_PHY_LINK_UP ; 
 int /*<<< orphan*/  NEQE_EVENT_CODE ; 
 int /*<<< orphan*/  NEQE_EXTSWITCH_PORT_UP ; 
 int /*<<< orphan*/  NEQE_EXTSWITCH_PRIMARY ; 
 int /*<<< orphan*/  NEQE_PORTNUM ; 
 int /*<<< orphan*/  NEQE_PORT_UP ; 
 struct ehea_port* ehea_get_port (struct ehea_adapter*,int) ; 
 int ehea_sense_port_attr (struct ehea_port*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct ehea_port*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  prop_carrier_state ; 

__attribute__((used)) static void ehea_parse_eqe(struct ehea_adapter *adapter, u64 eqe)
{
	int ret;
	u8 ec;
	u8 portnum;
	struct ehea_port *port;
	struct net_device *dev;

	ec = EHEA_BMASK_GET(NEQE_EVENT_CODE, eqe);
	portnum = EHEA_BMASK_GET(NEQE_PORTNUM, eqe);
	port = ehea_get_port(adapter, portnum);
	if (!port) {
		netdev_err(NULL, "unknown portnum %x\n", portnum);
		return;
	}
	dev = port->netdev;

	switch (ec) {
	case EHEA_EC_PORTSTATE_CHG:	/* port state change */

		if (EHEA_BMASK_GET(NEQE_PORT_UP, eqe)) {
			if (!netif_carrier_ok(dev)) {
				ret = ehea_sense_port_attr(port);
				if (ret) {
					netdev_err(dev, "failed resensing port attributes\n");
					break;
				}

				netif_info(port, link, dev,
					   "Logical port up: %dMbps %s Duplex\n",
					   port->port_speed,
					   port->full_duplex == 1 ?
					   "Full" : "Half");

				netif_carrier_on(dev);
				netif_wake_queue(dev);
			}
		} else
			if (netif_carrier_ok(dev)) {
				netif_info(port, link, dev,
					   "Logical port down\n");
				netif_carrier_off(dev);
				netif_tx_disable(dev);
			}

		if (EHEA_BMASK_GET(NEQE_EXTSWITCH_PORT_UP, eqe)) {
			port->phy_link = EHEA_PHY_LINK_UP;
			netif_info(port, link, dev,
				   "Physical port up\n");
			if (prop_carrier_state)
				netif_carrier_on(dev);
		} else {
			port->phy_link = EHEA_PHY_LINK_DOWN;
			netif_info(port, link, dev,
				   "Physical port down\n");
			if (prop_carrier_state)
				netif_carrier_off(dev);
		}

		if (EHEA_BMASK_GET(NEQE_EXTSWITCH_PRIMARY, eqe))
			netdev_info(dev,
				    "External switch port is primary port\n");
		else
			netdev_info(dev,
				    "External switch port is backup port\n");

		break;
	case EHEA_EC_ADAPTER_MALFUNC:
		netdev_err(dev, "Adapter malfunction\n");
		break;
	case EHEA_EC_PORT_MALFUNC:
		netdev_info(dev, "Port malfunction\n");
		netif_carrier_off(dev);
		netif_tx_disable(dev);
		break;
	default:
		netdev_err(dev, "unknown event code %x, eqe=0x%llX\n", ec, eqe);
		break;
	}
}