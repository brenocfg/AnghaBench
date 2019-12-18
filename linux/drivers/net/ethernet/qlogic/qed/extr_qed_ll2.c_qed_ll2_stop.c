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
struct qed_hwfn {int dummy; } ;
struct qed_dev {TYPE_1__* ll2; int /*<<< orphan*/  ll2_mac_address; } ;
struct TYPE_2__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 struct qed_hwfn* QED_AFFIN_HWFN (struct qed_dev*) ; 
 scalar_t__ QED_IS_ISCSI_PERSONALITY (struct qed_hwfn*) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 scalar_t__ QED_LL2_UNUSED_HANDLE ; 
 int __qed_ll2_stop (struct qed_hwfn*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int qed_ll2_is_storage_eng1 (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_ll2_kill_buffers (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_ll2_stop_ooo (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_llh_remove_mac_filter (struct qed_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_ll2_stop(struct qed_dev *cdev)
{
	bool b_is_storage_eng1 = qed_ll2_is_storage_eng1(cdev);
	struct qed_hwfn *p_hwfn = QED_AFFIN_HWFN(cdev);
	int rc = 0, rc2 = 0;

	if (cdev->ll2->handle == QED_LL2_UNUSED_HANDLE)
		return 0;

	qed_llh_remove_mac_filter(cdev, 0, cdev->ll2_mac_address);
	eth_zero_addr(cdev->ll2_mac_address);

	if (QED_IS_ISCSI_PERSONALITY(p_hwfn))
		qed_ll2_stop_ooo(p_hwfn);

	/* In CMT mode, LL2 is always started on engine 0 for a storage PF */
	if (b_is_storage_eng1) {
		rc2 = __qed_ll2_stop(QED_LEADING_HWFN(cdev));
		if (rc2)
			DP_NOTICE(QED_LEADING_HWFN(cdev),
				  "Failed to stop LL2 on engine 0\n");
	}

	rc = __qed_ll2_stop(p_hwfn);
	if (rc)
		DP_NOTICE(p_hwfn, "Failed to stop LL2\n");

	qed_ll2_kill_buffers(cdev);

	cdev->ll2->handle = QED_LL2_UNUSED_HANDLE;

	return rc | rc2;
}