#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct TYPE_12__ {size_t num_queues; size_t queue_relative_offset; size_t bdq_resource_id; int /*<<< orphan*/  q_validity; scalar_t__* bdq_pbl_num_entries; void* rq_buffer_size; void** bdq_xon_threshold; void** bdq_xoff_threshold; int /*<<< orphan*/ * bdq_pbl_base_address; int /*<<< orphan*/  cmdq_sb_pi; int /*<<< orphan*/  cq_sb_pi; void** cq_cmdq_sb_num_arr; void* cmdq_num_entries; void* cq_num_entries; int /*<<< orphan*/  glbl_q_params_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  debug_mode; int /*<<< orphan*/  log_page_size; void* num_tasks; } ;
struct fcoe_init_func_ramrod_data {TYPE_6__ q_params; TYPE_4__ func_params; void* sq_num_pages_in_pbl; void* mtu; } ;
struct fcoe_init_ramrod_params {struct fcoe_init_func_ramrod_data init_ramrod_data; } ;
struct TYPE_7__ {struct fcoe_init_ramrod_params fcoe_init; } ;
struct qed_spq_entry {TYPE_1__ ramrod; } ;
struct qed_spq_comp_cb {int dummy; } ;
struct qed_sp_init_data {int comp_mode; struct qed_spq_comp_cb* p_comp_data; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_11__ {scalar_t__* feat_num; scalar_t__* resc_start; int /*<<< orphan*/  opaque_fid; } ;
struct qed_fcoe_pf_params {scalar_t__ num_cqs; void* mtu; void* sq_num_pbl_pages; void* num_tasks; void* cq_num_entries; void* cmdq_num_entries; scalar_t__ is_target; void* rq_buffer_size; void** bdq_xon_threshold; void** bdq_xoff_threshold; scalar_t__* bdq_pbl_num_entries; int /*<<< orphan*/ * bdq_pbl_base_addr; int /*<<< orphan*/  gl_cmd_pi; int /*<<< orphan*/  gl_rq_pi; int /*<<< orphan*/  glbl_q_params_addr; int /*<<< orphan*/  debug_mode; int /*<<< orphan*/  log_page_size; void* dummy_icid; } ;
struct TYPE_8__ {struct qed_fcoe_pf_params fcoe_pf_params; } ;
struct qed_hwfn {TYPE_5__ hw_info; TYPE_2__ pf_params; } ;
struct qed_cxt_info {struct e4_fcoe_conn_context* p_cxt; scalar_t__ iid; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags3; } ;
struct e4_fcoe_conn_context {TYPE_3__ tstorm_ag_context; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum spq_mode { ____Placeholder_spq_mode } spq_mode ;

/* Variables and functions */
 size_t BDQ_ID_IMM_DATA ; 
 size_t BDQ_ID_RQ ; 
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,scalar_t__) ; 
 int /*<<< orphan*/  E4_TSTORM_FCOE_CONN_AG_CTX_DUMMY_TIMER_CF_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  FCOE_RAMROD_CMD_ID_INIT_FUNC ; 
 int /*<<< orphan*/  PROTOCOLID_FCOE ; 
 int /*<<< orphan*/  QED_BDQ ; 
 size_t QED_CMDQS_CQS ; 
 size_t QED_FCOE_CQ ; 
 scalar_t__ RESC_START (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_INIT_FUNC_QUEUES_CMD_VALID ; 
 int /*<<< orphan*/  SCSI_INIT_FUNC_QUEUES_IMM_DATA_VALID ; 
 int /*<<< orphan*/  SCSI_INIT_FUNC_QUEUES_RQ_VALID ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le16 (void*) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_cxt_acquire_cid (struct qed_hwfn*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int qed_cxt_get_cid_info (struct qed_hwfn*,struct qed_cxt_info*) ; 
 void* qed_get_igu_sb_id (struct qed_hwfn*,size_t) ; 
 int /*<<< orphan*/  qed_sp_destroy_request (struct qed_hwfn*,struct qed_spq_entry*) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int /*<<< orphan*/  qed_spq_get_cid (struct qed_hwfn*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_sp_fcoe_func_start(struct qed_hwfn *p_hwfn,
		       enum spq_mode comp_mode,
		       struct qed_spq_comp_cb *p_comp_addr)
{
	struct qed_fcoe_pf_params *fcoe_pf_params = NULL;
	struct fcoe_init_ramrod_params *p_ramrod = NULL;
	struct fcoe_init_func_ramrod_data *p_data;
	struct e4_fcoe_conn_context *p_cxt = NULL;
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	struct qed_cxt_info cxt_info;
	u32 dummy_cid;
	int rc = 0;
	u16 tmp;
	u8 i;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 FCOE_RAMROD_CMD_ID_INIT_FUNC,
				 PROTOCOLID_FCOE, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.fcoe_init;
	p_data = &p_ramrod->init_ramrod_data;
	fcoe_pf_params = &p_hwfn->pf_params.fcoe_pf_params;

	/* Sanity */
	if (fcoe_pf_params->num_cqs > p_hwfn->hw_info.feat_num[QED_FCOE_CQ]) {
		DP_ERR(p_hwfn,
		       "Cannot satisfy CQ amount. CQs requested %d, CQs available %d. Aborting function start\n",
		       fcoe_pf_params->num_cqs,
		       p_hwfn->hw_info.feat_num[QED_FCOE_CQ]);
		rc = -EINVAL;
		goto err;
	}

	p_data->mtu = cpu_to_le16(fcoe_pf_params->mtu);
	tmp = cpu_to_le16(fcoe_pf_params->sq_num_pbl_pages);
	p_data->sq_num_pages_in_pbl = tmp;

	rc = qed_cxt_acquire_cid(p_hwfn, PROTOCOLID_FCOE, &dummy_cid);
	if (rc)
		goto err;

	cxt_info.iid = dummy_cid;
	rc = qed_cxt_get_cid_info(p_hwfn, &cxt_info);
	if (rc) {
		DP_NOTICE(p_hwfn, "Cannot find context info for dummy cid=%d\n",
			  dummy_cid);
		goto err;
	}
	p_cxt = cxt_info.p_cxt;
	SET_FIELD(p_cxt->tstorm_ag_context.flags3,
		  E4_TSTORM_FCOE_CONN_AG_CTX_DUMMY_TIMER_CF_EN, 1);

	fcoe_pf_params->dummy_icid = (u16)dummy_cid;

	tmp = cpu_to_le16(fcoe_pf_params->num_tasks);
	p_data->func_params.num_tasks = tmp;
	p_data->func_params.log_page_size = fcoe_pf_params->log_page_size;
	p_data->func_params.debug_mode = fcoe_pf_params->debug_mode;

	DMA_REGPAIR_LE(p_data->q_params.glbl_q_params_addr,
		       fcoe_pf_params->glbl_q_params_addr);

	tmp = cpu_to_le16(fcoe_pf_params->cq_num_entries);
	p_data->q_params.cq_num_entries = tmp;

	tmp = cpu_to_le16(fcoe_pf_params->cmdq_num_entries);
	p_data->q_params.cmdq_num_entries = tmp;

	tmp = fcoe_pf_params->num_cqs;
	p_data->q_params.num_queues = (u8)tmp;

	tmp = (u16)p_hwfn->hw_info.resc_start[QED_CMDQS_CQS];
	p_data->q_params.queue_relative_offset = (u8)tmp;

	for (i = 0; i < fcoe_pf_params->num_cqs; i++) {
		u16 igu_sb_id;

		igu_sb_id = qed_get_igu_sb_id(p_hwfn, i);
		tmp = cpu_to_le16(igu_sb_id);
		p_data->q_params.cq_cmdq_sb_num_arr[i] = tmp;
	}

	p_data->q_params.cq_sb_pi = fcoe_pf_params->gl_rq_pi;
	p_data->q_params.cmdq_sb_pi = fcoe_pf_params->gl_cmd_pi;

	p_data->q_params.bdq_resource_id = (u8)RESC_START(p_hwfn, QED_BDQ);

	DMA_REGPAIR_LE(p_data->q_params.bdq_pbl_base_address[BDQ_ID_RQ],
		       fcoe_pf_params->bdq_pbl_base_addr[BDQ_ID_RQ]);
	p_data->q_params.bdq_pbl_num_entries[BDQ_ID_RQ] =
	    fcoe_pf_params->bdq_pbl_num_entries[BDQ_ID_RQ];
	tmp = fcoe_pf_params->bdq_xoff_threshold[BDQ_ID_RQ];
	p_data->q_params.bdq_xoff_threshold[BDQ_ID_RQ] = cpu_to_le16(tmp);
	tmp = fcoe_pf_params->bdq_xon_threshold[BDQ_ID_RQ];
	p_data->q_params.bdq_xon_threshold[BDQ_ID_RQ] = cpu_to_le16(tmp);

	DMA_REGPAIR_LE(p_data->q_params.bdq_pbl_base_address[BDQ_ID_IMM_DATA],
		       fcoe_pf_params->bdq_pbl_base_addr[BDQ_ID_IMM_DATA]);
	p_data->q_params.bdq_pbl_num_entries[BDQ_ID_IMM_DATA] =
	    fcoe_pf_params->bdq_pbl_num_entries[BDQ_ID_IMM_DATA];
	tmp = fcoe_pf_params->bdq_xoff_threshold[BDQ_ID_IMM_DATA];
	p_data->q_params.bdq_xoff_threshold[BDQ_ID_IMM_DATA] = cpu_to_le16(tmp);
	tmp = fcoe_pf_params->bdq_xon_threshold[BDQ_ID_IMM_DATA];
	p_data->q_params.bdq_xon_threshold[BDQ_ID_IMM_DATA] = cpu_to_le16(tmp);
	tmp = fcoe_pf_params->rq_buffer_size;
	p_data->q_params.rq_buffer_size = cpu_to_le16(tmp);

	if (fcoe_pf_params->is_target) {
		SET_FIELD(p_data->q_params.q_validity,
			  SCSI_INIT_FUNC_QUEUES_RQ_VALID, 1);
		if (p_data->q_params.bdq_pbl_num_entries[BDQ_ID_IMM_DATA])
			SET_FIELD(p_data->q_params.q_validity,
				  SCSI_INIT_FUNC_QUEUES_IMM_DATA_VALID, 1);
		SET_FIELD(p_data->q_params.q_validity,
			  SCSI_INIT_FUNC_QUEUES_CMD_VALID, 1);
	} else {
		SET_FIELD(p_data->q_params.q_validity,
			  SCSI_INIT_FUNC_QUEUES_RQ_VALID, 1);
	}

	rc = qed_spq_post(p_hwfn, p_ent, NULL);

	return rc;

err:
	qed_sp_destroy_request(p_hwfn, p_ent);
	return rc;
}