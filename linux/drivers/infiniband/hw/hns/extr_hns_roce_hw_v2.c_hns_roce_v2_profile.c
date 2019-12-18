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
struct TYPE_4__ {int /*<<< orphan*/  node_guid; } ;
struct hns_roce_caps {int idx_entry_sz; int reserved_mrws; int pbl_ba_pg_sz; int wqe_sq_hop_num; int wqe_sge_hop_num; int wqe_rq_hop_num; int cqe_ba_pg_sz; int flags; int* pkey_table_len; int /*<<< orphan*/  sccc_hop_num; scalar_t__ sccc_buf_pg_sz; scalar_t__ sccc_ba_pg_sz; int /*<<< orphan*/  sccc_entry_sz; void* cqc_timer_hop_num; scalar_t__ cqc_timer_buf_pg_sz; scalar_t__ cqc_timer_ba_pg_sz; int /*<<< orphan*/  cqc_timer_entry_sz; int /*<<< orphan*/  num_cqc_timer; void* qpc_timer_hop_num; scalar_t__ qpc_timer_buf_pg_sz; scalar_t__ qpc_timer_ba_pg_sz; int /*<<< orphan*/  qpc_timer_entry_sz; int /*<<< orphan*/  num_qpc_timer; int /*<<< orphan*/  max_srq_sges; int /*<<< orphan*/  max_srq_wrs; int /*<<< orphan*/  max_srqs; int /*<<< orphan*/  max_mtu; scalar_t__ local_ca_ack_delay; int /*<<< orphan*/  aeqe_depth; int /*<<< orphan*/  ceqe_depth; int /*<<< orphan*/ * gid_table_len; int /*<<< orphan*/  chunk_sz; scalar_t__ tsq_buf_pg_sz; int /*<<< orphan*/  eqe_hop_num; scalar_t__ eqe_buf_pg_sz; scalar_t__ eqe_ba_pg_sz; int /*<<< orphan*/  idx_hop_num; scalar_t__ idx_buf_pg_sz; scalar_t__ idx_ba_pg_sz; int /*<<< orphan*/  srqwqe_hop_num; scalar_t__ srqwqe_buf_pg_sz; scalar_t__ srqwqe_ba_pg_sz; int /*<<< orphan*/  cqe_hop_num; scalar_t__ cqe_buf_pg_sz; int /*<<< orphan*/  mtt_hop_num; scalar_t__ mtt_buf_pg_sz; scalar_t__ mtt_ba_pg_sz; int /*<<< orphan*/  pbl_hop_num; scalar_t__ pbl_buf_pg_sz; void* mpt_hop_num; scalar_t__ mpt_buf_pg_sz; scalar_t__ mpt_ba_pg_sz; void* cqc_hop_num; scalar_t__ cqc_buf_pg_sz; scalar_t__ cqc_ba_pg_sz; void* srqc_hop_num; scalar_t__ srqc_buf_pg_sz; scalar_t__ srqc_ba_pg_sz; void* qpc_hop_num; scalar_t__ qpc_buf_pg_sz; scalar_t__ qpc_ba_pg_sz; int /*<<< orphan*/  reserved_qps; scalar_t__ reserved_srqs; scalar_t__ reserved_cqs; scalar_t__ reserved_uars; scalar_t__ reserved_pds; scalar_t__ reserved_lkey; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  cq_entry_sz; int /*<<< orphan*/  mtt_entry_sz; int /*<<< orphan*/  mtpt_entry_sz; int /*<<< orphan*/  srqc_entry_sz; int /*<<< orphan*/  cqc_entry_sz; int /*<<< orphan*/  trrl_entry_sz; int /*<<< orphan*/  irrl_entry_sz; int /*<<< orphan*/  qpc_entry_sz; int /*<<< orphan*/  max_srq_desc_sz; int /*<<< orphan*/  max_rq_desc_sz; int /*<<< orphan*/  max_sq_desc_sz; int /*<<< orphan*/  max_qp_dest_rdma; int /*<<< orphan*/  max_qp_init_rdma; int /*<<< orphan*/  num_pds; int /*<<< orphan*/  num_idx_segs; int /*<<< orphan*/  num_srqwqe_segs; int /*<<< orphan*/  num_cqe_segs; int /*<<< orphan*/  num_mtt_segs; int /*<<< orphan*/  num_mtpts; int /*<<< orphan*/  num_other_vectors; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  num_aeq_vectors; int /*<<< orphan*/  phy_num_uars; int /*<<< orphan*/  num_uars; int /*<<< orphan*/  max_srq_sg; int /*<<< orphan*/  max_sq_inline; int /*<<< orphan*/  max_rq_sg; int /*<<< orphan*/  max_extend_sg; int /*<<< orphan*/  max_sq_sg; int /*<<< orphan*/  max_srqwqes; int /*<<< orphan*/  max_cqes; int /*<<< orphan*/  min_cqes; int /*<<< orphan*/  num_srqs; int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  max_wqes; int /*<<< orphan*/  num_qps; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; TYPE_1__* pci_dev; TYPE_2__ ib_dev; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  vendor_part_id; struct hns_roce_caps caps; } ;
struct TYPE_3__ {int revision; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_ATOMIC ; 
 int HNS_ROCE_CAP_FLAG_FRMR ; 
 int HNS_ROCE_CAP_FLAG_MW ; 
 int HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL ; 
 int HNS_ROCE_CAP_FLAG_RECORD_DB ; 
 int HNS_ROCE_CAP_FLAG_REREG_MR ; 
 int HNS_ROCE_CAP_FLAG_ROCE_V1_V2 ; 
 int HNS_ROCE_CAP_FLAG_RQ_INLINE ; 
 int HNS_ROCE_CAP_FLAG_SQ_RECORD_DB ; 
 int HNS_ROCE_CAP_FLAG_SRQ ; 
 void* HNS_ROCE_CONTEXT_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_CQE_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_EQE_HOP_NUM ; 
 void* HNS_ROCE_HOP_NUM_0 ; 
 int /*<<< orphan*/  HNS_ROCE_IDX_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_MIN_CQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_MTT_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_PBL_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_SCCC_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_SRQWQE_HOP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_ABNORMAL_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_ASYNC_EQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_COMP_EQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_COMP_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_CQC_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_CQC_TIMER_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_CQE_ENTRY_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V2_GID_INDEX_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_IRRL_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_CQC_TIMER_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_CQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_CQE_SEGS ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_CQ_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_EXTEND_SGE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_IDX_SEGS ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_MTPT_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_MTT_SEGS ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_PD_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_QPC_TIMER_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_QP_DEST_RDMA ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_QP_INIT_RDMA ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_QP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_RQ_DESC_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_RQ_SGE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SQ_DESC_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SQ_INLINE ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SQ_SGE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQWQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQWQE_SEGS ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQ_DESC_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQ_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQ_SGE ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQ_SGE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_SRQ_WR ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MAX_WQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MTPT_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_MTT_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_PAGE_SIZE_SUPPORTED ; 
 int /*<<< orphan*/  HNS_ROCE_V2_PHY_UAR_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V2_QPC_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_QPC_TIMER_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_RSV_QPS ; 
 int /*<<< orphan*/  HNS_ROCE_V2_SCCC_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_SRQC_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_TABLE_CHUNK_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V2_TRRL_ENTRY_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V2_UAR_NUM ; 
 int /*<<< orphan*/  IB_MTU_4096 ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hns_roce_alloc_vf_resource (struct hns_roce_dev*) ; 
 int hns_roce_cmq_query_hw_info (struct hns_roce_dev*) ; 
 int hns_roce_config_global_param (struct hns_roce_dev*) ; 
 int hns_roce_query_fw_ver (struct hns_roce_dev*) ; 
 int hns_roce_query_pf_resource (struct hns_roce_dev*) ; 
 int hns_roce_query_pf_timer_resource (struct hns_roce_dev*) ; 
 int hns_roce_set_vf_switch_param (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int hns_roce_v2_set_bt (struct hns_roce_dev*) ; 

__attribute__((used)) static int hns_roce_v2_profile(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_caps *caps = &hr_dev->caps;
	int ret;

	ret = hns_roce_cmq_query_hw_info(hr_dev);
	if (ret) {
		dev_err(hr_dev->dev, "Query hardware version fail, ret = %d.\n",
			ret);
		return ret;
	}

	ret = hns_roce_query_fw_ver(hr_dev);
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

	if (hr_dev->pci_dev->revision == 0x21) {
		ret = hns_roce_query_pf_timer_resource(hr_dev);
		if (ret) {
			dev_err(hr_dev->dev,
				"Query pf timer resource fail, ret = %d.\n",
				ret);
			return ret;
		}
	}

	ret = hns_roce_alloc_vf_resource(hr_dev);
	if (ret) {
		dev_err(hr_dev->dev, "Allocate vf resource fail, ret = %d.\n",
			ret);
		return ret;
	}

	if (hr_dev->pci_dev->revision == 0x21) {
		ret = hns_roce_set_vf_switch_param(hr_dev, 0);
		if (ret) {
			dev_err(hr_dev->dev,
				"Set function switch param fail, ret = %d.\n",
				ret);
			return ret;
		}
	}

	hr_dev->vendor_part_id = hr_dev->pci_dev->device;
	hr_dev->sys_image_guid = be64_to_cpu(hr_dev->ib_dev.node_guid);

	caps->num_qps		= HNS_ROCE_V2_MAX_QP_NUM;
	caps->max_wqes		= HNS_ROCE_V2_MAX_WQE_NUM;
	caps->num_cqs		= HNS_ROCE_V2_MAX_CQ_NUM;
	caps->num_srqs		= HNS_ROCE_V2_MAX_SRQ_NUM;
	caps->min_cqes		= HNS_ROCE_MIN_CQE_NUM;
	caps->max_cqes		= HNS_ROCE_V2_MAX_CQE_NUM;
	caps->max_srqwqes	= HNS_ROCE_V2_MAX_SRQWQE_NUM;
	caps->max_sq_sg		= HNS_ROCE_V2_MAX_SQ_SGE_NUM;
	caps->max_extend_sg	= HNS_ROCE_V2_MAX_EXTEND_SGE_NUM;
	caps->max_rq_sg		= HNS_ROCE_V2_MAX_RQ_SGE_NUM;
	caps->max_sq_inline	= HNS_ROCE_V2_MAX_SQ_INLINE;
	caps->max_srq_sg	= HNS_ROCE_V2_MAX_SRQ_SGE_NUM;
	caps->num_uars		= HNS_ROCE_V2_UAR_NUM;
	caps->phy_num_uars	= HNS_ROCE_V2_PHY_UAR_NUM;
	caps->num_aeq_vectors	= HNS_ROCE_V2_AEQE_VEC_NUM;
	caps->num_comp_vectors	= HNS_ROCE_V2_COMP_VEC_NUM;
	caps->num_other_vectors	= HNS_ROCE_V2_ABNORMAL_VEC_NUM;
	caps->num_mtpts		= HNS_ROCE_V2_MAX_MTPT_NUM;
	caps->num_mtt_segs	= HNS_ROCE_V2_MAX_MTT_SEGS;
	caps->num_cqe_segs	= HNS_ROCE_V2_MAX_CQE_SEGS;
	caps->num_srqwqe_segs	= HNS_ROCE_V2_MAX_SRQWQE_SEGS;
	caps->num_idx_segs	= HNS_ROCE_V2_MAX_IDX_SEGS;
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
	caps->srqc_entry_sz	= HNS_ROCE_V2_SRQC_ENTRY_SZ;
	caps->mtpt_entry_sz	= HNS_ROCE_V2_MTPT_ENTRY_SZ;
	caps->mtt_entry_sz	= HNS_ROCE_V2_MTT_ENTRY_SZ;
	caps->idx_entry_sz	= 4;
	caps->cq_entry_sz	= HNS_ROCE_V2_CQE_ENTRY_SIZE;
	caps->page_size_cap	= HNS_ROCE_V2_PAGE_SIZE_SUPPORTED;
	caps->reserved_lkey	= 0;
	caps->reserved_pds	= 0;
	caps->reserved_mrws	= 1;
	caps->reserved_uars	= 0;
	caps->reserved_cqs	= 0;
	caps->reserved_srqs	= 0;
	caps->reserved_qps	= HNS_ROCE_V2_RSV_QPS;

	caps->qpc_ba_pg_sz	= 0;
	caps->qpc_buf_pg_sz	= 0;
	caps->qpc_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->srqc_ba_pg_sz	= 0;
	caps->srqc_buf_pg_sz	= 0;
	caps->srqc_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->cqc_ba_pg_sz	= 0;
	caps->cqc_buf_pg_sz	= 0;
	caps->cqc_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->mpt_ba_pg_sz	= 0;
	caps->mpt_buf_pg_sz	= 0;
	caps->mpt_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->pbl_ba_pg_sz	= 2;
	caps->pbl_buf_pg_sz	= 0;
	caps->pbl_hop_num	= HNS_ROCE_PBL_HOP_NUM;
	caps->mtt_ba_pg_sz	= 0;
	caps->mtt_buf_pg_sz	= 0;
	caps->mtt_hop_num	= HNS_ROCE_MTT_HOP_NUM;
	caps->wqe_sq_hop_num	= 2;
	caps->wqe_sge_hop_num	= 1;
	caps->wqe_rq_hop_num	= 2;
	caps->cqe_ba_pg_sz	= 6;
	caps->cqe_buf_pg_sz	= 0;
	caps->cqe_hop_num	= HNS_ROCE_CQE_HOP_NUM;
	caps->srqwqe_ba_pg_sz	= 0;
	caps->srqwqe_buf_pg_sz	= 0;
	caps->srqwqe_hop_num	= HNS_ROCE_SRQWQE_HOP_NUM;
	caps->idx_ba_pg_sz	= 0;
	caps->idx_buf_pg_sz	= 0;
	caps->idx_hop_num	= HNS_ROCE_IDX_HOP_NUM;
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

	if (hr_dev->pci_dev->revision == 0x21)
		caps->flags |= HNS_ROCE_CAP_FLAG_MW |
			       HNS_ROCE_CAP_FLAG_FRMR;

	caps->pkey_table_len[0] = 1;
	caps->gid_table_len[0] = HNS_ROCE_V2_GID_INDEX_NUM;
	caps->ceqe_depth	= HNS_ROCE_V2_COMP_EQE_NUM;
	caps->aeqe_depth	= HNS_ROCE_V2_ASYNC_EQE_NUM;
	caps->local_ca_ack_delay = 0;
	caps->max_mtu = IB_MTU_4096;

	caps->max_srqs		= HNS_ROCE_V2_MAX_SRQ;
	caps->max_srq_wrs	= HNS_ROCE_V2_MAX_SRQ_WR;
	caps->max_srq_sges	= HNS_ROCE_V2_MAX_SRQ_SGE;

	if (hr_dev->pci_dev->revision == 0x21) {
		caps->flags |= HNS_ROCE_CAP_FLAG_ATOMIC |
			       HNS_ROCE_CAP_FLAG_SRQ |
			       HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL;

		caps->num_qpc_timer	  = HNS_ROCE_V2_MAX_QPC_TIMER_NUM;
		caps->qpc_timer_entry_sz  = HNS_ROCE_V2_QPC_TIMER_ENTRY_SZ;
		caps->qpc_timer_ba_pg_sz  = 0;
		caps->qpc_timer_buf_pg_sz = 0;
		caps->qpc_timer_hop_num   = HNS_ROCE_HOP_NUM_0;
		caps->num_cqc_timer	  = HNS_ROCE_V2_MAX_CQC_TIMER_NUM;
		caps->cqc_timer_entry_sz  = HNS_ROCE_V2_CQC_TIMER_ENTRY_SZ;
		caps->cqc_timer_ba_pg_sz  = 0;
		caps->cqc_timer_buf_pg_sz = 0;
		caps->cqc_timer_hop_num   = HNS_ROCE_HOP_NUM_0;

		caps->sccc_entry_sz	= HNS_ROCE_V2_SCCC_ENTRY_SZ;
		caps->sccc_ba_pg_sz	= 0;
		caps->sccc_buf_pg_sz    = 0;
		caps->sccc_hop_num	= HNS_ROCE_SCCC_HOP_NUM;
	}

	ret = hns_roce_v2_set_bt(hr_dev);
	if (ret)
		dev_err(hr_dev->dev, "Configure bt attribute fail, ret = %d.\n",
			ret);

	return ret;
}