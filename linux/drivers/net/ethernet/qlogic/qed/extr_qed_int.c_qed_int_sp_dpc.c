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
typedef  int u32 ;
typedef  int u16 ;
struct qed_sb_info {int sb_ack; int /*<<< orphan*/  igu_addr; int /*<<< orphan*/  sb_virt; } ;
struct qed_sb_attn_info {int index; int /*<<< orphan*/  sb_attn; } ;
struct qed_pi_info {int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* comp_cb ) (struct qed_hwfn*,int /*<<< orphan*/ ) ;} ;
struct qed_hwfn {TYPE_1__* p_sp_sb; int /*<<< orphan*/  cdev; int /*<<< orphan*/  p_dpc_ptt; int /*<<< orphan*/  my_id; struct qed_sb_attn_info* p_sb_attn; } ;
struct TYPE_2__ {struct qed_pi_info* pi_info_arr; struct qed_sb_info sb_info; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct qed_pi_info*) ; 
 int /*<<< orphan*/  DP_ERR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  IGU_INT_DISABLE ; 
 int /*<<< orphan*/  IGU_INT_ENABLE ; 
 int /*<<< orphan*/  NETIF_MSG_INTR ; 
 int QED_SB_ATT_IDX ; 
 int QED_SB_EVENT_MASK ; 
 int QED_SB_IDX ; 
 int qed_attn_update_idx (struct qed_hwfn*,struct qed_sb_attn_info*) ; 
 int /*<<< orphan*/  qed_int_attentions (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_sb_ack (struct qed_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_sb_ack_attn (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 
 int qed_sb_update_sb_idx (struct qed_sb_info*) ; 
 int /*<<< orphan*/  stub1 (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

void qed_int_sp_dpc(unsigned long hwfn_cookie)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)hwfn_cookie;
	struct qed_pi_info *pi_info = NULL;
	struct qed_sb_attn_info *sb_attn;
	struct qed_sb_info *sb_info;
	int arr_size;
	u16 rc = 0;

	if (!p_hwfn->p_sp_sb) {
		DP_ERR(p_hwfn->cdev, "DPC called - no p_sp_sb\n");
		return;
	}

	sb_info = &p_hwfn->p_sp_sb->sb_info;
	arr_size = ARRAY_SIZE(p_hwfn->p_sp_sb->pi_info_arr);
	if (!sb_info) {
		DP_ERR(p_hwfn->cdev,
		       "Status block is NULL - cannot ack interrupts\n");
		return;
	}

	if (!p_hwfn->p_sb_attn) {
		DP_ERR(p_hwfn->cdev, "DPC called - no p_sb_attn");
		return;
	}
	sb_attn = p_hwfn->p_sb_attn;

	DP_VERBOSE(p_hwfn, NETIF_MSG_INTR, "DPC Called! (hwfn %p %d)\n",
		   p_hwfn, p_hwfn->my_id);

	/* Disable ack for def status block. Required both for msix +
	 * inta in non-mask mode, in inta does no harm.
	 */
	qed_sb_ack(sb_info, IGU_INT_DISABLE, 0);

	/* Gather Interrupts/Attentions information */
	if (!sb_info->sb_virt) {
		DP_ERR(p_hwfn->cdev,
		       "Interrupt Status block is NULL - cannot check for new interrupts!\n");
	} else {
		u32 tmp_index = sb_info->sb_ack;

		rc = qed_sb_update_sb_idx(sb_info);
		DP_VERBOSE(p_hwfn->cdev, NETIF_MSG_INTR,
			   "Interrupt indices: 0x%08x --> 0x%08x\n",
			   tmp_index, sb_info->sb_ack);
	}

	if (!sb_attn || !sb_attn->sb_attn) {
		DP_ERR(p_hwfn->cdev,
		       "Attentions Status block is NULL - cannot check for new attentions!\n");
	} else {
		u16 tmp_index = sb_attn->index;

		rc |= qed_attn_update_idx(p_hwfn, sb_attn);
		DP_VERBOSE(p_hwfn->cdev, NETIF_MSG_INTR,
			   "Attention indices: 0x%08x --> 0x%08x\n",
			   tmp_index, sb_attn->index);
	}

	/* Check if we expect interrupts at this time. if not just ack them */
	if (!(rc & QED_SB_EVENT_MASK)) {
		qed_sb_ack(sb_info, IGU_INT_ENABLE, 1);
		return;
	}

	/* Check the validity of the DPC ptt. If not ack interrupts and fail */
	if (!p_hwfn->p_dpc_ptt) {
		DP_NOTICE(p_hwfn->cdev, "Failed to allocate PTT\n");
		qed_sb_ack(sb_info, IGU_INT_ENABLE, 1);
		return;
	}

	if (rc & QED_SB_ATT_IDX)
		qed_int_attentions(p_hwfn);

	if (rc & QED_SB_IDX) {
		int pi;

		/* Look for a free index */
		for (pi = 0; pi < arr_size; pi++) {
			pi_info = &p_hwfn->p_sp_sb->pi_info_arr[pi];
			if (pi_info->comp_cb)
				pi_info->comp_cb(p_hwfn, pi_info->cookie);
		}
	}

	if (sb_attn && (rc & QED_SB_ATT_IDX))
		/* This should be done before the interrupts are enabled,
		 * since otherwise a new attention will be generated.
		 */
		qed_sb_ack_attn(p_hwfn, sb_info->igu_addr, sb_attn->index);

	qed_sb_ack(sb_info, IGU_INT_ENABLE, 1);
}