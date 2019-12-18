#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qed_hwfn {TYPE_2__* mcp_info; } ;
struct qed_dev_fcoe_info {int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  wwnn; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  secondary_bdq_rq_addr; int /*<<< orphan*/  primary_dbq_rq_addr; int /*<<< orphan*/  common; } ;
struct qed_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wwn_node; int /*<<< orphan*/  wwn_port; } ;
struct TYPE_4__ {TYPE_1__ func_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDQ_ID_RQ ; 
 int /*<<< orphan*/  FEAT_NUM (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 struct qed_hwfn* QED_AFFIN_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_FCOE_CQ ; 
 int /*<<< orphan*/  memset (struct qed_dev_fcoe_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_fcoe_get_primary_bdq_prod (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_fcoe_get_secondary_bdq_prod (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int qed_fill_dev_info (struct qed_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_fill_fcoe_dev_info(struct qed_dev *cdev,
				  struct qed_dev_fcoe_info *info)
{
	struct qed_hwfn *hwfn = QED_AFFIN_HWFN(cdev);
	int rc;

	memset(info, 0, sizeof(*info));
	rc = qed_fill_dev_info(cdev, &info->common);

	info->primary_dbq_rq_addr =
	    qed_fcoe_get_primary_bdq_prod(hwfn, BDQ_ID_RQ);
	info->secondary_bdq_rq_addr =
	    qed_fcoe_get_secondary_bdq_prod(hwfn, BDQ_ID_RQ);

	info->wwpn = hwfn->mcp_info->func_info.wwn_port;
	info->wwnn = hwfn->mcp_info->func_info.wwn_node;

	info->num_cqs = FEAT_NUM(hwfn, QED_FCOE_CQ);

	return rc;
}