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
typedef  enum mlx5_ib_uapi_flow_table_type { ____Placeholder_mlx5_ib_uapi_flow_table_type } mlx5_ib_uapi_flow_table_type ;
typedef  enum mlx5_flow_namespace_type { ____Placeholder_mlx5_flow_namespace_type } mlx5_flow_namespace_type ;

/* Variables and functions */
 int EINVAL ; 
 int MLX5_FLOW_NAMESPACE_BYPASS ; 
 int MLX5_FLOW_NAMESPACE_EGRESS ; 
 int MLX5_FLOW_NAMESPACE_FDB ; 
 int MLX5_FLOW_NAMESPACE_RDMA_RX ; 
#define  MLX5_IB_UAPI_FLOW_TABLE_TYPE_FDB 131 
#define  MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX 130 
#define  MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX 129 
#define  MLX5_IB_UAPI_FLOW_TABLE_TYPE_RDMA_RX 128 

__attribute__((used)) static int
mlx5_ib_ft_type_to_namespace(enum mlx5_ib_uapi_flow_table_type table_type,
			     enum mlx5_flow_namespace_type *namespace)
{
	switch (table_type) {
	case MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX:
		*namespace = MLX5_FLOW_NAMESPACE_BYPASS;
		break;
	case MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX:
		*namespace = MLX5_FLOW_NAMESPACE_EGRESS;
		break;
	case MLX5_IB_UAPI_FLOW_TABLE_TYPE_FDB:
		*namespace = MLX5_FLOW_NAMESPACE_FDB;
		break;
	case MLX5_IB_UAPI_FLOW_TABLE_TYPE_RDMA_RX:
		*namespace = MLX5_FLOW_NAMESPACE_RDMA_RX;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}