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
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_QED_SRIOV (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int qed_sriov_disable (struct qed_dev*,int) ; 
 int qed_sriov_enable (struct qed_dev*,int) ; 

__attribute__((used)) static int qed_sriov_configure(struct qed_dev *cdev, int num_vfs_param)
{
	if (!IS_QED_SRIOV(cdev)) {
		DP_VERBOSE(cdev, QED_MSG_IOV, "SR-IOV is not supported\n");
		return -EOPNOTSUPP;
	}

	if (num_vfs_param)
		return qed_sriov_enable(cdev, num_vfs_param);
	else
		return qed_sriov_disable(cdev, true);
}