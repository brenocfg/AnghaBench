#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mtt_table; int /*<<< orphan*/  mtt_cqe_table; int /*<<< orphan*/  mtpt_table; } ;
struct TYPE_5__ {int /*<<< orphan*/  qp_table; int /*<<< orphan*/  irrl_table; int /*<<< orphan*/  trrl_table; } ;
struct TYPE_8__ {scalar_t__ trrl_entry_sz; } ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;
struct hns_roce_dev {TYPE_2__ mr_table; TYPE_1__ qp_table; TYPE_4__ caps; TYPE_3__ cq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEM_TYPE_CQE ; 
 scalar_t__ hns_roce_check_whether_mhop (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_cleanup_hem_table (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 

void hns_roce_cleanup_hem(struct hns_roce_dev *hr_dev)
{
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->cq_table.table);
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