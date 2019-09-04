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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_gid_attr {scalar_t__ gid_type; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 int /*<<< orphan*/  MLX5_CAP_ROCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_roce_min_src_udp_port ; 

__be16 mlx5_get_roce_udp_sport(struct mlx5_ib_dev *dev,
			       const struct ib_gid_attr *attr)
{
	if (attr->gid_type != IB_GID_TYPE_ROCE_UDP_ENCAP)
		return 0;

	return cpu_to_be16(MLX5_CAP_ROCE(dev->mdev, r_roce_min_src_udp_port));
}