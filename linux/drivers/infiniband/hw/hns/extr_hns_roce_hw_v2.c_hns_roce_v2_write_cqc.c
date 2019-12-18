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
typedef  int u64 ;
typedef  int u32 ;
struct hns_roce_v2_cq_context {int /*<<< orphan*/  byte_56_cqe_period_maxcnt; void* db_record_addr; int /*<<< orphan*/  byte_44_db_record; int /*<<< orphan*/  byte_40_cqe_ba; void* cqe_ba; int /*<<< orphan*/  byte_24_pgsz_addr; void* cqe_nxt_blk_addr; int /*<<< orphan*/  byte_16_hop_addr; void* cqe_cur_blk_addr; int /*<<< orphan*/  byte_8_cqn; int /*<<< orphan*/  byte_4_pg_ceqn; } ;
struct TYPE_3__ {scalar_t__ cqe_hop_num; int cqe_ba_pg_sz; int cqe_buf_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;
struct TYPE_4__ {int dma; } ;
struct hns_roce_cq {int cqn; TYPE_2__ db; scalar_t__ db_en; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ HNS_ROCE_HOP_NUM_0 ; 
 int HNS_ROCE_V2_CQ_DEFAULT_BURST_NUM ; 
 int HNS_ROCE_V2_CQ_DEFAULT_INTERVAL ; 
 int PAGE_ADDR_SHIFT ; 
 int PG_SHIFT_OFFSET ; 
 int REG_NXT_CEQE ; 
 int /*<<< orphan*/  V2_CQC_BYTE_16_CQE_CUR_BLK_ADDR_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_16_CQE_CUR_BLK_ADDR_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_16_CQE_HOP_NUM_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_16_CQE_HOP_NUM_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_24_CQE_BA_PG_SZ_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_24_CQE_BA_PG_SZ_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_24_CQE_BUF_PG_SZ_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_24_CQE_BUF_PG_SZ_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_24_CQE_NXT_BLK_ADDR_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_24_CQE_NXT_BLK_ADDR_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_40_CQE_BA_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_40_CQE_BA_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_44_DB_RECORD_ADDR_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_44_DB_RECORD_ADDR_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_44_DB_RECORD_EN_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_4_ARM_ST_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_4_ARM_ST_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_4_CEQN_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_4_CEQN_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_4_CQ_ST_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_4_CQ_ST_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_4_SHIFT_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_4_SHIFT_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_56_CQ_MAX_CNT_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_56_CQ_MAX_CNT_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_56_CQ_PERIOD_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_56_CQ_PERIOD_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_8_CQN_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_8_CQN_S ; 
 int V2_CQ_STATE_VALID ; 
 void* cpu_to_le32 (int) ; 
 int ilog2 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct hns_roce_v2_cq_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_roce_v2_write_cqc(struct hns_roce_dev *hr_dev,
				  struct hns_roce_cq *hr_cq, void *mb_buf,
				  u64 *mtts, dma_addr_t dma_handle, int nent,
				  u32 vector)
{
	struct hns_roce_v2_cq_context *cq_context;

	cq_context = mb_buf;
	memset(cq_context, 0, sizeof(*cq_context));

	roce_set_field(cq_context->byte_4_pg_ceqn, V2_CQC_BYTE_4_CQ_ST_M,
		       V2_CQC_BYTE_4_CQ_ST_S, V2_CQ_STATE_VALID);
	roce_set_field(cq_context->byte_4_pg_ceqn, V2_CQC_BYTE_4_ARM_ST_M,
		       V2_CQC_BYTE_4_ARM_ST_S, REG_NXT_CEQE);
	roce_set_field(cq_context->byte_4_pg_ceqn, V2_CQC_BYTE_4_SHIFT_M,
		       V2_CQC_BYTE_4_SHIFT_S, ilog2((unsigned int)nent));
	roce_set_field(cq_context->byte_4_pg_ceqn, V2_CQC_BYTE_4_CEQN_M,
		       V2_CQC_BYTE_4_CEQN_S, vector);

	roce_set_field(cq_context->byte_8_cqn, V2_CQC_BYTE_8_CQN_M,
		       V2_CQC_BYTE_8_CQN_S, hr_cq->cqn);

	cq_context->cqe_cur_blk_addr = cpu_to_le32(mtts[0] >> PAGE_ADDR_SHIFT);

	roce_set_field(cq_context->byte_16_hop_addr,
		       V2_CQC_BYTE_16_CQE_CUR_BLK_ADDR_M,
		       V2_CQC_BYTE_16_CQE_CUR_BLK_ADDR_S,
		       mtts[0] >> (32 + PAGE_ADDR_SHIFT));
	roce_set_field(cq_context->byte_16_hop_addr,
		       V2_CQC_BYTE_16_CQE_HOP_NUM_M,
		       V2_CQC_BYTE_16_CQE_HOP_NUM_S, hr_dev->caps.cqe_hop_num ==
		       HNS_ROCE_HOP_NUM_0 ? 0 : hr_dev->caps.cqe_hop_num);

	cq_context->cqe_nxt_blk_addr = cpu_to_le32(mtts[1] >> PAGE_ADDR_SHIFT);
	roce_set_field(cq_context->byte_24_pgsz_addr,
		       V2_CQC_BYTE_24_CQE_NXT_BLK_ADDR_M,
		       V2_CQC_BYTE_24_CQE_NXT_BLK_ADDR_S,
		       mtts[1] >> (32 + PAGE_ADDR_SHIFT));
	roce_set_field(cq_context->byte_24_pgsz_addr,
		       V2_CQC_BYTE_24_CQE_BA_PG_SZ_M,
		       V2_CQC_BYTE_24_CQE_BA_PG_SZ_S,
		       hr_dev->caps.cqe_ba_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(cq_context->byte_24_pgsz_addr,
		       V2_CQC_BYTE_24_CQE_BUF_PG_SZ_M,
		       V2_CQC_BYTE_24_CQE_BUF_PG_SZ_S,
		       hr_dev->caps.cqe_buf_pg_sz + PG_SHIFT_OFFSET);

	cq_context->cqe_ba = cpu_to_le32(dma_handle >> 3);

	roce_set_field(cq_context->byte_40_cqe_ba, V2_CQC_BYTE_40_CQE_BA_M,
		       V2_CQC_BYTE_40_CQE_BA_S, (dma_handle >> (32 + 3)));

	if (hr_cq->db_en)
		roce_set_bit(cq_context->byte_44_db_record,
			     V2_CQC_BYTE_44_DB_RECORD_EN_S, 1);

	roce_set_field(cq_context->byte_44_db_record,
		       V2_CQC_BYTE_44_DB_RECORD_ADDR_M,
		       V2_CQC_BYTE_44_DB_RECORD_ADDR_S,
		       ((u32)hr_cq->db.dma) >> 1);
	cq_context->db_record_addr = cpu_to_le32(hr_cq->db.dma >> 32);

	roce_set_field(cq_context->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_MAX_CNT_M,
		       V2_CQC_BYTE_56_CQ_MAX_CNT_S,
		       HNS_ROCE_V2_CQ_DEFAULT_BURST_NUM);
	roce_set_field(cq_context->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_PERIOD_M,
		       V2_CQC_BYTE_56_CQ_PERIOD_S,
		       HNS_ROCE_V2_CQ_DEFAULT_INTERVAL);
}