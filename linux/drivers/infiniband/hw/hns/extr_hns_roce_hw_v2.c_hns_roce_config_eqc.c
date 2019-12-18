#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hns_roce_eq_context {int /*<<< orphan*/  nxt_eqe_ba1; int /*<<< orphan*/  nxt_eqe_ba0; int /*<<< orphan*/  byte_36; int /*<<< orphan*/  byte_32; int /*<<< orphan*/  byte_28; int /*<<< orphan*/  eqe_ba1; int /*<<< orphan*/  eqe_ba0; int /*<<< orphan*/  eqe_report_timer; int /*<<< orphan*/  byte_12; int /*<<< orphan*/  byte_8; int /*<<< orphan*/  byte_4; } ;
struct hns_roce_eq {int hop_num; int over_ignore; int coalesce; int arm_st; int eqe_ba_pg_sz; int eqe_buf_pg_sz; int shift; int eqe_ba; int l0_dma; int eqn; int eq_max_cnt; int eq_period; int cur_eqe_ba; int nxt_eqe_ba; TYPE_2__* buf_list; scalar_t__ entries; scalar_t__ cons_index; scalar_t__ doorbell; } ;
struct TYPE_3__ {int eqe_hop_num; int eqe_ba_pg_sz; int eqe_buf_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; scalar_t__ reg_base; } ;
struct TYPE_4__ {int map; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_EQC_ARM_ST_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_ARM_ST_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_BA_PG_SZ_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_BA_PG_SZ_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_BUF_PG_SZ_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_BUF_PG_SZ_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_COALESCE_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_COALESCE_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_CONS_INDX_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_CONS_INDX_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_CUR_EQE_BA_H_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_CUR_EQE_BA_H_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_CUR_EQE_BA_L_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_CUR_EQE_BA_L_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_CUR_EQE_BA_M_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_CUR_EQE_BA_M_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQE_BA_H_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQE_BA_H_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQE_BA_L_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQE_BA_L_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQE_CNT_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQE_CNT_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQN_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQN_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQ_ST_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_EQ_ST_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_HOP_NUM_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_HOP_NUM_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_MAX_CNT_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_MAX_CNT_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_MSI_INDX_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_MSI_INDX_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_NXT_EQE_BA_H_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_NXT_EQE_BA_H_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_NXT_EQE_BA_L_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_NXT_EQE_BA_L_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_OVER_IGNORE_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_OVER_IGNORE_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_PERIOD_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_PERIOD_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_PROD_INDX_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_PROD_INDX_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_REPORT_TIMER_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_REPORT_TIMER_S ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_SHIFT_M ; 
 int /*<<< orphan*/  HNS_ROCE_EQC_SHIFT_S ; 
 int HNS_ROCE_EQ_INIT_CONS_IDX ; 
 int HNS_ROCE_EQ_INIT_EQE_CNT ; 
 int HNS_ROCE_EQ_INIT_MSI_IDX ; 
 int HNS_ROCE_EQ_INIT_PROD_IDX ; 
 int HNS_ROCE_EQ_INIT_REPORT_TIMER ; 
 int HNS_ROCE_V2_EQ_ALWAYS_ARMED ; 
 int HNS_ROCE_V2_EQ_COALESCE_0 ; 
 int HNS_ROCE_V2_EQ_OVER_IGNORE_0 ; 
 int HNS_ROCE_V2_EQ_STATE_VALID ; 
 int PG_SHIFT_OFFSET ; 
 scalar_t__ ROCEE_VF_EQ_DB_CFG0_REG ; 
 int ilog2 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct hns_roce_eq_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_roce_config_eqc(struct hns_roce_dev *hr_dev,
				struct hns_roce_eq *eq,
				void *mb_buf)
{
	struct hns_roce_eq_context *eqc;

	eqc = mb_buf;
	memset(eqc, 0, sizeof(struct hns_roce_eq_context));

	/* init eqc */
	eq->doorbell = hr_dev->reg_base + ROCEE_VF_EQ_DB_CFG0_REG;
	eq->hop_num = hr_dev->caps.eqe_hop_num;
	eq->cons_index = 0;
	eq->over_ignore = HNS_ROCE_V2_EQ_OVER_IGNORE_0;
	eq->coalesce = HNS_ROCE_V2_EQ_COALESCE_0;
	eq->arm_st = HNS_ROCE_V2_EQ_ALWAYS_ARMED;
	eq->eqe_ba_pg_sz = hr_dev->caps.eqe_ba_pg_sz;
	eq->eqe_buf_pg_sz = hr_dev->caps.eqe_buf_pg_sz;
	eq->shift = ilog2((unsigned int)eq->entries);

	if (!eq->hop_num)
		eq->eqe_ba = eq->buf_list->map;
	else
		eq->eqe_ba = eq->l0_dma;

	/* set eqc state */
	roce_set_field(eqc->byte_4,
		       HNS_ROCE_EQC_EQ_ST_M,
		       HNS_ROCE_EQC_EQ_ST_S,
		       HNS_ROCE_V2_EQ_STATE_VALID);

	/* set eqe hop num */
	roce_set_field(eqc->byte_4,
		       HNS_ROCE_EQC_HOP_NUM_M,
		       HNS_ROCE_EQC_HOP_NUM_S, eq->hop_num);

	/* set eqc over_ignore */
	roce_set_field(eqc->byte_4,
		       HNS_ROCE_EQC_OVER_IGNORE_M,
		       HNS_ROCE_EQC_OVER_IGNORE_S, eq->over_ignore);

	/* set eqc coalesce */
	roce_set_field(eqc->byte_4,
		       HNS_ROCE_EQC_COALESCE_M,
		       HNS_ROCE_EQC_COALESCE_S, eq->coalesce);

	/* set eqc arm_state */
	roce_set_field(eqc->byte_4,
		       HNS_ROCE_EQC_ARM_ST_M,
		       HNS_ROCE_EQC_ARM_ST_S, eq->arm_st);

	/* set eqn */
	roce_set_field(eqc->byte_4,
		       HNS_ROCE_EQC_EQN_M,
		       HNS_ROCE_EQC_EQN_S, eq->eqn);

	/* set eqe_cnt */
	roce_set_field(eqc->byte_4,
		       HNS_ROCE_EQC_EQE_CNT_M,
		       HNS_ROCE_EQC_EQE_CNT_S,
		       HNS_ROCE_EQ_INIT_EQE_CNT);

	/* set eqe_ba_pg_sz */
	roce_set_field(eqc->byte_8,
		       HNS_ROCE_EQC_BA_PG_SZ_M,
		       HNS_ROCE_EQC_BA_PG_SZ_S,
		       eq->eqe_ba_pg_sz + PG_SHIFT_OFFSET);

	/* set eqe_buf_pg_sz */
	roce_set_field(eqc->byte_8,
		       HNS_ROCE_EQC_BUF_PG_SZ_M,
		       HNS_ROCE_EQC_BUF_PG_SZ_S,
		       eq->eqe_buf_pg_sz + PG_SHIFT_OFFSET);

	/* set eq_producer_idx */
	roce_set_field(eqc->byte_8,
		       HNS_ROCE_EQC_PROD_INDX_M,
		       HNS_ROCE_EQC_PROD_INDX_S,
		       HNS_ROCE_EQ_INIT_PROD_IDX);

	/* set eq_max_cnt */
	roce_set_field(eqc->byte_12,
		       HNS_ROCE_EQC_MAX_CNT_M,
		       HNS_ROCE_EQC_MAX_CNT_S, eq->eq_max_cnt);

	/* set eq_period */
	roce_set_field(eqc->byte_12,
		       HNS_ROCE_EQC_PERIOD_M,
		       HNS_ROCE_EQC_PERIOD_S, eq->eq_period);

	/* set eqe_report_timer */
	roce_set_field(eqc->eqe_report_timer,
		       HNS_ROCE_EQC_REPORT_TIMER_M,
		       HNS_ROCE_EQC_REPORT_TIMER_S,
		       HNS_ROCE_EQ_INIT_REPORT_TIMER);

	/* set eqe_ba [34:3] */
	roce_set_field(eqc->eqe_ba0,
		       HNS_ROCE_EQC_EQE_BA_L_M,
		       HNS_ROCE_EQC_EQE_BA_L_S, eq->eqe_ba >> 3);

	/* set eqe_ba [64:35] */
	roce_set_field(eqc->eqe_ba1,
		       HNS_ROCE_EQC_EQE_BA_H_M,
		       HNS_ROCE_EQC_EQE_BA_H_S, eq->eqe_ba >> 35);

	/* set eq shift */
	roce_set_field(eqc->byte_28,
		       HNS_ROCE_EQC_SHIFT_M,
		       HNS_ROCE_EQC_SHIFT_S, eq->shift);

	/* set eq MSI_IDX */
	roce_set_field(eqc->byte_28,
		       HNS_ROCE_EQC_MSI_INDX_M,
		       HNS_ROCE_EQC_MSI_INDX_S,
		       HNS_ROCE_EQ_INIT_MSI_IDX);

	/* set cur_eqe_ba [27:12] */
	roce_set_field(eqc->byte_28,
		       HNS_ROCE_EQC_CUR_EQE_BA_L_M,
		       HNS_ROCE_EQC_CUR_EQE_BA_L_S, eq->cur_eqe_ba >> 12);

	/* set cur_eqe_ba [59:28] */
	roce_set_field(eqc->byte_32,
		       HNS_ROCE_EQC_CUR_EQE_BA_M_M,
		       HNS_ROCE_EQC_CUR_EQE_BA_M_S, eq->cur_eqe_ba >> 28);

	/* set cur_eqe_ba [63:60] */
	roce_set_field(eqc->byte_36,
		       HNS_ROCE_EQC_CUR_EQE_BA_H_M,
		       HNS_ROCE_EQC_CUR_EQE_BA_H_S, eq->cur_eqe_ba >> 60);

	/* set eq consumer idx */
	roce_set_field(eqc->byte_36,
		       HNS_ROCE_EQC_CONS_INDX_M,
		       HNS_ROCE_EQC_CONS_INDX_S,
		       HNS_ROCE_EQ_INIT_CONS_IDX);

	/* set nex_eqe_ba[43:12] */
	roce_set_field(eqc->nxt_eqe_ba0,
		       HNS_ROCE_EQC_NXT_EQE_BA_L_M,
		       HNS_ROCE_EQC_NXT_EQE_BA_L_S, eq->nxt_eqe_ba >> 12);

	/* set nex_eqe_ba[63:44] */
	roce_set_field(eqc->nxt_eqe_ba1,
		       HNS_ROCE_EQC_NXT_EQE_BA_H_M,
		       HNS_ROCE_EQC_NXT_EQE_BA_H_S, eq->nxt_eqe_ba >> 44);
}