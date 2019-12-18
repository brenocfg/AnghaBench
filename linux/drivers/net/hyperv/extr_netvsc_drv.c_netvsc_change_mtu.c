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
struct netvsc_device_info {int dummy; } ;
struct netvsc_device {scalar_t__ destroy; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; int /*<<< orphan*/  vf_netdev; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int dev_set_mtu (struct net_device*,int) ; 
 int /*<<< orphan*/  kfree (struct netvsc_device_info*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int netvsc_attach (struct net_device*,struct netvsc_device_info*) ; 
 int netvsc_detach (struct net_device*,struct netvsc_device*) ; 
 struct netvsc_device_info* netvsc_devinfo_get (struct netvsc_device*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netvsc_change_mtu(struct net_device *ndev, int mtu)
{
	struct net_device_context *ndevctx = netdev_priv(ndev);
	struct net_device *vf_netdev = rtnl_dereference(ndevctx->vf_netdev);
	struct netvsc_device *nvdev = rtnl_dereference(ndevctx->nvdev);
	int orig_mtu = ndev->mtu;
	struct netvsc_device_info *device_info;
	int ret = 0;

	if (!nvdev || nvdev->destroy)
		return -ENODEV;

	device_info = netvsc_devinfo_get(nvdev);

	if (!device_info)
		return -ENOMEM;

	/* Change MTU of underlying VF netdev first. */
	if (vf_netdev) {
		ret = dev_set_mtu(vf_netdev, mtu);
		if (ret)
			goto out;
	}

	ret = netvsc_detach(ndev, nvdev);
	if (ret)
		goto rollback_vf;

	ndev->mtu = mtu;

	ret = netvsc_attach(ndev, device_info);
	if (!ret)
		goto out;

	/* Attempt rollback to original MTU */
	ndev->mtu = orig_mtu;

	if (netvsc_attach(ndev, device_info))
		netdev_err(ndev, "restoring mtu failed\n");
rollback_vf:
	if (vf_netdev)
		dev_set_mtu(vf_netdev, orig_mtu);

out:
	kfree(device_info);
	return ret;
}