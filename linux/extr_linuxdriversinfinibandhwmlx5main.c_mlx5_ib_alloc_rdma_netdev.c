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
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum rdma_netdev_t { ____Placeholder_rdma_netdev_t } rdma_netdev_t ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int RDMA_NETDEV_IPOIB ; 
 struct net_device* mlx5_rdma_netdev_alloc (int /*<<< orphan*/ ,struct ib_device*,char const*,void (*) (struct net_device*)) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct net_device*
mlx5_ib_alloc_rdma_netdev(struct ib_device *hca,
			  u8 port_num,
			  enum rdma_netdev_t type,
			  const char *name,
			  unsigned char name_assign_type,
			  void (*setup)(struct net_device *))
{
	struct net_device *netdev;

	if (type != RDMA_NETDEV_IPOIB)
		return ERR_PTR(-EOPNOTSUPP);

	netdev = mlx5_rdma_netdev_alloc(to_mdev(hca)->mdev, hca,
					name, setup);
	return netdev;
}