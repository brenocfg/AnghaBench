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
struct qed_hwfn {struct qed_ptt* p_main_ptt; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_RECOVERY_PROLOG_SLEEP_MS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int qed_pglueb_set_pfid_enable (struct qed_hwfn*,struct qed_ptt*,int) ; 

int qed_recovery_prolog(struct qed_dev *cdev)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt = p_hwfn->p_main_ptt;
	int rc;

	/* Allow ongoing PCIe transactions to complete */
	msleep(QED_RECOVERY_PROLOG_SLEEP_MS);

	/* Clear the PF's internal FID_enable in the PXP */
	rc = qed_pglueb_set_pfid_enable(p_hwfn, p_ptt, false);
	if (rc)
		DP_NOTICE(p_hwfn,
			  "qed_pglueb_set_pfid_enable() failed. rc = %d.\n",
			  rc);

	return rc;
}