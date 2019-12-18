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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ srqc_hop_num; scalar_t__ qpc_hop_num; scalar_t__ cqc_hop_num; scalar_t__ mpt_hop_num; scalar_t__ sccc_hop_num; scalar_t__ qpc_ba_pg_sz; scalar_t__ qpc_buf_pg_sz; scalar_t__ srqc_ba_pg_sz; scalar_t__ srqc_buf_pg_sz; scalar_t__ cqc_ba_pg_sz; scalar_t__ cqc_buf_pg_sz; scalar_t__ mpt_ba_pg_sz; scalar_t__ mpt_buf_pg_sz; scalar_t__ sccc_ba_pg_sz; scalar_t__ sccc_buf_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;
struct hns_roce_cmq_desc {scalar_t__ data; } ;
struct hns_roce_cfg_bt_attr {int /*<<< orphan*/  vf_sccc_cfg; int /*<<< orphan*/  vf_mpt_cfg; int /*<<< orphan*/  vf_cqc_cfg; int /*<<< orphan*/  vf_srqc_cfg; int /*<<< orphan*/  vf_qpc_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_0_VF_QPC_BA_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_0_VF_QPC_BA_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_0_VF_QPC_BUF_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_0_VF_QPC_BUF_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_0_VF_QPC_HOPNUM_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_0_VF_QPC_HOPNUM_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_1_VF_SRQC_BA_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_1_VF_SRQC_BA_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_1_VF_SRQC_BUF_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_1_VF_SRQC_BUF_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_1_VF_SRQC_HOPNUM_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_1_VF_SRQC_HOPNUM_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_2_VF_CQC_BA_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_2_VF_CQC_BA_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_2_VF_CQC_BUF_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_2_VF_CQC_BUF_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_2_VF_CQC_HOPNUM_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_2_VF_CQC_HOPNUM_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_3_VF_MPT_BA_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_3_VF_MPT_BA_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_3_VF_MPT_BUF_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_3_VF_MPT_BUF_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_3_VF_MPT_HOPNUM_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_3_VF_MPT_HOPNUM_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_4_VF_SCCC_BA_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_4_VF_SCCC_BA_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_4_VF_SCCC_BUF_PGSZ_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_4_VF_SCCC_BUF_PGSZ_S ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_4_VF_SCCC_HOPNUM_M ; 
 int /*<<< orphan*/  CFG_BT_ATTR_DATA_4_VF_SCCC_HOPNUM_S ; 
 scalar_t__ HNS_ROCE_HOP_NUM_0 ; 
 int /*<<< orphan*/  HNS_ROCE_OPC_CFG_BT_ATTR ; 
 scalar_t__ PG_SHIFT_OFFSET ; 
 int hns_roce_cmq_send (struct hns_roce_dev*,struct hns_roce_cmq_desc*,int) ; 
 int /*<<< orphan*/  hns_roce_cmq_setup_basic_desc (struct hns_roce_cmq_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct hns_roce_cfg_bt_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hns_roce_v2_set_bt(struct hns_roce_dev *hr_dev)
{
	u8 srqc_hop_num = hr_dev->caps.srqc_hop_num;
	u8 qpc_hop_num = hr_dev->caps.qpc_hop_num;
	u8 cqc_hop_num = hr_dev->caps.cqc_hop_num;
	u8 mpt_hop_num = hr_dev->caps.mpt_hop_num;
	u8 sccc_hop_num = hr_dev->caps.sccc_hop_num;
	struct hns_roce_cfg_bt_attr *req;
	struct hns_roce_cmq_desc desc;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CFG_BT_ATTR, false);
	req = (struct hns_roce_cfg_bt_attr *)desc.data;
	memset(req, 0, sizeof(*req));

	roce_set_field(req->vf_qpc_cfg, CFG_BT_ATTR_DATA_0_VF_QPC_BA_PGSZ_M,
		       CFG_BT_ATTR_DATA_0_VF_QPC_BA_PGSZ_S,
		       hr_dev->caps.qpc_ba_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_qpc_cfg, CFG_BT_ATTR_DATA_0_VF_QPC_BUF_PGSZ_M,
		       CFG_BT_ATTR_DATA_0_VF_QPC_BUF_PGSZ_S,
		       hr_dev->caps.qpc_buf_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_qpc_cfg, CFG_BT_ATTR_DATA_0_VF_QPC_HOPNUM_M,
		       CFG_BT_ATTR_DATA_0_VF_QPC_HOPNUM_S,
		       qpc_hop_num == HNS_ROCE_HOP_NUM_0 ? 0 : qpc_hop_num);

	roce_set_field(req->vf_srqc_cfg, CFG_BT_ATTR_DATA_1_VF_SRQC_BA_PGSZ_M,
		       CFG_BT_ATTR_DATA_1_VF_SRQC_BA_PGSZ_S,
		       hr_dev->caps.srqc_ba_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_srqc_cfg, CFG_BT_ATTR_DATA_1_VF_SRQC_BUF_PGSZ_M,
		       CFG_BT_ATTR_DATA_1_VF_SRQC_BUF_PGSZ_S,
		       hr_dev->caps.srqc_buf_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_srqc_cfg, CFG_BT_ATTR_DATA_1_VF_SRQC_HOPNUM_M,
		       CFG_BT_ATTR_DATA_1_VF_SRQC_HOPNUM_S,
		       srqc_hop_num == HNS_ROCE_HOP_NUM_0 ? 0 : srqc_hop_num);

	roce_set_field(req->vf_cqc_cfg, CFG_BT_ATTR_DATA_2_VF_CQC_BA_PGSZ_M,
		       CFG_BT_ATTR_DATA_2_VF_CQC_BA_PGSZ_S,
		       hr_dev->caps.cqc_ba_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_cqc_cfg, CFG_BT_ATTR_DATA_2_VF_CQC_BUF_PGSZ_M,
		       CFG_BT_ATTR_DATA_2_VF_CQC_BUF_PGSZ_S,
		       hr_dev->caps.cqc_buf_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_cqc_cfg, CFG_BT_ATTR_DATA_2_VF_CQC_HOPNUM_M,
		       CFG_BT_ATTR_DATA_2_VF_CQC_HOPNUM_S,
		       cqc_hop_num == HNS_ROCE_HOP_NUM_0 ? 0 : cqc_hop_num);

	roce_set_field(req->vf_mpt_cfg, CFG_BT_ATTR_DATA_3_VF_MPT_BA_PGSZ_M,
		       CFG_BT_ATTR_DATA_3_VF_MPT_BA_PGSZ_S,
		       hr_dev->caps.mpt_ba_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_mpt_cfg, CFG_BT_ATTR_DATA_3_VF_MPT_BUF_PGSZ_M,
		       CFG_BT_ATTR_DATA_3_VF_MPT_BUF_PGSZ_S,
		       hr_dev->caps.mpt_buf_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_mpt_cfg, CFG_BT_ATTR_DATA_3_VF_MPT_HOPNUM_M,
		       CFG_BT_ATTR_DATA_3_VF_MPT_HOPNUM_S,
		       mpt_hop_num == HNS_ROCE_HOP_NUM_0 ? 0 : mpt_hop_num);

	roce_set_field(req->vf_sccc_cfg,
		       CFG_BT_ATTR_DATA_4_VF_SCCC_BA_PGSZ_M,
		       CFG_BT_ATTR_DATA_4_VF_SCCC_BA_PGSZ_S,
		       hr_dev->caps.sccc_ba_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_sccc_cfg,
		       CFG_BT_ATTR_DATA_4_VF_SCCC_BUF_PGSZ_M,
		       CFG_BT_ATTR_DATA_4_VF_SCCC_BUF_PGSZ_S,
		       hr_dev->caps.sccc_buf_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(req->vf_sccc_cfg,
		       CFG_BT_ATTR_DATA_4_VF_SCCC_HOPNUM_M,
		       CFG_BT_ATTR_DATA_4_VF_SCCC_HOPNUM_S,
		       sccc_hop_num ==
			      HNS_ROCE_HOP_NUM_0 ? 0 : sccc_hop_num);

	return hns_roce_cmq_send(hr_dev, &desc, 1);
}