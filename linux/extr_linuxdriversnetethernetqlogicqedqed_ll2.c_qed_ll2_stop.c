#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct qed_ptt {int dummy; } ;
struct qed_dev {TYPE_2__* ll2; int /*<<< orphan*/  ll2_mac_address; } ;
struct TYPE_9__ {scalar_t__ personality; } ;
struct TYPE_11__ {TYPE_1__ hw_info; } ;
struct TYPE_10__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_dev*,char*) ; 
 int EINVAL ; 
 TYPE_3__* QED_LEADING_HWFN (struct qed_dev*) ; 
 scalar_t__ QED_LL2_UNUSED_HANDLE ; 
 scalar_t__ QED_PCI_ISCSI ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ll2_kill_buffers (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_ll2_release_connection (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  qed_ll2_stop_ooo (struct qed_dev*) ; 
 int qed_ll2_terminate_connection (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  qed_llh_remove_mac_filter (TYPE_3__*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 struct qed_ptt* qed_ptt_acquire (TYPE_3__*) ; 
 int /*<<< orphan*/  qed_ptt_release (TYPE_3__*,struct qed_ptt*) ; 

__attribute__((used)) static int qed_ll2_stop(struct qed_dev *cdev)
{
	struct qed_ptt *p_ptt;
	int rc;

	if (cdev->ll2->handle == QED_LL2_UNUSED_HANDLE)
		return 0;

	p_ptt = qed_ptt_acquire(QED_LEADING_HWFN(cdev));
	if (!p_ptt) {
		DP_INFO(cdev, "Failed to acquire PTT\n");
		goto fail;
	}

	qed_llh_remove_mac_filter(QED_LEADING_HWFN(cdev), p_ptt,
				  cdev->ll2_mac_address);
	qed_ptt_release(QED_LEADING_HWFN(cdev), p_ptt);
	eth_zero_addr(cdev->ll2_mac_address);

	if (QED_LEADING_HWFN(cdev)->hw_info.personality == QED_PCI_ISCSI)
		qed_ll2_stop_ooo(cdev);

	rc = qed_ll2_terminate_connection(QED_LEADING_HWFN(cdev),
					  cdev->ll2->handle);
	if (rc)
		DP_INFO(cdev, "Failed to terminate LL2 connection\n");

	qed_ll2_kill_buffers(cdev);

	qed_ll2_release_connection(QED_LEADING_HWFN(cdev), cdev->ll2->handle);
	cdev->ll2->handle = QED_LL2_UNUSED_HANDLE;

	return rc;
fail:
	return -EINVAL;
}