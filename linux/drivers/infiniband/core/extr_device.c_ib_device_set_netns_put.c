#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct TYPE_4__ {scalar_t__ init_port; int /*<<< orphan*/  disassociate_ucontext; } ;
struct ib_device {int /*<<< orphan*/  dev; TYPE_1__ ops; } ;
struct TYPE_6__ {TYPE_2__* nsproxy; } ;
struct TYPE_5__ {int /*<<< orphan*/  net_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct net*) ; 
 int PTR_ERR (struct net*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 struct net* get_net_ns_by_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 scalar_t__ ib_devices_shared_netns ; 
 int /*<<< orphan*/  netlink_ns_capable (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int rdma_dev_change_netns (struct ib_device*,int /*<<< orphan*/ ,struct net*) ; 

int ib_device_set_netns_put(struct sk_buff *skb,
			    struct ib_device *dev, u32 ns_fd)
{
	struct net *net;
	int ret;

	net = get_net_ns_by_fd(ns_fd);
	if (IS_ERR(net)) {
		ret = PTR_ERR(net);
		goto net_err;
	}

	if (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN)) {
		ret = -EPERM;
		goto ns_err;
	}

	/*
	 * Currently supported only for those providers which support
	 * disassociation and don't do port specific sysfs init. Once a
	 * port_cleanup infrastructure is implemented, this limitation will be
	 * removed.
	 */
	if (!dev->ops.disassociate_ucontext || dev->ops.init_port ||
	    ib_devices_shared_netns) {
		ret = -EOPNOTSUPP;
		goto ns_err;
	}

	get_device(&dev->dev);
	ib_device_put(dev);
	ret = rdma_dev_change_netns(dev, current->nsproxy->net_ns, net);
	put_device(&dev->dev);

	put_net(net);
	return ret;

ns_err:
	put_net(net);
net_err:
	ib_device_put(dev);
	return ret;
}