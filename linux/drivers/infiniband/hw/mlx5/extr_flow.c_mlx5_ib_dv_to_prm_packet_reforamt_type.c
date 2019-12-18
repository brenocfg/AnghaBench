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
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 
#define  MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L2_TUNNEL 130 
#define  MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L3_TUNNEL 129 
#define  MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L3_TUNNEL_TO_L2 128 
 int MLX5_REFORMAT_TYPE_L2_TO_L2_TUNNEL ; 
 int MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL ; 
 int MLX5_REFORMAT_TYPE_L3_TUNNEL_TO_L2 ; 

__attribute__((used)) static int mlx5_ib_dv_to_prm_packet_reforamt_type(u8 dv_prt, u8 *prm_prt)
{
	switch (dv_prt) {
	case MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L2_TUNNEL:
		*prm_prt = MLX5_REFORMAT_TYPE_L2_TO_L2_TUNNEL;
		break;
	case MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L3_TUNNEL_TO_L2:
		*prm_prt = MLX5_REFORMAT_TYPE_L3_TUNNEL_TO_L2;
		break;
	case MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L3_TUNNEL:
		*prm_prt = MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}