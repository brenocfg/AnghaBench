#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct rdma_init_func_hdr {size_t num_cnqs; int cq_ring_mode; scalar_t__ cnq_start_offset; } ;
struct rdma_init_func_ramrod_data {struct rdma_cnq_params* cnq_params; struct rdma_init_func_hdr params_header; } ;
struct rdma_cnq_params {void* queue_zone_num; int /*<<< orphan*/  pbl_base_addr; int /*<<< orphan*/  num_pbl_pages; int /*<<< orphan*/  sb_index; void* sb_num; } ;
struct TYPE_9__ {struct rdma_init_func_ramrod_data rdma; } ;
struct TYPE_14__ {struct rdma_init_func_ramrod_data rdma; } ;
struct TYPE_10__ {TYPE_2__ roce_init_func; TYPE_7__ iwarp_init_func; } ;
struct qed_spq_entry {TYPE_3__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; } ;
struct qed_rdma_start_in_params {size_t desired_cnq; scalar_t__ cq_mode; struct qed_rdma_cnq_params* cnq_pbl_list; } ;
struct qed_rdma_cnq_params {int /*<<< orphan*/  pbl_ptr; int /*<<< orphan*/  num_pbl_pages; } ;
struct qed_ptt {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  gl_pi; } ;
struct TYPE_12__ {TYPE_4__ rdma_pf_params; } ;
struct TYPE_8__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_6__* p_rdma_info; TYPE_5__ pf_params; TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
struct TYPE_13__ {size_t num_cnqs; scalar_t__ queue_zone_base; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ QED_IS_IWARP_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_RDMA_CNQ_RAM ; 
 scalar_t__ QED_RDMA_CQ_MODE_16_BITS ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  RDMA_RAMROD_FUNC_INIT ; 
 scalar_t__ RESC_START (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qed_get_igu_sb_id (struct qed_hwfn*,size_t) ; 
 int /*<<< orphan*/  qed_iwarp_init_fw_ramrod (struct qed_hwfn*,TYPE_7__*) ; 
 size_t qed_rdma_get_sb_id (struct qed_hwfn*,size_t) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_rdma_start_fw(struct qed_hwfn *p_hwfn,
			     struct qed_rdma_start_in_params *params,
			     struct qed_ptt *p_ptt)
{
	struct rdma_init_func_ramrod_data *p_ramrod;
	struct qed_rdma_cnq_params *p_cnq_pbl_list;
	struct rdma_init_func_hdr *p_params_header;
	struct rdma_cnq_params *p_cnq_params;
	struct qed_sp_init_data init_data;
	struct qed_spq_entry *p_ent;
	u32 cnq_id, sb_id;
	u16 igu_sb_id;
	int rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Starting FW\n");

	/* Save the number of cnqs for the function close ramrod */
	p_hwfn->p_rdma_info->num_cnqs = params->desired_cnq;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent, RDMA_RAMROD_FUNC_INIT,
				 p_hwfn->p_rdma_info->proto, &init_data);
	if (rc)
		return rc;

	if (QED_IS_IWARP_PERSONALITY(p_hwfn)) {
		qed_iwarp_init_fw_ramrod(p_hwfn,
					 &p_ent->ramrod.iwarp_init_func);
		p_ramrod = &p_ent->ramrod.iwarp_init_func.rdma;
	} else {
		p_ramrod = &p_ent->ramrod.roce_init_func.rdma;
	}

	p_params_header = &p_ramrod->params_header;
	p_params_header->cnq_start_offset = (u8)RESC_START(p_hwfn,
							   QED_RDMA_CNQ_RAM);
	p_params_header->num_cnqs = params->desired_cnq;

	if (params->cq_mode == QED_RDMA_CQ_MODE_16_BITS)
		p_params_header->cq_ring_mode = 1;
	else
		p_params_header->cq_ring_mode = 0;

	for (cnq_id = 0; cnq_id < params->desired_cnq; cnq_id++) {
		sb_id = qed_rdma_get_sb_id(p_hwfn, cnq_id);
		igu_sb_id = qed_get_igu_sb_id(p_hwfn, sb_id);
		p_ramrod->cnq_params[cnq_id].sb_num = cpu_to_le16(igu_sb_id);
		p_cnq_params = &p_ramrod->cnq_params[cnq_id];
		p_cnq_pbl_list = &params->cnq_pbl_list[cnq_id];

		p_cnq_params->sb_index = p_hwfn->pf_params.rdma_pf_params.gl_pi;
		p_cnq_params->num_pbl_pages = p_cnq_pbl_list->num_pbl_pages;

		DMA_REGPAIR_LE(p_cnq_params->pbl_base_addr,
			       p_cnq_pbl_list->pbl_ptr);

		/* we assume here that cnq_id and qz_offset are the same */
		p_cnq_params->queue_zone_num =
			cpu_to_le16(p_hwfn->p_rdma_info->queue_zone_base +
				    cnq_id);
	}

	return qed_spq_post(p_hwfn, p_ent, NULL);
}