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
struct hns_roce_qp_table {int /*<<< orphan*/  qp_table; int /*<<< orphan*/  irrl_table; int /*<<< orphan*/  trrl_table; int /*<<< orphan*/  sccc_table; } ;
struct hns_roce_qp {unsigned long qpn; } ;
struct TYPE_2__ {scalar_t__ trrl_entry_sz; scalar_t__ sccc_entry_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; struct hns_roce_qp_table qp_table; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_gsi_qp_alloc (struct hns_roce_dev*,unsigned long,struct hns_roce_qp*) ; 
 int hns_roce_table_get (struct hns_roce_dev*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  hns_roce_table_put (struct hns_roce_dev*,int /*<<< orphan*/ *,unsigned long) ; 

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

	if (hr_dev->caps.sccc_entry_sz) {
		/* Alloc memory for SCC CTX */
		ret = hns_roce_table_get(hr_dev, &qp_table->sccc_table,
					 hr_qp->qpn);
		if (ret) {
			dev_err(dev, "SCC CTX table get failed\n");
			goto err_put_trrl;
		}
	}

	ret = hns_roce_gsi_qp_alloc(hr_dev, qpn, hr_qp);
	if (ret)
		goto err_put_sccc;

	return 0;

err_put_sccc:
	if (hr_dev->caps.sccc_entry_sz)
		hns_roce_table_put(hr_dev, &qp_table->sccc_table,
				   hr_qp->qpn);

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