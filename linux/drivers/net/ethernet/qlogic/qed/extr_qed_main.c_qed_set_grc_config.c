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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_VF (struct qed_dev*) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int qed_dbg_grc_config (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 

__attribute__((used)) static int qed_set_grc_config(struct qed_dev *cdev, u32 cfg_id, u32 val)
{
	struct qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *ptt;
	int rc = 0;

	if (IS_VF(cdev))
		return 0;

	ptt = qed_ptt_acquire(hwfn);
	if (!ptt)
		return -EAGAIN;

	rc = qed_dbg_grc_config(hwfn, ptt, cfg_id, val);

	qed_ptt_release(hwfn, ptt);

	return rc;
}