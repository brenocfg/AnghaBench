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
struct client_init_general_data {int statistics_en_flg; int /*<<< orphan*/  cos; void* activate_flg; int /*<<< orphan*/  fp_hsi_ver; int /*<<< orphan*/  traffic_type; int /*<<< orphan*/  func_id; int /*<<< orphan*/  mtu; int /*<<< orphan*/  sp_client_id; void* is_fcoe_flg; int /*<<< orphan*/  statistics_counter_id; void* statistics_zero_flg; int /*<<< orphan*/  client_id; } ;
struct bnx2x_queue_sp_obj {int /*<<< orphan*/  func_id; int /*<<< orphan*/  cl_id; } ;
struct bnx2x_general_setup_params {int /*<<< orphan*/  fp_hsi; int /*<<< orphan*/  cos; int /*<<< orphan*/  mtu; int /*<<< orphan*/  spcl_id; int /*<<< orphan*/  stat_id; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_ACTIVE ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_FCOE ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_STATS ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_ZERO_STATS ; 
 int /*<<< orphan*/  DISABLE_STATISTIC_COUNTER_ID_VALUE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LLFC_TRAFFIC_TYPE_FCOE ; 
 int /*<<< orphan*/  LLFC_TRAFFIC_TYPE_NW ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void bnx2x_q_fill_init_general_data(struct bnx2x *bp,
				struct bnx2x_queue_sp_obj *o,
				struct bnx2x_general_setup_params *params,
				struct client_init_general_data *gen_data,
				unsigned long *flags)
{
	gen_data->client_id = o->cl_id;

	if (test_bit(BNX2X_Q_FLG_STATS, flags)) {
		gen_data->statistics_counter_id =
					params->stat_id;
		gen_data->statistics_en_flg = 1;
		gen_data->statistics_zero_flg =
			test_bit(BNX2X_Q_FLG_ZERO_STATS, flags);
	} else
		gen_data->statistics_counter_id =
					DISABLE_STATISTIC_COUNTER_ID_VALUE;

	gen_data->is_fcoe_flg = test_bit(BNX2X_Q_FLG_FCOE, flags);
	gen_data->activate_flg = test_bit(BNX2X_Q_FLG_ACTIVE, flags);
	gen_data->sp_client_id = params->spcl_id;
	gen_data->mtu = cpu_to_le16(params->mtu);
	gen_data->func_id = o->func_id;

	gen_data->cos = params->cos;

	gen_data->traffic_type =
		test_bit(BNX2X_Q_FLG_FCOE, flags) ?
		LLFC_TRAFFIC_TYPE_FCOE : LLFC_TRAFFIC_TYPE_NW;

	gen_data->fp_hsi_ver = params->fp_hsi;

	DP(BNX2X_MSG_SP, "flags: active %d, cos %d, stats en %d\n",
	   gen_data->activate_flg, gen_data->cos, gen_data->statistics_en_flg);
}