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
struct rdma_netdev_alloc_params {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum rdma_netdev_t { ____Placeholder_rdma_netdev_t } rdma_netdev_t ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int RDMA_NETDEV_IPOIB ; 
 int mlx5_rdma_rn_get_params (int /*<<< orphan*/ ,struct ib_device*,struct rdma_netdev_alloc_params*) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mlx5_ib_rn_get_params(struct ib_device *device, u8 port_num,
				 enum rdma_netdev_t type,
				 struct rdma_netdev_alloc_params *params)
{
	if (type != RDMA_NETDEV_IPOIB)
		return -EOPNOTSUPP;

	return mlx5_rdma_rn_get_params(to_mdev(device)->mdev, device, params);
}