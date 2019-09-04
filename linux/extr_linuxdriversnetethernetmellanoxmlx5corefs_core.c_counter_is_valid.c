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
typedef  int u32 ;
struct mlx5_fc {int dummy; } ;

/* Variables and functions */
 int MLX5_FLOW_CONTEXT_ACTION_COUNT ; 
 int MLX5_FLOW_CONTEXT_ACTION_DROP ; 
 int MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 

__attribute__((used)) static bool counter_is_valid(struct mlx5_fc *counter, u32 action)
{
	if (!(action & MLX5_FLOW_CONTEXT_ACTION_COUNT))
		return !counter;

	if (!counter)
		return false;

	return (action & (MLX5_FLOW_CONTEXT_ACTION_DROP |
			  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST));
}