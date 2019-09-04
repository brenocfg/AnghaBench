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
struct hns_roce_qp_table {int /*<<< orphan*/  lock; } ;
struct hns_roce_qp {int qpn; } ;
struct TYPE_2__ {int num_qps; } ;
struct hns_roce_dev {TYPE_1__ caps; int /*<<< orphan*/  qp_table_tree; struct hns_roce_qp_table qp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void hns_roce_qp_remove(struct hns_roce_dev *hr_dev, struct hns_roce_qp *hr_qp)
{
	struct hns_roce_qp_table *qp_table = &hr_dev->qp_table;
	unsigned long flags;

	spin_lock_irqsave(&qp_table->lock, flags);
	radix_tree_delete(&hr_dev->qp_table_tree,
			  hr_qp->qpn & (hr_dev->caps.num_qps - 1));
	spin_unlock_irqrestore(&qp_table->lock, flags);
}