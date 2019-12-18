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
typedef  int u64 ;
struct hns_roce_caps {int reserved_mrws; int reserved_qps; int num_ports; int* pkey_table_len; int* gid_table_len; int local_ca_ack_delay; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  aeqe_depth; int /*<<< orphan*/  ceqe_depth; int /*<<< orphan*/  chunk_sz; scalar_t__ reserved_cqs; scalar_t__ reserved_uars; scalar_t__ reserved_pds; scalar_t__ reserved_lkey; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  cq_entry_sz; int /*<<< orphan*/  mtt_entry_sz; int /*<<< orphan*/  mtpt_entry_sz; int /*<<< orphan*/  cqc_entry_sz; int /*<<< orphan*/  irrl_entry_sz; int /*<<< orphan*/  qpc_entry_sz; int /*<<< orphan*/  max_rq_desc_sz; int /*<<< orphan*/  max_sq_desc_sz; int /*<<< orphan*/  max_qp_dest_rdma; int /*<<< orphan*/  max_qp_init_rdma; int /*<<< orphan*/  num_pds; int /*<<< orphan*/  num_mtt_segs; int /*<<< orphan*/  num_mtpts; int /*<<< orphan*/  num_other_vectors; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  num_aeq_vectors; int /*<<< orphan*/  phy_num_uars; int /*<<< orphan*/  num_uars; int /*<<< orphan*/  max_sq_inline; void* max_rq_sg; void* max_sq_sg; int /*<<< orphan*/  max_cqes; int /*<<< orphan*/  min_cqes; int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  min_wqes; int /*<<< orphan*/  max_wqes; int /*<<< orphan*/  num_qps; } ;
struct hns_roce_dev {int vendor_id; int vendor_part_id; int sys_image_guid; int /*<<< orphan*/  hw_rev; struct hns_roce_caps caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_HW_VER1 ; 
 int /*<<< orphan*/  HNS_ROCE_MIN_CQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_MIN_WQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_ABNORMAL_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_AEQE_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_ASYNC_EQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_COMP_EQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_COMP_VEC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_CQC_ENTRY_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_CQE_ENTRY_SIZE ; 
 int HNS_ROCE_V1_GID_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_INLINE_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_IRRL_ENTRY_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_CQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_CQ_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_MTPT_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_MTT_SEGS ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_PD_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_QP_DEST_RDMA ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_QP_INIT_RDMA ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_QP_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_RQ_DESC_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_SQ_DESC_SZ ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MAX_WQE_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MTPT_ENTRY_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_MTT_ENTRY_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_PAGE_SIZE_SUPPORT ; 
 int /*<<< orphan*/  HNS_ROCE_V1_PHY_UAR_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_QPC_ENTRY_SIZE ; 
 void* HNS_ROCE_V1_SG_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_V1_TABLE_CHUNK_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_UAR_NUM ; 
 int /*<<< orphan*/  IB_MTU_2048 ; 
 int /*<<< orphan*/  ROCEE_ACK_DELAY_REG ; 
 int /*<<< orphan*/  ROCEE_SYS_IMAGE_GUID_H_REG ; 
 int /*<<< orphan*/  ROCEE_SYS_IMAGE_GUID_L_REG ; 
 int /*<<< orphan*/  ROCEE_VENDOR_ID_REG ; 
 int /*<<< orphan*/  ROCEE_VENDOR_PART_ID_REG ; 
 int roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v1_profile(struct hns_roce_dev *hr_dev)
{
	int i = 0;
	struct hns_roce_caps *caps = &hr_dev->caps;

	hr_dev->vendor_id = roce_read(hr_dev, ROCEE_VENDOR_ID_REG);
	hr_dev->vendor_part_id = roce_read(hr_dev, ROCEE_VENDOR_PART_ID_REG);
	hr_dev->sys_image_guid = roce_read(hr_dev, ROCEE_SYS_IMAGE_GUID_L_REG) |
				((u64)roce_read(hr_dev,
					    ROCEE_SYS_IMAGE_GUID_H_REG) << 32);
	hr_dev->hw_rev		= HNS_ROCE_HW_VER1;

	caps->num_qps		= HNS_ROCE_V1_MAX_QP_NUM;
	caps->max_wqes		= HNS_ROCE_V1_MAX_WQE_NUM;
	caps->min_wqes		= HNS_ROCE_MIN_WQE_NUM;
	caps->num_cqs		= HNS_ROCE_V1_MAX_CQ_NUM;
	caps->min_cqes		= HNS_ROCE_MIN_CQE_NUM;
	caps->max_cqes		= HNS_ROCE_V1_MAX_CQE_NUM;
	caps->max_sq_sg		= HNS_ROCE_V1_SG_NUM;
	caps->max_rq_sg		= HNS_ROCE_V1_SG_NUM;
	caps->max_sq_inline	= HNS_ROCE_V1_INLINE_SIZE;
	caps->num_uars		= HNS_ROCE_V1_UAR_NUM;
	caps->phy_num_uars	= HNS_ROCE_V1_PHY_UAR_NUM;
	caps->num_aeq_vectors	= HNS_ROCE_V1_AEQE_VEC_NUM;
	caps->num_comp_vectors	= HNS_ROCE_V1_COMP_VEC_NUM;
	caps->num_other_vectors	= HNS_ROCE_V1_ABNORMAL_VEC_NUM;
	caps->num_mtpts		= HNS_ROCE_V1_MAX_MTPT_NUM;
	caps->num_mtt_segs	= HNS_ROCE_V1_MAX_MTT_SEGS;
	caps->num_pds		= HNS_ROCE_V1_MAX_PD_NUM;
	caps->max_qp_init_rdma	= HNS_ROCE_V1_MAX_QP_INIT_RDMA;
	caps->max_qp_dest_rdma	= HNS_ROCE_V1_MAX_QP_DEST_RDMA;
	caps->max_sq_desc_sz	= HNS_ROCE_V1_MAX_SQ_DESC_SZ;
	caps->max_rq_desc_sz	= HNS_ROCE_V1_MAX_RQ_DESC_SZ;
	caps->qpc_entry_sz	= HNS_ROCE_V1_QPC_ENTRY_SIZE;
	caps->irrl_entry_sz	= HNS_ROCE_V1_IRRL_ENTRY_SIZE;
	caps->cqc_entry_sz	= HNS_ROCE_V1_CQC_ENTRY_SIZE;
	caps->mtpt_entry_sz	= HNS_ROCE_V1_MTPT_ENTRY_SIZE;
	caps->mtt_entry_sz	= HNS_ROCE_V1_MTT_ENTRY_SIZE;
	caps->cq_entry_sz	= HNS_ROCE_V1_CQE_ENTRY_SIZE;
	caps->page_size_cap	= HNS_ROCE_V1_PAGE_SIZE_SUPPORT;
	caps->reserved_lkey	= 0;
	caps->reserved_pds	= 0;
	caps->reserved_mrws	= 1;
	caps->reserved_uars	= 0;
	caps->reserved_cqs	= 0;
	caps->reserved_qps	= 12; /* 2 SQP per port, six ports total 12 */
	caps->chunk_sz		= HNS_ROCE_V1_TABLE_CHUNK_SIZE;

	for (i = 0; i < caps->num_ports; i++)
		caps->pkey_table_len[i] = 1;

	for (i = 0; i < caps->num_ports; i++) {
		/* Six ports shared 16 GID in v1 engine */
		if (i >= (HNS_ROCE_V1_GID_NUM % caps->num_ports))
			caps->gid_table_len[i] = HNS_ROCE_V1_GID_NUM /
						 caps->num_ports;
		else
			caps->gid_table_len[i] = HNS_ROCE_V1_GID_NUM /
						 caps->num_ports + 1;
	}

	caps->ceqe_depth = HNS_ROCE_V1_COMP_EQE_NUM;
	caps->aeqe_depth = HNS_ROCE_V1_ASYNC_EQE_NUM;
	caps->local_ca_ack_delay = roce_read(hr_dev, ROCEE_ACK_DELAY_REG);
	caps->max_mtu = IB_MTU_2048;

	return 0;
}