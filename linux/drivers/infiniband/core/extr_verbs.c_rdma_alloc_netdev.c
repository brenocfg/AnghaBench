#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rdma_netdev_alloc_params {int /*<<< orphan*/  rxqs; int /*<<< orphan*/  txqs; int /*<<< orphan*/  sizeof_priv; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int (* rdma_netdev_get_params ) (struct ib_device*,int /*<<< orphan*/ ,int,struct rdma_netdev_alloc_params*) ;} ;
struct ib_device {TYPE_1__ ops; } ;
typedef  enum rdma_netdev_t { ____Placeholder_rdma_netdev_t } rdma_netdev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct net_device* ERR_PTR (int) ; 
 struct net_device* alloc_netdev_mqs (int /*<<< orphan*/ ,char const*,unsigned char,void (*) (struct net_device*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_device*,int /*<<< orphan*/ ,int,struct rdma_netdev_alloc_params*) ; 

struct net_device *rdma_alloc_netdev(struct ib_device *device, u8 port_num,
				     enum rdma_netdev_t type, const char *name,
				     unsigned char name_assign_type,
				     void (*setup)(struct net_device *))
{
	struct rdma_netdev_alloc_params params;
	struct net_device *netdev;
	int rc;

	if (!device->ops.rdma_netdev_get_params)
		return ERR_PTR(-EOPNOTSUPP);

	rc = device->ops.rdma_netdev_get_params(device, port_num, type,
						&params);
	if (rc)
		return ERR_PTR(rc);

	netdev = alloc_netdev_mqs(params.sizeof_priv, name, name_assign_type,
				  setup, params.txqs, params.rxqs);
	if (!netdev)
		return ERR_PTR(-ENOMEM);

	return netdev;
}