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
typedef  int /*<<< orphan*/  u16 ;
struct hns_roce_buf_list {int map; scalar_t__ buf; } ;
struct TYPE_2__ {struct hns_roce_buf_list tptr_buf; } ;
struct hns_roce_v1_priv {TYPE_1__ tptr_table; } ;
struct hns_roce_dev {scalar_t__ priv; } ;
struct hns_roce_cq_context {int /*<<< orphan*/  cqc_byte_32; void* cqe_tptr_addr_l; int /*<<< orphan*/  cqc_byte_20; void* cur_cqe_ba0_l; int /*<<< orphan*/  cqc_byte_12; void* cq_bt_l; int /*<<< orphan*/  cqc_byte_4; } ;
struct hns_roce_cq {int cqn; int /*<<< orphan*/ * tptr_addr; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_12_CEQN_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_12_CEQN_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_32_CE_FLAG_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_32_NOTIFICATION_FLAG_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_32_SE_FLAG_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_S ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_4_CQN_M ; 
 int /*<<< orphan*/  CQ_CONTEXT_CQC_BYTE_4_CQN_S ; 
 int /*<<< orphan*/  CQ_CQNTEXT_CQC_BYTE_32_TYPE_OF_COMPLETION_NOTIFICATION_S ; 
 int CQ_STATE_VALID ; 
 int HNS_ROCE_V1_TPTR_ENTRY_SIZE ; 
 void* cpu_to_le32 (int) ; 
 int ilog2 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct hns_roce_cq_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_roce_v1_write_cqc(struct hns_roce_dev *hr_dev,
				  struct hns_roce_cq *hr_cq, void *mb_buf,
				  u64 *mtts, dma_addr_t dma_handle, int nent,
				  u32 vector)
{
	struct hns_roce_cq_context *cq_context = NULL;
	struct hns_roce_buf_list *tptr_buf;
	struct hns_roce_v1_priv *priv;
	dma_addr_t tptr_dma_addr;
	int offset;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	tptr_buf = &priv->tptr_table.tptr_buf;

	cq_context = mb_buf;
	memset(cq_context, 0, sizeof(*cq_context));

	/* Get the tptr for this CQ. */
	offset = hr_cq->cqn * HNS_ROCE_V1_TPTR_ENTRY_SIZE;
	tptr_dma_addr = tptr_buf->map + offset;
	hr_cq->tptr_addr = (u16 *)(tptr_buf->buf + offset);

	/* Register cq_context members */
	roce_set_field(cq_context->cqc_byte_4,
		       CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_M,
		       CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_S, CQ_STATE_VALID);
	roce_set_field(cq_context->cqc_byte_4, CQ_CONTEXT_CQC_BYTE_4_CQN_M,
		       CQ_CONTEXT_CQC_BYTE_4_CQN_S, hr_cq->cqn);

	cq_context->cq_bt_l = cpu_to_le32((u32)dma_handle);

	roce_set_field(cq_context->cqc_byte_12,
		       CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_M,
		       CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_S,
		       ((u64)dma_handle >> 32));
	roce_set_field(cq_context->cqc_byte_12,
		       CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_M,
		       CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_S,
		       ilog2((unsigned int)nent));
	roce_set_field(cq_context->cqc_byte_12, CQ_CONTEXT_CQC_BYTE_12_CEQN_M,
		       CQ_CONTEXT_CQC_BYTE_12_CEQN_S, vector);

	cq_context->cur_cqe_ba0_l = cpu_to_le32((u32)(mtts[0]));

	roce_set_field(cq_context->cqc_byte_20,
		       CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_M,
		       CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_S, (mtts[0]) >> 32);
	/* Dedicated hardware, directly set 0 */
	roce_set_field(cq_context->cqc_byte_20,
		       CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_M,
		       CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_S, 0);
	/**
	 * 44 = 32 + 12, When evaluating addr to hardware, shift 12 because of
	 * using 4K page, and shift more 32 because of
	 * caculating the high 32 bit value evaluated to hardware.
	 */
	roce_set_field(cq_context->cqc_byte_20,
		       CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_M,
		       CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_S,
		       tptr_dma_addr >> 44);

	cq_context->cqe_tptr_addr_l = cpu_to_le32((u32)(tptr_dma_addr >> 12));

	roce_set_field(cq_context->cqc_byte_32,
		       CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_M,
		       CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_S, 0);
	roce_set_bit(cq_context->cqc_byte_32,
		     CQ_CONTEXT_CQC_BYTE_32_SE_FLAG_S, 0);
	roce_set_bit(cq_context->cqc_byte_32,
		     CQ_CONTEXT_CQC_BYTE_32_CE_FLAG_S, 0);
	roce_set_bit(cq_context->cqc_byte_32,
		     CQ_CONTEXT_CQC_BYTE_32_NOTIFICATION_FLAG_S, 0);
	roce_set_bit(cq_context->cqc_byte_32,
		     CQ_CQNTEXT_CQC_BYTE_32_TYPE_OF_COMPLETION_NOTIFICATION_S,
		     0);
	/* The initial value of cq's ci is 0 */
	roce_set_field(cq_context->cqc_byte_32,
		       CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_M,
		       CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_S, 0);
}