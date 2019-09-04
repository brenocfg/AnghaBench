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
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_qp_work {scalar_t__ sche_cnt; int /*<<< orphan*/  db_wait_stage; int /*<<< orphan*/  sdb_inv_cnt; int /*<<< orphan*/  sdb_issue_ptr; } ;
struct hns_roce_qp {scalar_t__ state; int /*<<< orphan*/  qpn; int /*<<< orphan*/  ibqp; } ;
struct hns_roce_dev {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_V1_DB_STAGE1 ; 
 int /*<<< orphan*/  HNS_ROCE_V1_DB_WAIT_OK ; 
 scalar_t__ IB_QPS_ERR ; 
 scalar_t__ IB_QPS_RESET ; 
 int /*<<< orphan*/  ROCEE_SDB_ISSUE_PTR_REG ; 
 int check_qp_db_process_status (struct hns_roce_dev*,struct hns_roce_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int hns_roce_v1_modify_qp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_qp_reset_state(struct hns_roce_dev *hr_dev,
				struct hns_roce_qp *hr_qp,
				struct hns_roce_qp_work *qp_work_entry,
				int *is_timeout)
{
	struct device *dev = &hr_dev->pdev->dev;
	u32 sdb_issue_ptr;
	int ret;

	if (hr_qp->state != IB_QPS_RESET) {
		/* Set qp to ERR, waiting for hw complete processing all dbs */
		ret = hns_roce_v1_modify_qp(&hr_qp->ibqp, NULL, 0, hr_qp->state,
					    IB_QPS_ERR);
		if (ret) {
			dev_err(dev, "Modify QP(0x%lx) to ERR failed!\n",
				hr_qp->qpn);
			return ret;
		}

		/* Record issued doorbell */
		sdb_issue_ptr = roce_read(hr_dev, ROCEE_SDB_ISSUE_PTR_REG);
		qp_work_entry->sdb_issue_ptr = sdb_issue_ptr;
		qp_work_entry->db_wait_stage = HNS_ROCE_V1_DB_STAGE1;

		/* Query db process status, until hw process completely */
		ret = check_qp_db_process_status(hr_dev, hr_qp, sdb_issue_ptr,
						 &qp_work_entry->sdb_inv_cnt,
						 &qp_work_entry->db_wait_stage);
		if (ret) {
			dev_err(dev, "Check QP(0x%lx) db process status failed!\n",
				hr_qp->qpn);
			return ret;
		}

		if (qp_work_entry->db_wait_stage != HNS_ROCE_V1_DB_WAIT_OK) {
			qp_work_entry->sche_cnt = 0;
			*is_timeout = 1;
			return 0;
		}

		/* Modify qp to reset before destroying qp */
		ret = hns_roce_v1_modify_qp(&hr_qp->ibqp, NULL, 0, hr_qp->state,
					    IB_QPS_RESET);
		if (ret) {
			dev_err(dev, "Modify QP(0x%lx) to RST failed!\n",
				hr_qp->qpn);
			return ret;
		}
	}

	return 0;
}