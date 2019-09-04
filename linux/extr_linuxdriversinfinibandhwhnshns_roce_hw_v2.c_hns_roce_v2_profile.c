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
struct hns_roce_caps {int reserved_mrws; int flags; int* pkey_table_len; int /*<<< orphan*/  max_mtu; scalar_t__ local_ca_ack_delay; int /*<<< orphan*/  aeqe_depth; int /*<<< orphan*/  ceqe_depth; int /*<<< orphan*/ * gid_table_len; int /*<<< orphan*/  chunk_sz; scalar_t__ tsq_buf_pg_sz; int /*<<< orphan*/  eqe_hop_num; scalar_t__ eqe_buf_pg_sz; scalar_t__ eqe_ba_pg_sz; int /*<<< orphan*/  cqe_hop_num; scalar_t__ cqe_buf_pg_sz; scalar_t__ cqe_ba_pg_sz; int /*<<< orphan*/  mtt_hop_num; scalar_t__ mtt_buf_pg_sz; scalar_t__ mtt_ba_pg_sz; int /*<<< orphan*/  pbl_hop_num; scalar_t__ pbl_buf_pg_sz; scalar_t__ pbl_ba_pg_sz; void* mpt_hop_num; scalar_t__ mpt_buf_pg_sz; scalar_t__ mpt_ba_pg_sz; void* cqc_hop_num; scalar_t__ cqc_buf_pg_sz; scalar_t__ cqc_ba_pg_sz; int /*<<< orphan*/  srqc_hop_num; scalar_t__ srqc_buf_pg_sz; scalar_t__ srqc_ba_pg_sz; void* qpc_hop_num; scalar_t__ qpc_buf_pg_sz; scalar_t__ qpc_ba_pg_sz; scalar_t__ reserved_cqs; scalar_t__ reserved_uars; scalar_t__ reserved_pds; scalar_t__ reserved_lkey; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  cq_entry_sz; int /*<<< orphan*/  mtt_entry_sz; int /*<<< orphan*/  mtpt_entry_sz; int /*<<< orphan*/  cqc_entry_sz; int /*<<< orphan*/  trrl_entry_sz; int /*<<< orphan*/  irrl_entry_sz; int /*<<< orphan*/  qpc_entry_sz; int /*<<< orphan*/  max_srq_desc_sz; int /*<<< orphan*/  max_rq_desc_sz; int /*<<< orphan*/  max_sq_desc_sz; int /*<<< orphan*/  max_qp_dest_rdma; int /*<<< orphan*/  max_qp_init_rdma; int /*<<< orphan*/  num_pds; int /*<<< orphan*/  num_cqe_segs; int /*<<< orphan*/  num_mtt_segs; int /*<<< orphan*/  num_mtpts; int /*<<< orphan*/  num_other_vectors; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  num_aeq_vectors; int /*<<< orphan*/  phy_num_uars; int /*<<< orphan*/  num_uars; int /*<<< orphan*/  max_sq_inline; int /*<<< orphan*/  max_rq_sg; int /*<<< orphan*/  max_sq_sg; int /*<<< orphan*/  max_cqes; int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  max_wqes; int /*<<< orphan*/  num_qps; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; scalar_t__ sys_image_guid; scalar_t__ vendor_part_id; struct hns_roce_caps caps; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_RECORD_DB ; 
 int HNS_ROCE_CAP_FLAG_REREG_MR ; 
 int HNS_ROCE_CAP_FLAG_ROCE_V1_V2 ; 
 int HNS_ROCE_CAP_FLAG_RQ_INLINE ; 
 int HNS_ROCE_CAP_FLAG_SQ_RECORD_DB ; 
 void* HNS_ROCE_CONTEXT_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_CQE_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_EQE_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_HOP_NUM_0 ; 
 int /*<<< orphan*/  HNS_ROCE_MTT_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_PBL_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_ABNORMAL_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_ASYNC_EQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_COMP_EQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_COMP_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_CQC_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_CQE_ENTRY_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V2_GID_INDEX_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_IRRL_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_CQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_CQE_SEGS ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_CQ_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_MTPT_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_MTT_SEGS ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_PD_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_QP_DEST_RDMA ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_QP_INIT_RDMA ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_QP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_RQ_DESC_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_RQ_SGE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SQ_DESC_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SQ_INLINE ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SQ_SGE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQ_DESC_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_WQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MTPT_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MTT_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_PAGE_SIZE_SUPPORTED ; 
 int /*<<< orphan*/  HNS_ROCE_V2_PHY_UAR_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_QPC_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_TABLE_CHUNK_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V2_TRRL_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_UAR_NUM ; 
 int /*<<< orphan*/  IB_MTU_4096 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hns_roce_alloc_vf_resource (struct hns_roce_dev*) ; 
 int hns_roce_cmq_query_hw_info (struct hns_roce_dev*) ; 
 int hns_roce_config_global_param (struct hns_roce_dev*) ; 
 int hns_roce_query_pf_resource (struct hns_roce_dev*) ; 
 int hns_roce_v2_set_bt (struct hns_roce_dev*) ; 

__attribute__((used)) static int hns_roce_v2_profile(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_caps *caps = &hr_dev->caps;
	int ret;

	ret = hns_roce_cmq_query_hw_info(hr_dev);
	if (ret) {
		dev_err(hr_dev->dev, "Query firmware version fail, ret = %d.\n",
			ret);
		return ret;
	}

	ret = hns_roce_config_global_param(hr_dev);
	if (ret) {
		dev_err(hr_dev->dev, "Configure global param fail, ret = %d.\n",
			ret);
		return ret;
	}

	/* Get pf resource owned by every pf */
	ret = hns_roce_query_pf_resource(hr_dev);
	if (ret) {
		dev_err(hr_dev->dev, "Query pf resource fail, ret = %d.\n",
			ret);
		return ret;
	}

	ret = hns_roce_alloc_vf_resource(hr_dev);
	if (ret) {
		dev_err(hr_dev->dev, "Allocate vf resource fail, ret = %d.\n",
			ret);
		return ret;
	}

	hr_dev->vendor_part_id = 0;
	hr_dev->sys_image_guid = 0;

	caps->num_qps		= HNS_ROCE_V2_MAX_QP_NUM;
	caps->max_wqes		= HNS_ROCE_V2_MAX_WQE_NUM;
	caps->num_cqs		= HNS_ROCE_V2_MAX_CQ_NUM;
	caps->max_cqes		= HNS_ROCE_V2_MAX_CQE_NUM;
	caps->max_sq_sg		= HNS_ROCE_V2_MAX_SQ_SGE_NUM;
	caps->max_rq_sg		= HNS_ROCE_V2_MAX_RQ_SGE_NUM;
	caps->max_sq_inline	= HNS_ROCE_V2_MAX_SQ_INLINE;
	caps->num_uars		= HNS_ROCE_V2_UAR_NUM;
	caps->phy_num_uars	= HNS_ROCE_V2_PHY_UAR_NUM;
	caps->num_aeq_vectors	= HNS_ROCE_V2_AEQE_VEC_NUM;
	caps->num_comp_vectors	= HNS_ROCE_V2_COMP_VEC_NUM;
	caps->num_other_vectors	= HNS_ROCE_V2_ABNORMAL_VEC_NUM;
	caps->num_mtpts		= HNS_ROCE_V2_MAX_MTPT_NUM;
	caps->num_mtt_segs	= HNS_ROCE_V2_MAX_MTT_SEGS;
	caps->num_cqe_segs	= HNS_ROCE_V2_MAX_CQE_SEGS;
	caps->num_pds		= HNS_ROCE_V2_MAX_PD_NUM;
	caps->max_qp_init_rdma	= HNS_ROCE_V2_MAX_QP_INIT_RDMA;
	caps->max_qp_dest_rdma	= HNS_ROCE_V2_MAX_QP_DEST_RDMA;
	caps->max_sq_desc_sz	= HNS_ROCE_V2_MAX_SQ_DESC_SZ;
	caps->max_rq_desc_sz	= HNS_ROCE_V2_MAX_RQ_DESC_SZ;
	caps->max_srq_desc_sz	= HNS_ROCE_V2_MAX_SRQ_DESC_SZ;
	caps->qpc_entry_sz	= HNS_ROCE_V2_QPC_ENTRY_SZ;
	caps->irrl_entry_sz	= HNS_ROCE_V2_IRRL_ENTRY_SZ;
	caps->trrl_entry_sz	= HNS_ROCE_V2_TRRL_ENTRY_SZ;
	caps->cqc_entry_sz	= HNS_ROCE_V2_CQC_ENTRY_SZ;
	caps->mtpt_entry_sz	= HNS_ROCE_V2_MTPT_ENTRY_SZ;
	caps->mtt_entry_sz	= HNS_ROCE_V2_MTT_ENTRY_SZ;
	caps->cq_entry_sz	= HNS_ROCE_V2_CQE_ENTRY_SIZE;
	caps->page_size_cap	= HNS_ROCE_V2_PAGE_SIZE_SUPPORTED;
	caps->reserved_lkey	= 0;
	caps->reserved_pds	= 0;
	caps->reserved_mrws	= 1;
	caps->reserved_uars	= 0;
	caps->reserved_cqs	= 0;

	caps->qpc_ba_pg_sz	= 0;
	caps->qpc_buf_pg_sz	= 0;
	caps->qpc_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->srqc_ba_pg_sz	= 0;
	caps->srqc_buf_pg_sz	= 0;
	caps->srqc_hop_num	= HNS_ROCE_HOP_NUM_0;
	caps->cqc_ba_pg_sz	= 0;
	caps->cqc_buf_pg_sz	= 0;
	caps->cqc_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->mpt_ba_pg_sz	= 0;
	caps->mpt_buf_pg_sz	= 0;
	caps->mpt_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->pbl_ba_pg_sz	= 0;
	caps->pbl_buf_pg_sz	= 0;
	caps->pbl_hop_num	= HNS_ROCE_PBL_HOP_NUM;
	caps->mtt_ba_pg_sz	= 0;
	caps->mtt_buf_pg_sz	= 0;
	caps->mtt_hop_num	= HNS_ROCE_MTT_HOP_NUM;
	caps->cqe_ba_pg_sz	= 0;
	caps->cqe_buf_pg_sz	= 0;
	caps->cqe_hop_num	= HNS_ROCE_CQE_HOP_NUM;
	caps->eqe_ba_pg_sz	= 0;
	caps->eqe_buf_pg_sz	= 0;
	caps->eqe_hop_num	= HNS_ROCE_EQE_HOP_NUM;
	caps->tsq_buf_pg_sz	= 0;
	caps->chunk_sz		= HNS_ROCE_V2_TABLE_CHUNK_SIZE;

	caps->flags		= HNS_ROCE_CAP_FLAG_REREG_MR |
				  HNS_ROCE_CAP_FLAG_ROCE_V1_V2 |
				  HNS_ROCE_CAP_FLAG_RQ_INLINE |
				  HNS_ROCE_CAP_FLAG_RECORD_DB |
				  HNS_ROCE_CAP_FLAG_SQ_RECORD_DB;
	caps->pkey_table_len[0] = 1;
	caps->gid_table_len[0] = HNS_ROCE_V2_GID_INDEX_NUM;
	caps->ceqe_depth	= HNS_ROCE_V2_COMP_EQE_NUM;
	caps->aeqe_depth	= HNS_ROCE_V2_ASYNC_EQE_NUM;
	caps->local_ca_ack_delay = 0;
	caps->max_mtu = IB_MTU_4096;

	ret = hns_roce_v2_set_bt(hr_dev);
	if (ret)
		dev_err(hr_dev->dev, "Configure bt attribute fail, ret = %d.\n",
			ret);

	return ret;
}