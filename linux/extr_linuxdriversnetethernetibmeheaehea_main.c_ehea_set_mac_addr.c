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
struct sockaddr {int /*<<< orphan*/ * sa_data; } ;
struct net_device {int* dev_addr; int /*<<< orphan*/  addr_len; } ;
struct hcp_ehea_port_cb0 {int port_mac_addr; } ;
struct ehea_port {scalar_t__ state; int mac_addr; int /*<<< orphan*/  logical_port_id; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  EHEA_BMASK_SET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ EHEA_PORT_UP ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  H_DEREG_BCMC ; 
 int /*<<< orphan*/  H_PORT_CB0 ; 
 int /*<<< orphan*/  H_PORT_CB0_MAC ; 
 int /*<<< orphan*/  H_REG_BCMC ; 
 scalar_t__ H_SUCCESS ; 
 int ehea_broadcast_reg_helper (struct ehea_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ ehea_h_modify_ehea_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hcp_ehea_port_cb0*) ; 
 int /*<<< orphan*/  ehea_update_bcmc_registrations () ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ehea_set_mac_addr(struct net_device *dev, void *sa)
{
	struct ehea_port *port = netdev_priv(dev);
	struct sockaddr *mac_addr = sa;
	struct hcp_ehea_port_cb0 *cb0;
	int ret;
	u64 hret;

	if (!is_valid_ether_addr(mac_addr->sa_data)) {
		ret = -EADDRNOTAVAIL;
		goto out;
	}

	cb0 = (void *)get_zeroed_page(GFP_KERNEL);
	if (!cb0) {
		pr_err("no mem for cb0\n");
		ret = -ENOMEM;
		goto out;
	}

	memcpy(&(cb0->port_mac_addr), &(mac_addr->sa_data[0]), ETH_ALEN);

	cb0->port_mac_addr = cb0->port_mac_addr >> 16;

	hret = ehea_h_modify_ehea_port(port->adapter->handle,
				       port->logical_port_id, H_PORT_CB0,
				       EHEA_BMASK_SET(H_PORT_CB0_MAC, 1), cb0);
	if (hret != H_SUCCESS) {
		ret = -EIO;
		goto out_free;
	}

	memcpy(dev->dev_addr, mac_addr->sa_data, dev->addr_len);

	/* Deregister old MAC in pHYP */
	if (port->state == EHEA_PORT_UP) {
		ret = ehea_broadcast_reg_helper(port, H_DEREG_BCMC);
		if (ret)
			goto out_upregs;
	}

	port->mac_addr = cb0->port_mac_addr << 16;

	/* Register new MAC in pHYP */
	if (port->state == EHEA_PORT_UP) {
		ret = ehea_broadcast_reg_helper(port, H_REG_BCMC);
		if (ret)
			goto out_upregs;
	}

	ret = 0;

out_upregs:
	ehea_update_bcmc_registrations();
out_free:
	free_page((unsigned long)cb0);
out:
	return ret;
}