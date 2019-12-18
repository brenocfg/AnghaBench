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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct hcp_ehea_port_cb4 {int port_speed; } ;
struct ehea_port {int autoneg; int full_duplex; scalar_t__ phy_link; int /*<<< orphan*/  netdev; void* port_speed; int /*<<< orphan*/  logical_port_id; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ EHEA_PHY_LINK_UP ; 
 void* EHEA_SPEED_100M ; 
 void* EHEA_SPEED_10G ; 
 void* EHEA_SPEED_10M ; 
 void* EHEA_SPEED_1G ; 
 scalar_t__ EHEA_SPEED_AUTONEG ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ H_AUTHORITY ; 
 int /*<<< orphan*/  H_PORT_CB4 ; 
 int /*<<< orphan*/  H_PORT_CB4_SPEED ; 
#define  H_SPEED_100M_F 133 
#define  H_SPEED_100M_H 132 
#define  H_SPEED_10G_F 131 
#define  H_SPEED_10M_F 130 
#define  H_SPEED_10M_H 129 
#define  H_SPEED_1G_F 128 
 scalar_t__ H_SUCCESS ; 
 scalar_t__ ehea_h_modify_ehea_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hcp_ehea_port_cb4*) ; 
 scalar_t__ ehea_h_query_ehea_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hcp_ehea_port_cb4*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  prop_carrier_state ; 

int ehea_set_portspeed(struct ehea_port *port, u32 port_speed)
{
	struct hcp_ehea_port_cb4 *cb4;
	u64 hret;
	int ret = 0;

	cb4 = (void *)get_zeroed_page(GFP_KERNEL);
	if (!cb4) {
		pr_err("no mem for cb4\n");
		ret = -ENOMEM;
		goto out;
	}

	cb4->port_speed = port_speed;

	netif_carrier_off(port->netdev);

	hret = ehea_h_modify_ehea_port(port->adapter->handle,
				       port->logical_port_id,
				       H_PORT_CB4, H_PORT_CB4_SPEED, cb4);
	if (hret == H_SUCCESS) {
		port->autoneg = port_speed == EHEA_SPEED_AUTONEG ? 1 : 0;

		hret = ehea_h_query_ehea_port(port->adapter->handle,
					      port->logical_port_id,
					      H_PORT_CB4, H_PORT_CB4_SPEED,
					      cb4);
		if (hret == H_SUCCESS) {
			switch (cb4->port_speed) {
			case H_SPEED_10M_H:
				port->port_speed = EHEA_SPEED_10M;
				port->full_duplex = 0;
				break;
			case H_SPEED_10M_F:
				port->port_speed = EHEA_SPEED_10M;
				port->full_duplex = 1;
				break;
			case H_SPEED_100M_H:
				port->port_speed = EHEA_SPEED_100M;
				port->full_duplex = 0;
				break;
			case H_SPEED_100M_F:
				port->port_speed = EHEA_SPEED_100M;
				port->full_duplex = 1;
				break;
			case H_SPEED_1G_F:
				port->port_speed = EHEA_SPEED_1G;
				port->full_duplex = 1;
				break;
			case H_SPEED_10G_F:
				port->port_speed = EHEA_SPEED_10G;
				port->full_duplex = 1;
				break;
			default:
				port->port_speed = 0;
				port->full_duplex = 0;
				break;
			}
		} else {
			pr_err("Failed sensing port speed\n");
			ret = -EIO;
		}
	} else {
		if (hret == H_AUTHORITY) {
			pr_info("Hypervisor denied setting port speed\n");
			ret = -EPERM;
		} else {
			ret = -EIO;
			pr_err("Failed setting port speed\n");
		}
	}
	if (!prop_carrier_state || (port->phy_link == EHEA_PHY_LINK_UP))
		netif_carrier_on(port->netdev);

	free_page((unsigned long)cb4);
out:
	return ret;
}