#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rdma_close_func_ramrod_data {scalar_t__ cnq_start_offset; int /*<<< orphan*/  num_cnqs; } ;
struct TYPE_5__ {struct rdma_close_func_ramrod_data rdma_close_func; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; } ;
struct qed_ptt {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {int b_rdma_enabled_in_prs; TYPE_3__* p_rdma_info; TYPE_1__ hw_info; int /*<<< orphan*/  rdma_prs_search_reg; } ;
typedef  int /*<<< orphan*/  init_data ;
struct TYPE_6__ {int /*<<< orphan*/  num_cnqs; int /*<<< orphan*/  proto; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int EBUSY ; 
 int /*<<< orphan*/  PRS_REG_LIGHT_L2_ETHERTYPE_EN ; 
 int /*<<< orphan*/  PRS_REG_ROCE_DEST_QP_MAX_PF ; 
 scalar_t__ QED_IS_IWARP_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_RDMA_CNQ_RAM ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  RDMA_RAMROD_FUNC_CLOSE ; 
 scalar_t__ RESC_START (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_iwarp_stop (struct qed_hwfn*) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_rdma_free (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_roce_stop (struct qed_hwfn*) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_rdma_stop(void *rdma_cxt)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)rdma_cxt;
	struct rdma_close_func_ramrod_data *p_ramrod;
	struct qed_sp_init_data init_data;
	struct qed_spq_entry *p_ent;
	struct qed_ptt *p_ptt;
	u32 ll2_ethertype_en;
	int rc = -EBUSY;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA stop\n");

	p_ptt = qed_ptt_acquire(p_hwfn);
	if (!p_ptt) {
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Failed to acquire PTT\n");
		return rc;
	}

	/* Disable RoCE search */
	qed_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 0);
	p_hwfn->b_rdma_enabled_in_prs = false;
	p_hwfn->p_rdma_info->active = 0;
	qed_wr(p_hwfn, p_ptt, PRS_REG_ROCE_DEST_QP_MAX_PF, 0);

	ll2_ethertype_en = qed_rd(p_hwfn, p_ptt, PRS_REG_LIGHT_L2_ETHERTYPE_EN);

	qed_wr(p_hwfn, p_ptt, PRS_REG_LIGHT_L2_ETHERTYPE_EN,
	       (ll2_ethertype_en & 0xFFFE));

	if (QED_IS_IWARP_PERSONALITY(p_hwfn)) {
		rc = qed_iwarp_stop(p_hwfn);
		if (rc) {
			qed_ptt_release(p_hwfn, p_ptt);
			return rc;
		}
	} else {
		qed_roce_stop(p_hwfn);
	}

	qed_ptt_release(p_hwfn, p_ptt);

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	/* Stop RoCE */
	rc = qed_sp_init_request(p_hwfn, &p_ent, RDMA_RAMROD_FUNC_CLOSE,
				 p_hwfn->p_rdma_info->proto, &init_data);
	if (rc)
		goto out;

	p_ramrod = &p_ent->ramrod.rdma_close_func;

	p_ramrod->num_cnqs = p_hwfn->p_rdma_info->num_cnqs;
	p_ramrod->cnq_start_offset = (u8)RESC_START(p_hwfn, QED_RDMA_CNQ_RAM);

	rc = qed_spq_post(p_hwfn, p_ent, NULL);

out:
	qed_rdma_free(p_hwfn);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA stop done, rc = %d\n", rc);
	return rc;
}