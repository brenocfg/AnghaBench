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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct nfp_net {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_MACADDR ; 
 int /*<<< orphan*/  eth_commit_mac_addr_change (struct net_device*,void*) ; 
 int eth_prepare_mac_addr_change (struct net_device*,void*) ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int nfp_net_reconfig (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_write_mac_addr (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_net_set_mac_address(struct net_device *netdev, void *addr)
{
	struct nfp_net *nn = netdev_priv(netdev);
	struct sockaddr *saddr = addr;
	int err;

	err = eth_prepare_mac_addr_change(netdev, addr);
	if (err)
		return err;

	nfp_net_write_mac_addr(nn, saddr->sa_data);

	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_MACADDR);
	if (err)
		return err;

	eth_commit_mac_addr_change(netdev, addr);

	return 0;
}