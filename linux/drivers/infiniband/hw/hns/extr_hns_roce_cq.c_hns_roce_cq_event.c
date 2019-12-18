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
typedef  int u32 ;
struct TYPE_2__ {int num_cqs; } ;
struct hns_roce_cq_table {int /*<<< orphan*/  array; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; struct hns_roce_cq_table cq_table; } ;
struct hns_roce_cq {int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; int /*<<< orphan*/  (* event ) (struct hns_roce_cq*,int) ;} ;
struct device {int dummy; } ;
typedef  enum hns_roce_event { ____Placeholder_hns_roce_event } hns_roce_event ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct hns_roce_cq*,int) ; 
 struct hns_roce_cq* xa_load (int /*<<< orphan*/ *,int) ; 

void hns_roce_cq_event(struct hns_roce_dev *hr_dev, u32 cqn, int event_type)
{
	struct hns_roce_cq_table *cq_table = &hr_dev->cq_table;
	struct device *dev = hr_dev->dev;
	struct hns_roce_cq *cq;

	cq = xa_load(&cq_table->array, cqn & (hr_dev->caps.num_cqs - 1));
	if (cq)
		atomic_inc(&cq->refcount);

	if (!cq) {
		dev_warn(dev, "Async event for bogus CQ %08x\n", cqn);
		return;
	}

	cq->event(cq, (enum hns_roce_event)event_type);

	if (atomic_dec_and_test(&cq->refcount))
		complete(&cq->free);
}