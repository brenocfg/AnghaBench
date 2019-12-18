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
struct hns_roce_qp_table {int /*<<< orphan*/  irrl_table; int /*<<< orphan*/  trrl_table; } ;
struct TYPE_3__ {scalar_t__ qp_type; } ;
struct hns_roce_qp {int /*<<< orphan*/  qpn; TYPE_1__ ibqp; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {scalar_t__ trrl_entry_sz; } ;
struct hns_roce_dev {TYPE_2__ caps; struct hns_roce_qp_table qp_table; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_table_put (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void hns_roce_qp_free(struct hns_roce_dev *hr_dev, struct hns_roce_qp *hr_qp)
{
	struct hns_roce_qp_table *qp_table = &hr_dev->qp_table;

	if (atomic_dec_and_test(&hr_qp->refcount))
		complete(&hr_qp->free);
	wait_for_completion(&hr_qp->free);

	if ((hr_qp->ibqp.qp_type) != IB_QPT_GSI) {
		if (hr_dev->caps.trrl_entry_sz)
			hns_roce_table_put(hr_dev, &qp_table->trrl_table,
					   hr_qp->qpn);
		hns_roce_table_put(hr_dev, &qp_table->irrl_table, hr_qp->qpn);
	}
}