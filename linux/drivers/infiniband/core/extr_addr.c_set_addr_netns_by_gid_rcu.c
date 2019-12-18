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
struct rdma_dev_addr {int /*<<< orphan*/  bound_dev_if; int /*<<< orphan*/  net; int /*<<< orphan*/  sgid_attr; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct net_device*) ; 
 int PTR_ERR (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct net_device* rdma_read_gid_attr_ndev_rcu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_addr_netns_by_gid_rcu(struct rdma_dev_addr *addr)
{
	struct net_device *ndev;

	ndev = rdma_read_gid_attr_ndev_rcu(addr->sgid_attr);
	if (IS_ERR(ndev))
		return PTR_ERR(ndev);

	/*
	 * Since we are holding the rcu, reading net and ifindex
	 * are safe without any additional reference; because
	 * change_net_namespace() in net/core/dev.c does rcu sync
	 * after it changes the state to IFF_DOWN and before
	 * updating netdev fields {net, ifindex}.
	 */
	addr->net = dev_net(ndev);
	addr->bound_dev_if = ndev->ifindex;
	return 0;
}