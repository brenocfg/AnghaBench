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
struct netvsc_device {int dummy; } ;
struct net_device_context {int /*<<< orphan*/  vf_netdev; int /*<<< orphan*/  nvdev; } ;
struct net_device {scalar_t__ addr_len; int /*<<< orphan*/  features; int /*<<< orphan*/  wanted_features; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int dev_change_net_namespace (struct net_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct net_device* get_netvsc_byslot (struct net_device*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 scalar_t__ netvsc_vf_join (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_device*) ; 
 struct netvsc_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netvsc_register_vf(struct net_device *vf_netdev)
{
	struct net_device_context *net_device_ctx;
	struct netvsc_device *netvsc_dev;
	struct net_device *ndev;
	int ret;

	if (vf_netdev->addr_len != ETH_ALEN)
		return NOTIFY_DONE;

	ndev = get_netvsc_byslot(vf_netdev);
	if (!ndev)
		return NOTIFY_DONE;

	net_device_ctx = netdev_priv(ndev);
	netvsc_dev = rtnl_dereference(net_device_ctx->nvdev);
	if (!netvsc_dev || rtnl_dereference(net_device_ctx->vf_netdev))
		return NOTIFY_DONE;

	/* if synthetic interface is a different namespace,
	 * then move the VF to that namespace; join will be
	 * done again in that context.
	 */
	if (!net_eq(dev_net(ndev), dev_net(vf_netdev))) {
		ret = dev_change_net_namespace(vf_netdev,
					       dev_net(ndev), "eth%d");
		if (ret)
			netdev_err(vf_netdev,
				   "could not move to same namespace as %s: %d\n",
				   ndev->name, ret);
		else
			netdev_info(vf_netdev,
				    "VF moved to namespace with: %s\n",
				    ndev->name);
		return NOTIFY_DONE;
	}

	netdev_info(ndev, "VF registering: %s\n", vf_netdev->name);

	if (netvsc_vf_join(vf_netdev, ndev) != 0)
		return NOTIFY_DONE;

	dev_hold(vf_netdev);
	rcu_assign_pointer(net_device_ctx->vf_netdev, vf_netdev);

	vf_netdev->wanted_features = ndev->features;
	netdev_update_features(vf_netdev);

	return NOTIFY_OK;
}