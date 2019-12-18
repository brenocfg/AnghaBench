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
struct netvsc_device {int dummy; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; int /*<<< orphan*/  vf_netdev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int dev_set_mac_address (struct net_device*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_commit_mac_addr_change (struct net_device*,void*) ; 
 int eth_prepare_mac_addr_change (struct net_device*,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int rndis_filter_set_device_mac (struct netvsc_device*,int /*<<< orphan*/ ) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netvsc_set_mac_addr(struct net_device *ndev, void *p)
{
	struct net_device_context *ndc = netdev_priv(ndev);
	struct net_device *vf_netdev = rtnl_dereference(ndc->vf_netdev);
	struct netvsc_device *nvdev = rtnl_dereference(ndc->nvdev);
	struct sockaddr *addr = p;
	int err;

	err = eth_prepare_mac_addr_change(ndev, p);
	if (err)
		return err;

	if (!nvdev)
		return -ENODEV;

	if (vf_netdev) {
		err = dev_set_mac_address(vf_netdev, addr, NULL);
		if (err)
			return err;
	}

	err = rndis_filter_set_device_mac(nvdev, addr->sa_data);
	if (!err) {
		eth_commit_mac_addr_change(ndev, p);
	} else if (vf_netdev) {
		/* rollback change on VF */
		memcpy(addr->sa_data, ndev->dev_addr, ETH_ALEN);
		dev_set_mac_address(vf_netdev, addr, NULL);
	}

	return err;
}