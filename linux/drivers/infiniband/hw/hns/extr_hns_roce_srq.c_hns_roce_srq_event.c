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
struct hns_roce_srq_table {int /*<<< orphan*/  xa; } ;
struct hns_roce_srq {int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; int /*<<< orphan*/  (* event ) (struct hns_roce_srq*,int) ;} ;
struct TYPE_2__ {int num_srqs; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; TYPE_1__ caps; struct hns_roce_srq_table srq_table; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct hns_roce_srq*,int) ; 
 struct hns_roce_srq* xa_load (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xa_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock (int /*<<< orphan*/ *) ; 

void hns_roce_srq_event(struct hns_roce_dev *hr_dev, u32 srqn, int event_type)
{
	struct hns_roce_srq_table *srq_table = &hr_dev->srq_table;
	struct hns_roce_srq *srq;

	xa_lock(&srq_table->xa);
	srq = xa_load(&srq_table->xa, srqn & (hr_dev->caps.num_srqs - 1));
	if (srq)
		atomic_inc(&srq->refcount);
	xa_unlock(&srq_table->xa);

	if (!srq) {
		dev_warn(hr_dev->dev, "Async event for bogus SRQ %08x\n", srqn);
		return;
	}

	srq->event(srq, event_type);

	if (atomic_dec_and_test(&srq->refcount))
		complete(&srq->free);
}