#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qed_dev {int num_hwfns; int /*<<< orphan*/  firmware; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_arfs_ptt; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_PF (struct qed_dev*) ; 
 scalar_t__ IS_QED_ETH_IF (struct qed_dev*) ; 
 TYPE_1__* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_disable_msix (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_free_stream_mem (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_iov_wq_stop (struct qed_dev*,int) ; 
 int /*<<< orphan*/  qed_ll2_dealloc_if (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_nic_stop (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_ptt_release (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_resc_free (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_slowpath_irq_free (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_slowpath_wq_stop (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_sriov_disable (struct qed_dev*,int) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_slowpath_stop(struct qed_dev *cdev)
{
	if (!cdev)
		return -ENODEV;

	qed_slowpath_wq_stop(cdev);

	qed_ll2_dealloc_if(cdev);

	if (IS_PF(cdev)) {
		if (cdev->num_hwfns == 1)
			qed_ptt_release(QED_LEADING_HWFN(cdev),
					QED_LEADING_HWFN(cdev)->p_arfs_ptt);
		qed_free_stream_mem(cdev);
		if (IS_QED_ETH_IF(cdev))
			qed_sriov_disable(cdev, true);
	}

	qed_nic_stop(cdev);

	if (IS_PF(cdev))
		qed_slowpath_irq_free(cdev);

	qed_disable_msix(cdev);

	qed_resc_free(cdev);

	qed_iov_wq_stop(cdev, true);

	if (IS_PF(cdev))
		release_firmware(cdev->firmware);

	return 0;
}