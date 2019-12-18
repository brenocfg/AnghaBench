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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {struct qed_dev* cdev; } ;
struct qed_dev {scalar_t__ recov_in_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  MISC_REG_AEU_GENERAL_ATTN_35 ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

int qed_start_recovery_process(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	struct qed_dev *cdev = p_hwfn->cdev;

	if (cdev->recov_in_prog) {
		DP_NOTICE(p_hwfn,
			  "Avoid triggering a recovery since such a process is already in progress\n");
		return -EAGAIN;
	}

	DP_NOTICE(p_hwfn, "Triggering a recovery process\n");
	qed_wr(p_hwfn, p_ptt, MISC_REG_AEU_GENERAL_ATTN_35, 0x1);

	return 0;
}