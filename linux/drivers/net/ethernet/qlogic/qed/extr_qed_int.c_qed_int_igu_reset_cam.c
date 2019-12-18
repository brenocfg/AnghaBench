#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct qed_ptt {int dummy; } ;
struct TYPE_7__ {int cnt; scalar_t__ iov_cnt; scalar_t__ free_cnt; scalar_t__ free_cnt_iov; scalar_t__ orig; scalar_t__ iov_orig; } ;
struct qed_igu_info {int b_allow_pf_vf_change; scalar_t__ igu_dsb_id; TYPE_3__ usage; struct qed_igu_block* entry; } ;
struct qed_igu_block {int status; int function_id; int is_pf; int vector_number; } ;
struct TYPE_5__ {struct qed_igu_info* p_igu_info; } ;
struct qed_hwfn {int rel_pf_id; TYPE_4__* cdev; TYPE_1__ hw_info; } ;
struct TYPE_8__ {TYPE_2__* p_iov_info; } ;
struct TYPE_6__ {scalar_t__ total_vfs; int first_vf_in_pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*,int,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_FUNCTION_NUMBER ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_PF_VALID ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_VALID ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_VECTOR_NUMBER ; 
 scalar_t__ IGU_REG_MAPPING_MEMORY ; 
 scalar_t__ IS_PF_SRIOV (struct qed_hwfn*) ; 
 int /*<<< orphan*/  NETIF_MSG_INTR ; 
 int QED_IGU_STATUS_DSB ; 
 int QED_IGU_STATUS_FREE ; 
 int QED_IGU_STATUS_PF ; 
 int QED_IGU_STATUS_VALID ; 
 scalar_t__ QED_MAPPING_MEMORY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  QED_SB ; 
 int RESC_NUM (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,scalar_t__) ; 

int qed_int_igu_reset_cam(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	struct qed_igu_info *p_info = p_hwfn->hw_info.p_igu_info;
	struct qed_igu_block *p_block;
	int pf_sbs, vf_sbs;
	u16 igu_sb_id;
	u32 val, rval;

	if (!RESC_NUM(p_hwfn, QED_SB)) {
		p_info->b_allow_pf_vf_change = false;
	} else {
		/* Use the numbers the MFW have provided -
		 * don't forget MFW accounts for the default SB as well.
		 */
		p_info->b_allow_pf_vf_change = true;

		if (p_info->usage.cnt != RESC_NUM(p_hwfn, QED_SB) - 1) {
			DP_INFO(p_hwfn,
				"MFW notifies of 0x%04x PF SBs; IGU indicates of only 0x%04x\n",
				RESC_NUM(p_hwfn, QED_SB) - 1,
				p_info->usage.cnt);
			p_info->usage.cnt = RESC_NUM(p_hwfn, QED_SB) - 1;
		}

		if (IS_PF_SRIOV(p_hwfn)) {
			u16 vfs = p_hwfn->cdev->p_iov_info->total_vfs;

			if (vfs != p_info->usage.iov_cnt)
				DP_VERBOSE(p_hwfn,
					   NETIF_MSG_INTR,
					   "0x%04x VF SBs in IGU CAM != PCI configuration 0x%04x\n",
					   p_info->usage.iov_cnt, vfs);

			/* At this point we know how many SBs we have totally
			 * in IGU + number of PF SBs. So we can validate that
			 * we'd have sufficient for VF.
			 */
			if (vfs > p_info->usage.free_cnt +
			    p_info->usage.free_cnt_iov - p_info->usage.cnt) {
				DP_NOTICE(p_hwfn,
					  "Not enough SBs for VFs - 0x%04x SBs, from which %04x PFs and %04x are required\n",
					  p_info->usage.free_cnt +
					  p_info->usage.free_cnt_iov,
					  p_info->usage.cnt, vfs);
				return -EINVAL;
			}

			/* Currently cap the number of VFs SBs by the
			 * number of VFs.
			 */
			p_info->usage.iov_cnt = vfs;
		}
	}

	/* Mark all SBs as free, now in the right PF/VFs division */
	p_info->usage.free_cnt = p_info->usage.cnt;
	p_info->usage.free_cnt_iov = p_info->usage.iov_cnt;
	p_info->usage.orig = p_info->usage.cnt;
	p_info->usage.iov_orig = p_info->usage.iov_cnt;

	/* We now proceed to re-configure the IGU cam to reflect the initial
	 * configuration. We can start with the Default SB.
	 */
	pf_sbs = p_info->usage.cnt;
	vf_sbs = p_info->usage.iov_cnt;

	for (igu_sb_id = p_info->igu_dsb_id;
	     igu_sb_id < QED_MAPPING_MEMORY_SIZE(p_hwfn->cdev); igu_sb_id++) {
		p_block = &p_info->entry[igu_sb_id];
		val = 0;

		if (!(p_block->status & QED_IGU_STATUS_VALID))
			continue;

		if (p_block->status & QED_IGU_STATUS_DSB) {
			p_block->function_id = p_hwfn->rel_pf_id;
			p_block->is_pf = 1;
			p_block->vector_number = 0;
			p_block->status = QED_IGU_STATUS_VALID |
					  QED_IGU_STATUS_PF |
					  QED_IGU_STATUS_DSB;
		} else if (pf_sbs) {
			pf_sbs--;
			p_block->function_id = p_hwfn->rel_pf_id;
			p_block->is_pf = 1;
			p_block->vector_number = p_info->usage.cnt - pf_sbs;
			p_block->status = QED_IGU_STATUS_VALID |
					  QED_IGU_STATUS_PF |
					  QED_IGU_STATUS_FREE;
		} else if (vf_sbs) {
			p_block->function_id =
			    p_hwfn->cdev->p_iov_info->first_vf_in_pf +
			    p_info->usage.iov_cnt - vf_sbs;
			p_block->is_pf = 0;
			p_block->vector_number = 0;
			p_block->status = QED_IGU_STATUS_VALID |
					  QED_IGU_STATUS_FREE;
			vf_sbs--;
		} else {
			p_block->function_id = 0;
			p_block->is_pf = 0;
			p_block->vector_number = 0;
		}

		SET_FIELD(val, IGU_MAPPING_LINE_FUNCTION_NUMBER,
			  p_block->function_id);
		SET_FIELD(val, IGU_MAPPING_LINE_PF_VALID, p_block->is_pf);
		SET_FIELD(val, IGU_MAPPING_LINE_VECTOR_NUMBER,
			  p_block->vector_number);

		/* VF entries would be enabled when VF is initializaed */
		SET_FIELD(val, IGU_MAPPING_LINE_VALID, p_block->is_pf);

		rval = qed_rd(p_hwfn, p_ptt,
			      IGU_REG_MAPPING_MEMORY + sizeof(u32) * igu_sb_id);

		if (rval != val) {
			qed_wr(p_hwfn, p_ptt,
			       IGU_REG_MAPPING_MEMORY +
			       sizeof(u32) * igu_sb_id, val);

			DP_VERBOSE(p_hwfn,
				   NETIF_MSG_INTR,
				   "IGU reset: [SB 0x%04x] func_id = %d is_pf = %d vector_num = 0x%x [%08x -> %08x]\n",
				   igu_sb_id,
				   p_block->function_id,
				   p_block->is_pf,
				   p_block->vector_number, rval, val);
		}
	}

	return 0;
}