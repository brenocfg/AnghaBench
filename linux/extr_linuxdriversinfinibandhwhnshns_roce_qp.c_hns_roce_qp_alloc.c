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
struct hns_roce_qp_table {int /*<<< orphan*/  qp_table; int /*<<< orphan*/  irrl_table; int /*<<< orphan*/  trrl_table; int /*<<< orphan*/  lock; } ;
struct hns_roce_qp {unsigned long qpn; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int num_qps; scalar_t__ trrl_entry_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; int /*<<< orphan*/  qp_table_tree; struct device* dev; struct hns_roce_qp_table qp_table; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_table_get (struct hns_roce_dev*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  hns_roce_table_put (struct hns_roce_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_qp_alloc(struct hns_roce_dev *hr_dev, unsigned long qpn,
			     struct hns_roce_qp *hr_qp)
{
	struct hns_roce_qp_table *qp_table = &hr_dev->qp_table;
	struct device *dev = hr_dev->dev;
	int ret;

	if (!qpn)
		return -EINVAL;

	hr_qp->qpn = qpn;

	/* Alloc memory for QPC */
	ret = hns_roce_table_get(hr_dev, &qp_table->qp_table, hr_qp->qpn);
	if (ret) {
		dev_err(dev, "QPC table get failed\n");
		goto err_out;
	}

	/* Alloc memory for IRRL */
	ret = hns_roce_table_get(hr_dev, &qp_table->irrl_table, hr_qp->qpn);
	if (ret) {
		dev_err(dev, "IRRL table get failed\n");
		goto err_put_qp;
	}

	if (hr_dev->caps.trrl_entry_sz) {
		/* Alloc memory for TRRL */
		ret = hns_roce_table_get(hr_dev, &qp_table->trrl_table,
					 hr_qp->qpn);
		if (ret) {
			dev_err(dev, "TRRL table get failed\n");
			goto err_put_irrl;
		}
	}

	spin_lock_irq(&qp_table->lock);
	ret = radix_tree_insert(&hr_dev->qp_table_tree,
				hr_qp->qpn & (hr_dev->caps.num_qps - 1), hr_qp);
	spin_unlock_irq(&qp_table->lock);
	if (ret) {
		dev_err(dev, "QPC radix_tree_insert failed\n");
		goto err_put_trrl;
	}

	atomic_set(&hr_qp->refcount, 1);
	init_completion(&hr_qp->free);

	return 0;

err_put_trrl:
	if (hr_dev->caps.trrl_entry_sz)
		hns_roce_table_put(hr_dev, &qp_table->trrl_table, hr_qp->qpn);

err_put_irrl:
	hns_roce_table_put(hr_dev, &qp_table->irrl_table, hr_qp->qpn);

err_put_qp:
	hns_roce_table_put(hr_dev, &qp_table->qp_table, hr_qp->qpn);

err_out:
	return ret;
}