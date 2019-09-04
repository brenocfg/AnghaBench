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
typedef  int /*<<< orphan*/  u8 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_dev*,char*) ; 
 int EINVAL ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int qed_llh_add_mac_filter (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_llh_remove_mac_filter (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 

__attribute__((used)) static int qed_roce_ll2_set_mac_filter(struct qed_dev *cdev,
				       u8 *old_mac_address,
				       u8 *new_mac_address)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt;
	int rc = 0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	if (!p_ptt) {
		DP_ERR(cdev,
		       "qed roce ll2 mac filter set: failed to acquire PTT\n");
		return -EINVAL;
	}

	if (old_mac_address)
		qed_llh_remove_mac_filter(p_hwfn, p_ptt, old_mac_address);
	if (new_mac_address)
		rc = qed_llh_add_mac_filter(p_hwfn, p_ptt, new_mac_address);

	qed_ptt_release(p_hwfn, p_ptt);

	if (rc)
		DP_ERR(cdev,
		       "qed roce ll2 mac filter set: failed to add MAC filter\n");

	return rc;
}