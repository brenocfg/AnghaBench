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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct hns_roce_srq_context {int /*<<< orphan*/  db_record_addr_record_en; int /*<<< orphan*/  byte_56_xrc_cqn; int /*<<< orphan*/  rsv_idxnxtblkaddr; void* idx_nxt_blk_addr; int /*<<< orphan*/  byte_44_idxbufpgsz_addr; void* idx_cur_blk_addr; int /*<<< orphan*/  rsv_idx_bt_ba; void* idx_bt_ba; int /*<<< orphan*/  byte_28_rqws_pd; int /*<<< orphan*/  byte_24_wqe_bt_ba; void* wqe_bt_ba; int /*<<< orphan*/  byte_12_xrcd; int /*<<< orphan*/  byte_8_limit_wl; int /*<<< orphan*/  byte_4_srqn_srqst; } ;
struct hns_roce_srq {int srqn; scalar_t__ max_gs; int /*<<< orphan*/  max; } ;
struct TYPE_2__ {scalar_t__ srqwqe_hop_num; scalar_t__ idx_hop_num; int idx_ba_pg_sz; int idx_buf_pg_sz; int srqwqe_ba_pg_sz; int srqwqe_buf_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ HNS_ROCE_HOP_NUM_0 ; 
 int PAGE_ADDR_SHIFT ; 
 int PG_SHIFT_OFFSET ; 
 int /*<<< orphan*/  SRQC_BYTE_12_SRQ_XRCD_M ; 
 int /*<<< orphan*/  SRQC_BYTE_12_SRQ_XRCD_S ; 
 int /*<<< orphan*/  SRQC_BYTE_24_SRQ_WQE_BT_BA_M ; 
 int /*<<< orphan*/  SRQC_BYTE_24_SRQ_WQE_BT_BA_S ; 
 int /*<<< orphan*/  SRQC_BYTE_28_PD_M ; 
 int /*<<< orphan*/  SRQC_BYTE_28_PD_S ; 
 int /*<<< orphan*/  SRQC_BYTE_28_RQWS_M ; 
 int /*<<< orphan*/  SRQC_BYTE_28_RQWS_S ; 
 int /*<<< orphan*/  SRQC_BYTE_36_SRQ_IDX_BT_BA_M ; 
 int /*<<< orphan*/  SRQC_BYTE_36_SRQ_IDX_BT_BA_S ; 
 int /*<<< orphan*/  SRQC_BYTE_44_SRQ_IDX_BA_PG_SZ_M ; 
 int /*<<< orphan*/  SRQC_BYTE_44_SRQ_IDX_BA_PG_SZ_S ; 
 int /*<<< orphan*/  SRQC_BYTE_44_SRQ_IDX_BUF_PG_SZ_M ; 
 int /*<<< orphan*/  SRQC_BYTE_44_SRQ_IDX_BUF_PG_SZ_S ; 
 int /*<<< orphan*/  SRQC_BYTE_44_SRQ_IDX_CUR_BLK_ADDR_M ; 
 int /*<<< orphan*/  SRQC_BYTE_44_SRQ_IDX_CUR_BLK_ADDR_S ; 
 int /*<<< orphan*/  SRQC_BYTE_44_SRQ_IDX_HOP_NUM_M ; 
 int /*<<< orphan*/  SRQC_BYTE_44_SRQ_IDX_HOP_NUM_S ; 
 int /*<<< orphan*/  SRQC_BYTE_4_SRQN_M ; 
 int /*<<< orphan*/  SRQC_BYTE_4_SRQN_S ; 
 int /*<<< orphan*/  SRQC_BYTE_4_SRQ_SHIFT_M ; 
 int /*<<< orphan*/  SRQC_BYTE_4_SRQ_SHIFT_S ; 
 int /*<<< orphan*/  SRQC_BYTE_4_SRQ_ST_M ; 
 int /*<<< orphan*/  SRQC_BYTE_4_SRQ_ST_S ; 
 int /*<<< orphan*/  SRQC_BYTE_4_SRQ_WQE_HOP_NUM_M ; 
 int /*<<< orphan*/  SRQC_BYTE_4_SRQ_WQE_HOP_NUM_S ; 
 int /*<<< orphan*/  SRQC_BYTE_52_SRQ_IDX_NXT_BLK_ADDR_M ; 
 int /*<<< orphan*/  SRQC_BYTE_52_SRQ_IDX_NXT_BLK_ADDR_S ; 
 int /*<<< orphan*/  SRQC_BYTE_56_SRQ_WQE_BA_PG_SZ_M ; 
 int /*<<< orphan*/  SRQC_BYTE_56_SRQ_WQE_BA_PG_SZ_S ; 
 int /*<<< orphan*/  SRQC_BYTE_56_SRQ_WQE_BUF_PG_SZ_M ; 
 int /*<<< orphan*/  SRQC_BYTE_56_SRQ_WQE_BUF_PG_SZ_S ; 
 int /*<<< orphan*/  SRQC_BYTE_56_SRQ_XRC_CQN_M ; 
 int /*<<< orphan*/  SRQC_BYTE_56_SRQ_XRC_CQN_S ; 
 int /*<<< orphan*/  SRQC_BYTE_60_SRQ_RECORD_EN_S ; 
 int /*<<< orphan*/  SRQC_BYTE_8_SRQ_LIMIT_WL_M ; 
 int /*<<< orphan*/  SRQC_BYTE_8_SRQ_LIMIT_WL_S ; 
 void* cpu_to_le32 (int) ; 
 int fls (scalar_t__) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hns_roce_srq_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_roce_v2_write_srqc(struct hns_roce_dev *hr_dev,
				   struct hns_roce_srq *srq, u32 pdn, u16 xrcd,
				   u32 cqn, void *mb_buf, u64 *mtts_wqe,
				   u64 *mtts_idx, dma_addr_t dma_handle_wqe,
				   dma_addr_t dma_handle_idx)
{
	struct hns_roce_srq_context *srq_context;

	srq_context = mb_buf;
	memset(srq_context, 0, sizeof(*srq_context));

	roce_set_field(srq_context->byte_4_srqn_srqst, SRQC_BYTE_4_SRQ_ST_M,
		       SRQC_BYTE_4_SRQ_ST_S, 1);

	roce_set_field(srq_context->byte_4_srqn_srqst,
		       SRQC_BYTE_4_SRQ_WQE_HOP_NUM_M,
		       SRQC_BYTE_4_SRQ_WQE_HOP_NUM_S,
		       (hr_dev->caps.srqwqe_hop_num == HNS_ROCE_HOP_NUM_0 ? 0 :
		       hr_dev->caps.srqwqe_hop_num));
	roce_set_field(srq_context->byte_4_srqn_srqst,
		       SRQC_BYTE_4_SRQ_SHIFT_M, SRQC_BYTE_4_SRQ_SHIFT_S,
		       ilog2(srq->max));

	roce_set_field(srq_context->byte_4_srqn_srqst, SRQC_BYTE_4_SRQN_M,
		       SRQC_BYTE_4_SRQN_S, srq->srqn);

	roce_set_field(srq_context->byte_8_limit_wl, SRQC_BYTE_8_SRQ_LIMIT_WL_M,
		       SRQC_BYTE_8_SRQ_LIMIT_WL_S, 0);

	roce_set_field(srq_context->byte_12_xrcd, SRQC_BYTE_12_SRQ_XRCD_M,
		       SRQC_BYTE_12_SRQ_XRCD_S, xrcd);

	srq_context->wqe_bt_ba = cpu_to_le32((u32)(dma_handle_wqe >> 3));

	roce_set_field(srq_context->byte_24_wqe_bt_ba,
		       SRQC_BYTE_24_SRQ_WQE_BT_BA_M,
		       SRQC_BYTE_24_SRQ_WQE_BT_BA_S,
		       dma_handle_wqe >> 35);

	roce_set_field(srq_context->byte_28_rqws_pd, SRQC_BYTE_28_PD_M,
		       SRQC_BYTE_28_PD_S, pdn);
	roce_set_field(srq_context->byte_28_rqws_pd, SRQC_BYTE_28_RQWS_M,
		       SRQC_BYTE_28_RQWS_S, srq->max_gs <= 0 ? 0 :
		       fls(srq->max_gs - 1));

	srq_context->idx_bt_ba = cpu_to_le32(dma_handle_idx >> 3);
	roce_set_field(srq_context->rsv_idx_bt_ba,
		       SRQC_BYTE_36_SRQ_IDX_BT_BA_M,
		       SRQC_BYTE_36_SRQ_IDX_BT_BA_S,
		       dma_handle_idx >> 35);

	srq_context->idx_cur_blk_addr =
		cpu_to_le32(mtts_idx[0] >> PAGE_ADDR_SHIFT);
	roce_set_field(srq_context->byte_44_idxbufpgsz_addr,
		       SRQC_BYTE_44_SRQ_IDX_CUR_BLK_ADDR_M,
		       SRQC_BYTE_44_SRQ_IDX_CUR_BLK_ADDR_S,
		       mtts_idx[0] >> (32 + PAGE_ADDR_SHIFT));
	roce_set_field(srq_context->byte_44_idxbufpgsz_addr,
		       SRQC_BYTE_44_SRQ_IDX_HOP_NUM_M,
		       SRQC_BYTE_44_SRQ_IDX_HOP_NUM_S,
		       hr_dev->caps.idx_hop_num == HNS_ROCE_HOP_NUM_0 ? 0 :
		       hr_dev->caps.idx_hop_num);

	roce_set_field(srq_context->byte_44_idxbufpgsz_addr,
		       SRQC_BYTE_44_SRQ_IDX_BA_PG_SZ_M,
		       SRQC_BYTE_44_SRQ_IDX_BA_PG_SZ_S,
		       hr_dev->caps.idx_ba_pg_sz);
	roce_set_field(srq_context->byte_44_idxbufpgsz_addr,
		       SRQC_BYTE_44_SRQ_IDX_BUF_PG_SZ_M,
		       SRQC_BYTE_44_SRQ_IDX_BUF_PG_SZ_S,
		       hr_dev->caps.idx_buf_pg_sz);

	srq_context->idx_nxt_blk_addr =
		cpu_to_le32(mtts_idx[1] >> PAGE_ADDR_SHIFT);
	roce_set_field(srq_context->rsv_idxnxtblkaddr,
		       SRQC_BYTE_52_SRQ_IDX_NXT_BLK_ADDR_M,
		       SRQC_BYTE_52_SRQ_IDX_NXT_BLK_ADDR_S,
		       mtts_idx[1] >> (32 + PAGE_ADDR_SHIFT));
	roce_set_field(srq_context->byte_56_xrc_cqn,
		       SRQC_BYTE_56_SRQ_XRC_CQN_M, SRQC_BYTE_56_SRQ_XRC_CQN_S,
		       cqn);
	roce_set_field(srq_context->byte_56_xrc_cqn,
		       SRQC_BYTE_56_SRQ_WQE_BA_PG_SZ_M,
		       SRQC_BYTE_56_SRQ_WQE_BA_PG_SZ_S,
		       hr_dev->caps.srqwqe_ba_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(srq_context->byte_56_xrc_cqn,
		       SRQC_BYTE_56_SRQ_WQE_BUF_PG_SZ_M,
		       SRQC_BYTE_56_SRQ_WQE_BUF_PG_SZ_S,
		       hr_dev->caps.srqwqe_buf_pg_sz + PG_SHIFT_OFFSET);

	roce_set_bit(srq_context->db_record_addr_record_en,
		     SRQC_BYTE_60_SRQ_RECORD_EN_S, 0);
}