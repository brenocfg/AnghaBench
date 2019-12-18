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
struct net_device_context {int /*<<< orphan*/  nvdev; int /*<<< orphan*/  vf_netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netvsc_tx_disable (struct netvsc_device*,struct net_device*) ; 
 int netvsc_wait_until_empty (struct netvsc_device*) ; 
 int rndis_filter_close (struct netvsc_device*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netvsc_close(struct net_device *net)
{
	struct net_device_context *net_device_ctx = netdev_priv(net);
	struct net_device *vf_netdev
		= rtnl_dereference(net_device_ctx->vf_netdev);
	struct netvsc_device *nvdev = rtnl_dereference(net_device_ctx->nvdev);
	int ret;

	netvsc_tx_disable(nvdev, net);

	/* No need to close rndis filter if it is removed already */
	if (!nvdev)
		return 0;

	ret = rndis_filter_close(nvdev);
	if (ret != 0) {
		netdev_err(net, "unable to close device (ret %d).\n", ret);
		return ret;
	}

	ret = netvsc_wait_until_empty(nvdev);
	if (ret)
		netdev_err(net, "Ring buffer not empty after closing rndis\n");

	if (vf_netdev)
		dev_close(vf_netdev);

	return ret;
}