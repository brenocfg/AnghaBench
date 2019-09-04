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
typedef  enum mlx5_ib_dbg_cc_types { ____Placeholder_mlx5_ib_dbg_cc_types } mlx5_ib_dbg_cc_types ;
typedef  enum mlx5_ib_cong_node_type { ____Placeholder_mlx5_ib_cong_node_type } mlx5_ib_cong_node_type ;

/* Variables and functions */
 int MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE ; 
 int MLX5_IB_DBG_CC_RP_GD ; 
 int MLX5_IB_RROCE_ECN_NP ; 
 int MLX5_IB_RROCE_ECN_RP ; 

__attribute__((used)) static enum mlx5_ib_cong_node_type
mlx5_ib_param_to_node(enum mlx5_ib_dbg_cc_types param_offset)
{
	if (param_offset >= MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE &&
	    param_offset <= MLX5_IB_DBG_CC_RP_GD)
		return MLX5_IB_RROCE_ECN_RP;
	else
		return MLX5_IB_RROCE_ECN_NP;
}