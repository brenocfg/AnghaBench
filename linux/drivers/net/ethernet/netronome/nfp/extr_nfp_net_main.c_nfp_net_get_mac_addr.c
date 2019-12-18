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
struct nfp_port {int dummy; } ;
struct nfp_pf {int dummy; } ;
struct nfp_eth_table_port {int /*<<< orphan*/  mac_addr; } ;
struct net_device {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 struct nfp_eth_table_port* __nfp_port_get_eth_port (struct nfp_port*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nfp_net_get_mac_addr(struct nfp_pf *pf, struct net_device *netdev,
		     struct nfp_port *port)
{
	struct nfp_eth_table_port *eth_port;

	eth_port = __nfp_port_get_eth_port(port);
	if (!eth_port) {
		eth_hw_addr_random(netdev);
		return;
	}

	ether_addr_copy(netdev->dev_addr, eth_port->mac_addr);
	ether_addr_copy(netdev->perm_addr, eth_port->mac_addr);
}