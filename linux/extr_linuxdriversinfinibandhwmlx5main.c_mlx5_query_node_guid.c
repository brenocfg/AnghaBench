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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; int /*<<< orphan*/  ib_dev; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
#define  MLX5_VPORT_ACCESS_METHOD_HCA 130 
#define  MLX5_VPORT_ACCESS_METHOD_MAD 129 
#define  MLX5_VPORT_ACCESS_METHOD_NIC 128 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int mlx5_get_vport_access_method (int /*<<< orphan*/ *) ; 
 int mlx5_query_hca_vport_node_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5_query_mad_ifc_node_guid (struct mlx5_ib_dev*,int /*<<< orphan*/ *) ; 
 int mlx5_query_nic_vport_node_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_query_node_guid(struct mlx5_ib_dev *dev,
				__be64 *node_guid)
{
	u64 tmp;
	int err;

	switch (mlx5_get_vport_access_method(&dev->ib_dev)) {
	case MLX5_VPORT_ACCESS_METHOD_MAD:
		return mlx5_query_mad_ifc_node_guid(dev, node_guid);

	case MLX5_VPORT_ACCESS_METHOD_HCA:
		err = mlx5_query_hca_vport_node_guid(dev->mdev, &tmp);
		break;

	case MLX5_VPORT_ACCESS_METHOD_NIC:
		err = mlx5_query_nic_vport_node_guid(dev->mdev, &tmp);
		break;

	default:
		return -EINVAL;
	}

	if (!err)
		*node_guid = cpu_to_be64(tmp);

	return err;
}