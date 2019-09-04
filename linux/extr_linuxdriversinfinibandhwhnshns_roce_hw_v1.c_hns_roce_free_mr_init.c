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
struct hns_roce_free_mr {int /*<<< orphan*/  free_mr_wq; } ;
struct hns_roce_v1_priv {struct hns_roce_free_mr free_mr; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int hns_roce_v1_rsv_lp_qp (struct hns_roce_dev*) ; 

__attribute__((used)) static int hns_roce_free_mr_init(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_free_mr *free_mr;
	struct hns_roce_v1_priv *priv;
	int ret = 0;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	free_mr = &priv->free_mr;

	free_mr->free_mr_wq = create_singlethread_workqueue("hns_roce_free_mr");
	if (!free_mr->free_mr_wq) {
		dev_err(dev, "Create free mr workqueue failed!\n");
		return -ENOMEM;
	}

	ret = hns_roce_v1_rsv_lp_qp(hr_dev);
	if (ret) {
		dev_err(dev, "Reserved loop qp failed(%d)!\n", ret);
		flush_workqueue(free_mr->free_mr_wq);
		destroy_workqueue(free_mr->free_mr_wq);
	}

	return ret;
}