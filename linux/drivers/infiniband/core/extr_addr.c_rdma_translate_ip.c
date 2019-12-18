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
struct sockaddr {int dummy; } ;
struct rdma_dev_addr {int /*<<< orphan*/  net; scalar_t__ bound_dev_if; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IS_ERR (struct net_device*) ; 
 int PTR_ERR_OR_ZERO (struct net_device*) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdma_copy_src_l2_addr (struct rdma_dev_addr*,struct net_device*) ; 
 struct net_device* rdma_find_ndev_for_src_ip_rcu (int /*<<< orphan*/ ,struct sockaddr const*) ; 

int rdma_translate_ip(const struct sockaddr *addr,
		      struct rdma_dev_addr *dev_addr)
{
	struct net_device *dev;

	if (dev_addr->bound_dev_if) {
		dev = dev_get_by_index(dev_addr->net, dev_addr->bound_dev_if);
		if (!dev)
			return -ENODEV;
		rdma_copy_src_l2_addr(dev_addr, dev);
		dev_put(dev);
		return 0;
	}

	rcu_read_lock();
	dev = rdma_find_ndev_for_src_ip_rcu(dev_addr->net, addr);
	if (!IS_ERR(dev))
		rdma_copy_src_l2_addr(dev_addr, dev);
	rcu_read_unlock();
	return PTR_ERR_OR_ZERO(dev);
}