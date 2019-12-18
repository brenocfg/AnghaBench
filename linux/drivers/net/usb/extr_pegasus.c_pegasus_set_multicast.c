#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/ * eth_regs; } ;
typedef  TYPE_1__ pegasus_t ;

/* Variables and functions */
 size_t EthCtrl0 ; 
 size_t EthCtrl2 ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RX_MULTICAST ; 
 int /*<<< orphan*/  RX_PROMISCUOUS ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (TYPE_1__*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_info (TYPE_1__*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  update_eth_regs_async (TYPE_1__*) ; 

__attribute__((used)) static void pegasus_set_multicast(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);

	if (net->flags & IFF_PROMISC) {
		pegasus->eth_regs[EthCtrl2] |= RX_PROMISCUOUS;
		netif_info(pegasus, link, net, "Promiscuous mode enabled\n");
	} else if (!netdev_mc_empty(net) || (net->flags & IFF_ALLMULTI)) {
		pegasus->eth_regs[EthCtrl0] |= RX_MULTICAST;
		pegasus->eth_regs[EthCtrl2] &= ~RX_PROMISCUOUS;
		netif_dbg(pegasus, link, net, "set allmulti\n");
	} else {
		pegasus->eth_regs[EthCtrl0] &= ~RX_MULTICAST;
		pegasus->eth_regs[EthCtrl2] &= ~RX_PROMISCUOUS;
	}
	update_eth_regs_async(pegasus);
}