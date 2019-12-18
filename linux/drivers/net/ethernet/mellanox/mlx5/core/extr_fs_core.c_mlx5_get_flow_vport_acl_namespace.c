#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_steering {TYPE_1__** esw_ingress_root_ns; TYPE_3__** esw_egress_root_ns; } ;
struct mlx5_flow_namespace {int dummy; } ;
struct TYPE_5__ {struct mlx5_flow_steering* steering; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
typedef  enum mlx5_flow_namespace_type { ____Placeholder_mlx5_flow_namespace_type } mlx5_flow_namespace_type ;
struct TYPE_6__ {struct mlx5_flow_namespace ns; } ;
struct TYPE_4__ {struct mlx5_flow_namespace ns; } ;

/* Variables and functions */
#define  MLX5_FLOW_NAMESPACE_ESW_EGRESS 129 
#define  MLX5_FLOW_NAMESPACE_ESW_INGRESS 128 
 int mlx5_eswitch_get_total_vports (struct mlx5_core_dev*) ; 

struct mlx5_flow_namespace *mlx5_get_flow_vport_acl_namespace(struct mlx5_core_dev *dev,
							      enum mlx5_flow_namespace_type type,
							      int vport)
{
	struct mlx5_flow_steering *steering = dev->priv.steering;

	if (!steering || vport >= mlx5_eswitch_get_total_vports(dev))
		return NULL;

	switch (type) {
	case MLX5_FLOW_NAMESPACE_ESW_EGRESS:
		if (steering->esw_egress_root_ns &&
		    steering->esw_egress_root_ns[vport])
			return &steering->esw_egress_root_ns[vport]->ns;
		else
			return NULL;
	case MLX5_FLOW_NAMESPACE_ESW_INGRESS:
		if (steering->esw_ingress_root_ns &&
		    steering->esw_ingress_root_ns[vport])
			return &steering->esw_ingress_root_ns[vport]->ns;
		else
			return NULL;
	default:
		return NULL;
	}
}