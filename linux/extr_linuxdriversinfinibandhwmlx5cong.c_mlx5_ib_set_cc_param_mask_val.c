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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  MLX5_IB_DBG_CC_NP_CNP_DSCP 145 
#define  MLX5_IB_DBG_CC_NP_CNP_PRIO 144 
#define  MLX5_IB_DBG_CC_NP_CNP_PRIO_MODE 143 
#define  MLX5_IB_DBG_CC_RP_AI_RATE 142 
#define  MLX5_IB_DBG_CC_RP_BYTE_RESET 141 
#define  MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE 140 
#define  MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE_ATI 139 
#define  MLX5_IB_DBG_CC_RP_DCE_TCP_G 138 
#define  MLX5_IB_DBG_CC_RP_DCE_TCP_RTT 137 
#define  MLX5_IB_DBG_CC_RP_GD 136 
#define  MLX5_IB_DBG_CC_RP_HAI_RATE 135 
#define  MLX5_IB_DBG_CC_RP_INITIAL_ALPHA_VALUE 134 
#define  MLX5_IB_DBG_CC_RP_MIN_DEC_FAC 133 
#define  MLX5_IB_DBG_CC_RP_MIN_RATE 132 
#define  MLX5_IB_DBG_CC_RP_RATE_REDUCE_MONITOR_PERIOD 131 
#define  MLX5_IB_DBG_CC_RP_RATE_TO_SET_ON_FIRST_CNP 130 
#define  MLX5_IB_DBG_CC_RP_THRESHOLD 129 
#define  MLX5_IB_DBG_CC_RP_TIME_RESET 128 
 int /*<<< orphan*/  MLX5_IB_NP_CNP_DSCP_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_NP_CNP_PRIO_MODE_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_AI_RATE_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_BYTE_RESET_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_CLAMP_TGT_RATE_ATI_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_CLAMP_TGT_RATE_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_DCE_TCP_G_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_DCE_TCP_RTT_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_GD_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_HAI_RATE_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_INITIAL_ALPHA_VALUE_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_MIN_DEC_FAC_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_MIN_RATE_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_RATE_REDUCE_MONITOR_PERIOD_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_RATE_TO_SET_ON_FIRST_CNP_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_THRESHOLD_ATTR ; 
 int /*<<< orphan*/  MLX5_IB_RP_TIME_RESET_ATTR ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clamp_tgt_rate ; 
 int /*<<< orphan*/  clamp_tgt_rate_after_time_inc ; 
 int /*<<< orphan*/  cnp_802p_prio ; 
 int /*<<< orphan*/  cnp_dscp ; 
 int /*<<< orphan*/  cnp_prio_mode ; 
 int /*<<< orphan*/  cong_control_r_roce_ecn_np ; 
 int /*<<< orphan*/  cong_control_r_roce_ecn_rp ; 
 int /*<<< orphan*/  dce_tcp_g ; 
 int /*<<< orphan*/  dce_tcp_rtt ; 
 int /*<<< orphan*/  initial_alpha_value ; 
 int /*<<< orphan*/  rate_reduce_monitor_period ; 
 int /*<<< orphan*/  rate_to_set_on_first_cnp ; 
 int /*<<< orphan*/  rpg_ai_rate ; 
 int /*<<< orphan*/  rpg_byte_reset ; 
 int /*<<< orphan*/  rpg_gd ; 
 int /*<<< orphan*/  rpg_hai_rate ; 
 int /*<<< orphan*/  rpg_min_dec_fac ; 
 int /*<<< orphan*/  rpg_min_rate ; 
 int /*<<< orphan*/  rpg_threshold ; 
 int /*<<< orphan*/  rpg_time_reset ; 

__attribute__((used)) static void mlx5_ib_set_cc_param_mask_val(void *field, int offset,
					  u32 var, u32 *attr_mask)
{
	switch (offset) {
	case MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE:
		*attr_mask |= MLX5_IB_RP_CLAMP_TGT_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 clamp_tgt_rate, var);
		break;
	case MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE_ATI:
		*attr_mask |= MLX5_IB_RP_CLAMP_TGT_RATE_ATI_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 clamp_tgt_rate_after_time_inc, var);
		break;
	case MLX5_IB_DBG_CC_RP_TIME_RESET:
		*attr_mask |= MLX5_IB_RP_TIME_RESET_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_time_reset, var);
		break;
	case MLX5_IB_DBG_CC_RP_BYTE_RESET:
		*attr_mask |= MLX5_IB_RP_BYTE_RESET_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_byte_reset, var);
		break;
	case MLX5_IB_DBG_CC_RP_THRESHOLD:
		*attr_mask |= MLX5_IB_RP_THRESHOLD_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_threshold, var);
		break;
	case MLX5_IB_DBG_CC_RP_AI_RATE:
		*attr_mask |= MLX5_IB_RP_AI_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_ai_rate, var);
		break;
	case MLX5_IB_DBG_CC_RP_HAI_RATE:
		*attr_mask |= MLX5_IB_RP_HAI_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_hai_rate, var);
		break;
	case MLX5_IB_DBG_CC_RP_MIN_DEC_FAC:
		*attr_mask |= MLX5_IB_RP_MIN_DEC_FAC_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_min_dec_fac, var);
		break;
	case MLX5_IB_DBG_CC_RP_MIN_RATE:
		*attr_mask |= MLX5_IB_RP_MIN_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_min_rate, var);
		break;
	case MLX5_IB_DBG_CC_RP_RATE_TO_SET_ON_FIRST_CNP:
		*attr_mask |= MLX5_IB_RP_RATE_TO_SET_ON_FIRST_CNP_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rate_to_set_on_first_cnp, var);
		break;
	case MLX5_IB_DBG_CC_RP_DCE_TCP_G:
		*attr_mask |= MLX5_IB_RP_DCE_TCP_G_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 dce_tcp_g, var);
		break;
	case MLX5_IB_DBG_CC_RP_DCE_TCP_RTT:
		*attr_mask |= MLX5_IB_RP_DCE_TCP_RTT_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 dce_tcp_rtt, var);
		break;
	case MLX5_IB_DBG_CC_RP_RATE_REDUCE_MONITOR_PERIOD:
		*attr_mask |= MLX5_IB_RP_RATE_REDUCE_MONITOR_PERIOD_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rate_reduce_monitor_period, var);
		break;
	case MLX5_IB_DBG_CC_RP_INITIAL_ALPHA_VALUE:
		*attr_mask |= MLX5_IB_RP_INITIAL_ALPHA_VALUE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 initial_alpha_value, var);
		break;
	case MLX5_IB_DBG_CC_RP_GD:
		*attr_mask |= MLX5_IB_RP_GD_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_gd, var);
		break;
	case MLX5_IB_DBG_CC_NP_CNP_DSCP:
		*attr_mask |= MLX5_IB_NP_CNP_DSCP_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_np, field, cnp_dscp, var);
		break;
	case MLX5_IB_DBG_CC_NP_CNP_PRIO_MODE:
		*attr_mask |= MLX5_IB_NP_CNP_PRIO_MODE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_np, field, cnp_prio_mode, var);
		break;
	case MLX5_IB_DBG_CC_NP_CNP_PRIO:
		*attr_mask |= MLX5_IB_NP_CNP_PRIO_MODE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_np, field, cnp_prio_mode, 0);
		MLX5_SET(cong_control_r_roce_ecn_np, field, cnp_802p_prio, var);
		break;
	}
}