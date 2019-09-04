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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct hcp_ehea_port_cb0 {int port_mac_addr; int port_speed; int num_default_qps; } ;
struct ehea_port {int mac_addr; int full_duplex; int autoneg; int num_mcs; int num_def_qps; void* port_speed; int /*<<< orphan*/  logical_port_id; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  EHEA_BMASK_SET (int /*<<< orphan*/ ,int) ; 
 void* EHEA_SPEED_100M ; 
 void* EHEA_SPEED_10G ; 
 void* EHEA_SPEED_10M ; 
 void* EHEA_SPEED_1G ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  H_PORT_CB0 ; 
 int /*<<< orphan*/  H_PORT_CB0_ALL ; 
#define  H_SPEED_100M_F 133 
#define  H_SPEED_100M_H 132 
#define  H_SPEED_10G_F 131 
#define  H_SPEED_10M_F 130 
#define  H_SPEED_10M_H 129 
#define  H_SPEED_1G_F 128 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  ehea_dump (struct hcp_ehea_port_cb0*,int,char*) ; 
 scalar_t__ ehea_h_query_ehea_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hcp_ehea_port_cb0*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_msg_probe (struct ehea_port*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ use_mcs ; 

int ehea_sense_port_attr(struct ehea_port *port)
{
	int ret;
	u64 hret;
	struct hcp_ehea_port_cb0 *cb0;

	/* may be called via ehea_neq_tasklet() */
	cb0 = (void *)get_zeroed_page(GFP_ATOMIC);
	if (!cb0) {
		pr_err("no mem for cb0\n");
		ret = -ENOMEM;
		goto out;
	}

	hret = ehea_h_query_ehea_port(port->adapter->handle,
				      port->logical_port_id, H_PORT_CB0,
				      EHEA_BMASK_SET(H_PORT_CB0_ALL, 0xFFFF),
				      cb0);
	if (hret != H_SUCCESS) {
		ret = -EIO;
		goto out_free;
	}

	/* MAC address */
	port->mac_addr = cb0->port_mac_addr << 16;

	if (!is_valid_ether_addr((u8 *)&port->mac_addr)) {
		ret = -EADDRNOTAVAIL;
		goto out_free;
	}

	/* Port speed */
	switch (cb0->port_speed) {
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

	port->autoneg = 1;
	port->num_mcs = cb0->num_default_qps;

	/* Number of default QPs */
	if (use_mcs)
		port->num_def_qps = cb0->num_default_qps;
	else
		port->num_def_qps = 1;

	if (!port->num_def_qps) {
		ret = -EINVAL;
		goto out_free;
	}

	ret = 0;
out_free:
	if (ret || netif_msg_probe(port))
		ehea_dump(cb0, sizeof(*cb0), "ehea_sense_port_attr");
	free_page((unsigned long)cb0);
out:
	return ret;
}