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
typedef  scalar_t__ u32 ;
struct hns_roce_qp {int /*<<< orphan*/  qpn; } ;
struct hns_roce_dev {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HNS_ROCE_V1_CHECK_DB_SLEEP_MSECS ; 
 int /*<<< orphan*/  HNS_ROCE_V1_CHECK_DB_TIMEOUT_MSECS ; 
 scalar_t__ HNS_ROCE_V1_DB_STAGE1 ; 
 scalar_t__ HNS_ROCE_V1_DB_STAGE2 ; 
 scalar_t__ HNS_ROCE_V1_DB_WAIT_OK ; 
 int /*<<< orphan*/  ROCEE_SDB_CNT_CMP_BITS ; 
 int /*<<< orphan*/  ROCEE_SDB_INV_CNT_REG ; 
 int /*<<< orphan*/  ROCEE_SDB_ISSUE_PTR_SDB_ISSUE_PTR_M ; 
 int /*<<< orphan*/  ROCEE_SDB_ISSUE_PTR_SDB_ISSUE_PTR_S ; 
 int /*<<< orphan*/  ROCEE_SDB_PTR_CMP_BITS ; 
 int /*<<< orphan*/  ROCEE_SDB_RETRY_CNT_REG ; 
 int /*<<< orphan*/  ROCEE_SDB_SEND_PTR_REG ; 
 int /*<<< orphan*/  ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M ; 
 int /*<<< orphan*/  ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S ; 
 int /*<<< orphan*/  ROCEE_TSP_BP_ST_QH_FIFO_ENTRY_S ; 
 int /*<<< orphan*/  ROCEE_TSP_BP_ST_REG ; 
 scalar_t__ SDB_INV_CNT_OFFSET ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hns_roce_check_sdb_status (struct hns_roce_dev*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ roce_hw_index_cmp_lt (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int check_qp_db_process_status(struct hns_roce_dev *hr_dev,
				      struct hns_roce_qp *hr_qp,
				      u32 sdb_issue_ptr,
				      u32 *sdb_inv_cnt,
				      u32 *wait_stage)
{
	struct device *dev = &hr_dev->pdev->dev;
	u32 sdb_send_ptr, old_send;
	__le32 sdb_issue_ptr_tmp;
	__le32 sdb_send_ptr_tmp;
	u32 success_flags = 0;
	unsigned long end;
	u32 old_retry;
	u32 inv_cnt;
	u32 tsp_st;
	__le32 tmp;

	if (*wait_stage > HNS_ROCE_V1_DB_STAGE2 ||
	    *wait_stage < HNS_ROCE_V1_DB_STAGE1) {
		dev_err(dev, "QP(0x%lx) db status wait stage(%d) error!\n",
			hr_qp->qpn, *wait_stage);
		return -EINVAL;
	}

	/* Calculate the total timeout for the entire verification process */
	end = msecs_to_jiffies(HNS_ROCE_V1_CHECK_DB_TIMEOUT_MSECS) + jiffies;

	if (*wait_stage == HNS_ROCE_V1_DB_STAGE1) {
		/* Query db process status, until hw process completely */
		sdb_send_ptr = roce_read(hr_dev, ROCEE_SDB_SEND_PTR_REG);
		while (roce_hw_index_cmp_lt(sdb_send_ptr, sdb_issue_ptr,
					    ROCEE_SDB_PTR_CMP_BITS)) {
			if (!time_before(jiffies, end)) {
				dev_dbg(dev, "QP(0x%lx) db process stage1 timeout. issue 0x%x send 0x%x.\n",
					hr_qp->qpn, sdb_issue_ptr,
					sdb_send_ptr);
				return 0;
			}

			msleep(HNS_ROCE_V1_CHECK_DB_SLEEP_MSECS);
			sdb_send_ptr = roce_read(hr_dev,
						 ROCEE_SDB_SEND_PTR_REG);
		}

		sdb_send_ptr_tmp = cpu_to_le32(sdb_send_ptr);
		sdb_issue_ptr_tmp = cpu_to_le32(sdb_issue_ptr);
		if (roce_get_field(sdb_issue_ptr_tmp,
				   ROCEE_SDB_ISSUE_PTR_SDB_ISSUE_PTR_M,
				   ROCEE_SDB_ISSUE_PTR_SDB_ISSUE_PTR_S) ==
		    roce_get_field(sdb_send_ptr_tmp,
				   ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M,
				   ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S)) {
			old_send = roce_read(hr_dev, ROCEE_SDB_SEND_PTR_REG);
			old_retry = roce_read(hr_dev, ROCEE_SDB_RETRY_CNT_REG);

			do {
				tsp_st = roce_read(hr_dev, ROCEE_TSP_BP_ST_REG);
				tmp = cpu_to_le32(tsp_st);
				if (roce_get_bit(tmp,
					ROCEE_TSP_BP_ST_QH_FIFO_ENTRY_S) == 1) {
					*wait_stage = HNS_ROCE_V1_DB_WAIT_OK;
					return 0;
				}

				if (!time_before(jiffies, end)) {
					dev_dbg(dev, "QP(0x%lx) db process stage1 timeout when send ptr equals issue ptr.\n"
						     "issue 0x%x send 0x%x.\n",
						hr_qp->qpn,
						le32_to_cpu(sdb_issue_ptr_tmp),
						le32_to_cpu(sdb_send_ptr_tmp));
					return 0;
				}

				msleep(HNS_ROCE_V1_CHECK_DB_SLEEP_MSECS);

				hns_roce_check_sdb_status(hr_dev, &old_send,
							  &old_retry, &tsp_st,
							  &success_flags);
			} while (!success_flags);
		}

		*wait_stage = HNS_ROCE_V1_DB_STAGE2;

		/* Get list pointer */
		*sdb_inv_cnt = roce_read(hr_dev, ROCEE_SDB_INV_CNT_REG);
		dev_dbg(dev, "QP(0x%lx) db process stage2. inv cnt = 0x%x.\n",
			hr_qp->qpn, *sdb_inv_cnt);
	}

	if (*wait_stage == HNS_ROCE_V1_DB_STAGE2) {
		/* Query db's list status, until hw reversal */
		inv_cnt = roce_read(hr_dev, ROCEE_SDB_INV_CNT_REG);
		while (roce_hw_index_cmp_lt(inv_cnt,
					    *sdb_inv_cnt + SDB_INV_CNT_OFFSET,
					    ROCEE_SDB_CNT_CMP_BITS)) {
			if (!time_before(jiffies, end)) {
				dev_dbg(dev, "QP(0x%lx) db process stage2 timeout. inv cnt 0x%x.\n",
					hr_qp->qpn, inv_cnt);
				return 0;
			}

			msleep(HNS_ROCE_V1_CHECK_DB_SLEEP_MSECS);
			inv_cnt = roce_read(hr_dev, ROCEE_SDB_INV_CNT_REG);
		}

		*wait_stage = HNS_ROCE_V1_DB_WAIT_OK;
	}

	return 0;
}