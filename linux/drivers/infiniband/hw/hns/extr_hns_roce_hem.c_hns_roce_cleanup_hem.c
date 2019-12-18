#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mtt_table; int /*<<< orphan*/  mtt_cqe_table; int /*<<< orphan*/  mtpt_table; int /*<<< orphan*/  mtt_srqwqe_table; int /*<<< orphan*/  mtt_idx_table; } ;
struct TYPE_9__ {int /*<<< orphan*/  qp_table; int /*<<< orphan*/  irrl_table; int /*<<< orphan*/  trrl_table; int /*<<< orphan*/  sccc_table; } ;
struct TYPE_8__ {scalar_t__ trrl_entry_sz; scalar_t__ sccc_entry_sz; scalar_t__ cqc_timer_entry_sz; scalar_t__ qpc_timer_entry_sz; scalar_t__ srqc_entry_sz; scalar_t__ num_srqwqe_segs; scalar_t__ num_idx_segs; } ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct hns_roce_dev {TYPE_5__ mr_table; TYPE_4__ qp_table; TYPE_3__ caps; int /*<<< orphan*/  cqc_timer_table; int /*<<< orphan*/  qpc_timer_table; TYPE_2__ cq_table; TYPE_1__ srq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEM_TYPE_CQE ; 
 scalar_t__ hns_roce_check_whether_mhop (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_cleanup_hem_table (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 

void hns_roce_cleanup_hem(struct hns_roce_dev *hr_dev)
{
	if ((hr_dev->caps.num_idx_segs))
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->mr_table.mtt_idx_table);
	if (hr_dev->caps.num_srqwqe_segs)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->mr_table.mtt_srqwqe_table);
	if (hr_dev->caps.srqc_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->srq_table.table);
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->cq_table.table);
	if (hr_dev->caps.qpc_timer_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qpc_timer_table);
	if (hr_dev->caps.cqc_timer_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->cqc_timer_table);
	if (hr_dev->caps.sccc_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qp_table.sccc_table);
	if (hr_dev->caps.trrl_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qp_table.trrl_table);
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qp_table.irrl_table);
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qp_table.qp_table);
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->mr_table.mtpt_table);
	if (hns_roce_check_whether_mhop(hr_dev, HEM_TYPE_CQE))
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->mr_table.mtt_cqe_table);
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->mr_table.mtt_table);
}