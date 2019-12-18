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
struct qed_dev {int num_hwfns; } ;

/* Variables and functions */
 int FEAT_NUM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_AFFIN_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_PF_L2_QUE ; 

__attribute__((used)) static int qed_rdma_get_sb_start(struct qed_dev *cdev)
{
	int feat_num;

	if (cdev->num_hwfns > 1)
		feat_num = FEAT_NUM(QED_AFFIN_HWFN(cdev), QED_PF_L2_QUE);
	else
		feat_num = FEAT_NUM(QED_AFFIN_HWFN(cdev), QED_PF_L2_QUE) *
			   cdev->num_hwfns;

	return feat_num;
}