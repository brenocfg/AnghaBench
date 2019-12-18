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
typedef  int u32 ;
struct mlx5_flow_table {scalar_t__ level; } ;
struct mlx5_flow_destination {scalar_t__ type; TYPE_1__* ft; } ;
struct TYPE_2__ {scalar_t__ level; } ;

/* Variables and functions */
 int MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_COUNTER ; 
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE ; 
 int counter_is_valid (int) ; 

__attribute__((used)) static bool dest_is_valid(struct mlx5_flow_destination *dest,
			  u32 action,
			  struct mlx5_flow_table *ft)
{
	if (dest && (dest->type == MLX5_FLOW_DESTINATION_TYPE_COUNTER))
		return counter_is_valid(action);

	if (!(action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST))
		return true;

	if (!dest || ((dest->type ==
	    MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE) &&
	    (dest->ft->level <= ft->level)))
		return false;
	return true;
}