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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct qed_sb_info {int dummy; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct qed_dev {size_t num_hwfns; struct qed_hwfn* hwfns; } ;
typedef  enum qed_sb_type { ____Placeholder_qed_sb_type } qed_sb_type ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int,size_t,size_t) ; 
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ IS_LEAD_HWFN (struct qed_hwfn*) ; 
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_INTR ; 
 struct qed_hwfn* QED_AFFIN_HWFN (struct qed_dev*) ; 
 int QED_SB_TYPE_L2_QUEUE ; 
 int /*<<< orphan*/  qed_int_sb_init (struct qed_hwfn*,struct qed_ptt*,struct qed_sb_info*,void*,int /*<<< orphan*/ ,size_t) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 

__attribute__((used)) static u32 qed_sb_init(struct qed_dev *cdev,
		       struct qed_sb_info *sb_info,
		       void *sb_virt_addr,
		       dma_addr_t sb_phy_addr, u16 sb_id,
		       enum qed_sb_type type)
{
	struct qed_hwfn *p_hwfn;
	struct qed_ptt *p_ptt;
	u16 rel_sb_id;
	u32 rc;

	/* RoCE/Storage use a single engine in CMT mode while L2 uses both */
	if (type == QED_SB_TYPE_L2_QUEUE) {
		p_hwfn = &cdev->hwfns[sb_id % cdev->num_hwfns];
		rel_sb_id = sb_id / cdev->num_hwfns;
	} else {
		p_hwfn = QED_AFFIN_HWFN(cdev);
		rel_sb_id = sb_id;
	}

	DP_VERBOSE(cdev, NETIF_MSG_INTR,
		   "hwfn [%d] <--[init]-- SB %04x [0x%04x upper]\n",
		   IS_LEAD_HWFN(p_hwfn) ? 0 : 1, rel_sb_id, sb_id);

	if (IS_PF(p_hwfn->cdev)) {
		p_ptt = qed_ptt_acquire(p_hwfn);
		if (!p_ptt)
			return -EBUSY;

		rc = qed_int_sb_init(p_hwfn, p_ptt, sb_info, sb_virt_addr,
				     sb_phy_addr, rel_sb_id);
		qed_ptt_release(p_hwfn, p_ptt);
	} else {
		rc = qed_int_sb_init(p_hwfn, NULL, sb_info, sb_virt_addr,
				     sb_phy_addr, rel_sb_id);
	}

	return rc;
}