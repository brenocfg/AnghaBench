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
struct hns_roce_des_qp {int requeue_flag; int /*<<< orphan*/  qp_wq; } ;
struct hns_roce_v1_priv {struct hns_roce_des_qp des_qp; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int hns_roce_des_qp_init(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_v1_priv *priv;
	struct hns_roce_des_qp *des_qp;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	des_qp = &priv->des_qp;

	des_qp->requeue_flag = 1;
	des_qp->qp_wq = create_singlethread_workqueue("hns_roce_destroy_qp");
	if (!des_qp->qp_wq) {
		dev_err(dev, "Create destroy qp workqueue failed!\n");
		return -ENOMEM;
	}

	return 0;
}