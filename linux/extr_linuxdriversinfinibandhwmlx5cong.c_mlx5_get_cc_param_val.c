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
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static u32 mlx5_get_cc_param_val(void *field, int offset)
{
	switch (offset) {
	case MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				clamp_tgt_rate);
	case MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE_ATI:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				clamp_tgt_rate_after_time_inc);
	case MLX5_IB_DBG_CC_RP_TIME_RESET:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_time_reset);
	case MLX5_IB_DBG_CC_RP_BYTE_RESET:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_byte_reset);
	case MLX5_IB_DBG_CC_RP_THRESHOLD:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_threshold);
	case MLX5_IB_DBG_CC_RP_AI_RATE:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_ai_rate);
	case MLX5_IB_DBG_CC_RP_HAI_RATE:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_hai_rate);
	case MLX5_IB_DBG_CC_RP_MIN_DEC_FAC:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_min_dec_fac);
	case MLX5_IB_DBG_CC_RP_MIN_RATE:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_min_rate);
	case MLX5_IB_DBG_CC_RP_RATE_TO_SET_ON_FIRST_CNP:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rate_to_set_on_first_cnp);
	case MLX5_IB_DBG_CC_RP_DCE_TCP_G:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				dce_tcp_g);
	case MLX5_IB_DBG_CC_RP_DCE_TCP_RTT:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				dce_tcp_rtt);
	case MLX5_IB_DBG_CC_RP_RATE_REDUCE_MONITOR_PERIOD:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rate_reduce_monitor_period);
	case MLX5_IB_DBG_CC_RP_INITIAL_ALPHA_VALUE:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				initial_alpha_value);
	case MLX5_IB_DBG_CC_RP_GD:
		return MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_gd);
	case MLX5_IB_DBG_CC_NP_CNP_DSCP:
		return MLX5_GET(cong_control_r_roce_ecn_np, field,
				cnp_dscp);
	case MLX5_IB_DBG_CC_NP_CNP_PRIO_MODE:
		return MLX5_GET(cong_control_r_roce_ecn_np, field,
				cnp_prio_mode);
	case MLX5_IB_DBG_CC_NP_CNP_PRIO:
		return MLX5_GET(cong_control_r_roce_ecn_np, field,
				cnp_802p_prio);
	default:
		return 0;
	}
}