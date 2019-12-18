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
struct hns_roce_v2_mpt_entry {int /*<<< orphan*/  lkey; int /*<<< orphan*/  byte_64_buf_pa1; int /*<<< orphan*/  byte_12_mw_pa; int /*<<< orphan*/  byte_8_mw_cnt_en; int /*<<< orphan*/  byte_4_pd_hop_st; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct hns_roce_mw {scalar_t__ pdn; scalar_t__ pbl_hop_num; scalar_t__ pbl_ba_pg_sz; scalar_t__ pbl_buf_pg_sz; int /*<<< orphan*/  rkey; TYPE_1__ ibmw; } ;

/* Variables and functions */
 scalar_t__ HNS_ROCE_HOP_NUM_0 ; 
 scalar_t__ IB_MW_TYPE_1 ; 
 scalar_t__ PG_SHIFT_OFFSET ; 
 int /*<<< orphan*/  V2_MPT_BYTE_12_BPD_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_12_BQP_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_12_MR_MW_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_12_PA_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_4_MPT_ST_M ; 
 int /*<<< orphan*/  V2_MPT_BYTE_4_MPT_ST_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_4_PBL_BA_PG_SZ_M ; 
 int /*<<< orphan*/  V2_MPT_BYTE_4_PBL_BA_PG_SZ_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_4_PBL_HOP_NUM_M ; 
 int /*<<< orphan*/  V2_MPT_BYTE_4_PBL_HOP_NUM_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_4_PD_M ; 
 int /*<<< orphan*/  V2_MPT_BYTE_4_PD_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_64_PBL_BUF_PG_SZ_M ; 
 int /*<<< orphan*/  V2_MPT_BYTE_64_PBL_BUF_PG_SZ_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_8_L_INV_EN_S ; 
 int /*<<< orphan*/  V2_MPT_BYTE_8_R_INV_EN_S ; 
 scalar_t__ V2_MPT_ST_FREE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hns_roce_v2_mpt_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hns_roce_v2_mw_write_mtpt(void *mb_buf, struct hns_roce_mw *mw)
{
	struct hns_roce_v2_mpt_entry *mpt_entry;

	mpt_entry = mb_buf;
	memset(mpt_entry, 0, sizeof(*mpt_entry));

	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_MPT_ST_M,
		       V2_MPT_BYTE_4_MPT_ST_S, V2_MPT_ST_FREE);
	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_PD_M,
		       V2_MPT_BYTE_4_PD_S, mw->pdn);
	roce_set_field(mpt_entry->byte_4_pd_hop_st,
		       V2_MPT_BYTE_4_PBL_HOP_NUM_M,
		       V2_MPT_BYTE_4_PBL_HOP_NUM_S,
		       mw->pbl_hop_num == HNS_ROCE_HOP_NUM_0 ?
		       0 : mw->pbl_hop_num);
	roce_set_field(mpt_entry->byte_4_pd_hop_st,
		       V2_MPT_BYTE_4_PBL_BA_PG_SZ_M,
		       V2_MPT_BYTE_4_PBL_BA_PG_SZ_S,
		       mw->pbl_ba_pg_sz + PG_SHIFT_OFFSET);

	roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_R_INV_EN_S, 1);
	roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_L_INV_EN_S, 1);

	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_PA_S, 0);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_MR_MW_S, 1);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_BPD_S, 1);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_BQP_S,
		     mw->ibmw.type == IB_MW_TYPE_1 ? 0 : 1);

	roce_set_field(mpt_entry->byte_64_buf_pa1,
		       V2_MPT_BYTE_64_PBL_BUF_PG_SZ_M,
		       V2_MPT_BYTE_64_PBL_BUF_PG_SZ_S,
		       mw->pbl_buf_pg_sz + PG_SHIFT_OFFSET);

	mpt_entry->lkey = cpu_to_le32(mw->rkey);

	return 0;
}