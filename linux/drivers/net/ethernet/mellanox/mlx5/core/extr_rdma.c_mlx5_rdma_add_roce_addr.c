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
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MLX5_ROCE_VERSION_1 ; 
 int mlx5_core_roce_gid_set (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_rdma_make_default_gid (struct mlx5_core_dev*,union ib_gid*) ; 

__attribute__((used)) static int mlx5_rdma_add_roce_addr(struct mlx5_core_dev *dev)
{
	union ib_gid gid;
	u8 mac[ETH_ALEN];

	mlx5_rdma_make_default_gid(dev, &gid);
	return mlx5_core_roce_gid_set(dev, 0,
				      MLX5_ROCE_VERSION_1,
				      0, gid.raw, mac,
				      false, 0, 1);
}