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
struct rdma_netdev {struct ib_device* hca; int /*<<< orphan*/  detach_mcast; int /*<<< orphan*/  attach_mcast; int /*<<< orphan*/  send; } ;
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 struct net_device* alloc_netdev (int,char const*,unsigned char,void (*) (struct net_device*)) ; 
 int /*<<< orphan*/  ipoib_mcast_attach ; 
 int /*<<< orphan*/  ipoib_mcast_detach ; 
 int /*<<< orphan*/  ipoib_netdev_default_pf ; 
 int /*<<< orphan*/  ipoib_send ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device
*ipoib_create_netdev_default(struct ib_device *hca,
			     const char *name,
			     unsigned char name_assign_type,
			     void (*setup)(struct net_device *))
{
	struct net_device *dev;
	struct rdma_netdev *rn;

	dev = alloc_netdev((int)sizeof(struct rdma_netdev),
			   name,
			   name_assign_type, setup);
	if (!dev)
		return NULL;

	rn = netdev_priv(dev);

	rn->send = ipoib_send;
	rn->attach_mcast = ipoib_mcast_attach;
	rn->detach_mcast = ipoib_mcast_detach;
	rn->hca = hca;
	dev->netdev_ops = &ipoib_netdev_default_pf;

	return dev;
}