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
typedef  int u32 ;
struct TYPE_4__ {int num_cqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  array; } ;
struct hns_roce_dev {TYPE_2__ caps; TYPE_1__ cq_table; struct device* dev; } ;
struct hns_roce_cq {int /*<<< orphan*/  (* comp ) (struct hns_roce_cq*) ;int /*<<< orphan*/  arm_sn; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct hns_roce_cq*) ; 
 struct hns_roce_cq* xa_load (int /*<<< orphan*/ *,int) ; 

void hns_roce_cq_completion(struct hns_roce_dev *hr_dev, u32 cqn)
{
	struct device *dev = hr_dev->dev;
	struct hns_roce_cq *cq;

	cq = xa_load(&hr_dev->cq_table.array, cqn & (hr_dev->caps.num_cqs - 1));
	if (!cq) {
		dev_warn(dev, "Completion event for bogus CQ 0x%08x\n", cqn);
		return;
	}

	++cq->arm_sn;
	cq->comp(cq);
}