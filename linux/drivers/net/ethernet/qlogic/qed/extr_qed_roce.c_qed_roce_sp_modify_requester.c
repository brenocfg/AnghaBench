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
typedef  int /*<<< orphan*/  u32 ;
struct roce_modify_qp_req_ramrod_data {int /*<<< orphan*/  dst_gid; int /*<<< orphan*/  src_gid; void* mtu; void* ack_timeout_val; void* flow_label; void* p_key; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  max_ord; scalar_t__ fields; scalar_t__ flags; } ;
struct TYPE_4__ {struct roce_modify_qp_req_ramrod_data roce_modify_qp_req; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_sp_init_data {int cid; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; } ;
struct qed_rdma_qp {int icid; int sqd_async; int retry_cnt; int rnr_retry_cnt; int /*<<< orphan*/  mtu; int /*<<< orphan*/  ack_timeout; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  pkey; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  max_rd_atomic_req; int /*<<< orphan*/  req_offloaded; } ;
struct TYPE_3__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_PKEY ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_RETRY_CNT ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  ROCE_EVENT_MODIFY_QP ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ACK_TIMEOUT_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ADDRESS_VECTOR_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_EN_SQD_ASYNC_NOTIFY ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_MAX_ORD_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_ERR_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_SQD_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_P_KEY_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_FLG ; 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_rdma_copy_gids (struct qed_rdma_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_roce_sp_modify_requester(struct qed_hwfn *p_hwfn,
					struct qed_rdma_qp *qp,
					bool move_to_sqd,
					bool move_to_err, u32 modify_flags)
{
	struct roce_modify_qp_req_ramrod_data *p_ramrod;
	struct qed_sp_init_data init_data;
	struct qed_spq_entry *p_ent;
	int rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	if (move_to_err && !(qp->req_offloaded))
		return 0;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid + 1;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ROCE_EVENT_MODIFY_QP,
				 PROTOCOLID_ROCE, &init_data);
	if (rc) {
		DP_NOTICE(p_hwfn, "rc = %d\n", rc);
		return rc;
	}

	p_ramrod = &p_ent->ramrod.roce_modify_qp_req;

	p_ramrod->flags = 0;

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_ERR_FLG, move_to_err);

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_SQD_FLG, move_to_sqd);

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_EN_SQD_ASYNC_NOTIFY,
		  qp->sqd_async);

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_P_KEY_FLG,
		  GET_FIELD(modify_flags, QED_ROCE_MODIFY_QP_VALID_PKEY));

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ADDRESS_VECTOR_FLG,
		  GET_FIELD(modify_flags,
			    QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR));

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_MAX_ORD_FLG,
		  GET_FIELD(modify_flags,
			    QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ));

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_FLG,
		  GET_FIELD(modify_flags,
			    QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT));

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_FLG,
		  GET_FIELD(modify_flags, QED_ROCE_MODIFY_QP_VALID_RETRY_CNT));

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ACK_TIMEOUT_FLG,
		  GET_FIELD(modify_flags,
			    QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT));

	p_ramrod->fields = 0;
	SET_FIELD(p_ramrod->fields,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT, qp->retry_cnt);

	SET_FIELD(p_ramrod->fields,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT,
		  qp->rnr_retry_cnt);

	p_ramrod->max_ord = qp->max_rd_atomic_req;
	p_ramrod->traffic_class = qp->traffic_class_tos;
	p_ramrod->hop_limit = qp->hop_limit_ttl;
	p_ramrod->p_key = cpu_to_le16(qp->pkey);
	p_ramrod->flow_label = cpu_to_le32(qp->flow_label);
	p_ramrod->ack_timeout_val = cpu_to_le32(qp->ack_timeout);
	p_ramrod->mtu = cpu_to_le16(qp->mtu);
	qed_rdma_copy_gids(qp, p_ramrod->src_gid, p_ramrod->dst_gid);
	rc = qed_spq_post(p_hwfn, p_ent, NULL);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Modify requester, rc = %d\n", rc);
	return rc;
}