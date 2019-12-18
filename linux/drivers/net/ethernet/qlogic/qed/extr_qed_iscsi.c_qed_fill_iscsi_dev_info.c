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
struct qed_hwfn {int dummy; } ;
struct qed_dev_iscsi_info {int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  secondary_bdq_rq_addr; int /*<<< orphan*/  primary_dbq_rq_addr; int /*<<< orphan*/  common; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDQ_ID_RQ ; 
 int /*<<< orphan*/  FEAT_NUM (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 struct qed_hwfn* QED_AFFIN_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_ISCSI_CQ ; 
 int /*<<< orphan*/  memset (struct qed_dev_iscsi_info*,int /*<<< orphan*/ ,int) ; 
 int qed_fill_dev_info (struct qed_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_iscsi_get_primary_bdq_prod (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iscsi_get_secondary_bdq_prod (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_fill_iscsi_dev_info(struct qed_dev *cdev,
				   struct qed_dev_iscsi_info *info)
{
	struct qed_hwfn *hwfn = QED_AFFIN_HWFN(cdev);

	int rc;

	memset(info, 0, sizeof(*info));
	rc = qed_fill_dev_info(cdev, &info->common);

	info->primary_dbq_rq_addr =
	    qed_iscsi_get_primary_bdq_prod(hwfn, BDQ_ID_RQ);
	info->secondary_bdq_rq_addr =
	    qed_iscsi_get_secondary_bdq_prod(hwfn, BDQ_ID_RQ);

	info->num_cqs = FEAT_NUM(hwfn, QED_ISCSI_CQ);

	return rc;
}