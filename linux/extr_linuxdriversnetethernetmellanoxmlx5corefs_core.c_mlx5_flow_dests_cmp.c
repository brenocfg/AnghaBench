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
struct TYPE_2__ {scalar_t__ num; } ;
struct mlx5_flow_destination {scalar_t__ type; scalar_t__ ft; scalar_t__ tir_num; scalar_t__ ft_num; TYPE_1__ vport; } ;

/* Variables and functions */
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE ; 
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM ; 
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_TIR ; 
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_VPORT ; 

__attribute__((used)) static bool mlx5_flow_dests_cmp(struct mlx5_flow_destination *d1,
				struct mlx5_flow_destination *d2)
{
	if (d1->type == d2->type) {
		if ((d1->type == MLX5_FLOW_DESTINATION_TYPE_VPORT &&
		     d1->vport.num == d2->vport.num) ||
		    (d1->type == MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE &&
		     d1->ft == d2->ft) ||
		    (d1->type == MLX5_FLOW_DESTINATION_TYPE_TIR &&
		     d1->tir_num == d2->tir_num) ||
		    (d1->type == MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM &&
		     d1->ft_num == d2->ft_num))
			return true;
	}

	return false;
}