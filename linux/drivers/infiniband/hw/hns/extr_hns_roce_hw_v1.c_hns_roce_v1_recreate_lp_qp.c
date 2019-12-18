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
struct hns_roce_recreate_lp_qp_work {int comp_flag; int /*<<< orphan*/  work; struct completion* comp; int /*<<< orphan*/ * ib_dev; } ;
struct hns_roce_dev {int /*<<< orphan*/  ib_dev; scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct completion {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 long HNS_ROCE_V1_RECREATE_LP_QP_TIMEOUT_MSECS ; 
 scalar_t__ HNS_ROCE_V1_RECREATE_LP_QP_WAIT_VALUE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  hns_roce_v1_recreate_lp_qp_work_fn ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 struct hns_roce_recreate_lp_qp_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ try_wait_for_completion (struct completion*) ; 

__attribute__((used)) static int hns_roce_v1_recreate_lp_qp(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_recreate_lp_qp_work *lp_qp_work;
	struct hns_roce_free_mr *free_mr;
	struct hns_roce_v1_priv *priv;
	struct completion comp;
	long end = HNS_ROCE_V1_RECREATE_LP_QP_TIMEOUT_MSECS;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	free_mr = &priv->free_mr;

	lp_qp_work = kzalloc(sizeof(struct hns_roce_recreate_lp_qp_work),
			     GFP_KERNEL);
	if (!lp_qp_work)
		return -ENOMEM;

	INIT_WORK(&(lp_qp_work->work), hns_roce_v1_recreate_lp_qp_work_fn);

	lp_qp_work->ib_dev = &(hr_dev->ib_dev);
	lp_qp_work->comp = &comp;
	lp_qp_work->comp_flag = 1;

	init_completion(lp_qp_work->comp);

	queue_work(free_mr->free_mr_wq, &(lp_qp_work->work));

	while (end > 0) {
		if (try_wait_for_completion(&comp))
			return 0;
		msleep(HNS_ROCE_V1_RECREATE_LP_QP_WAIT_VALUE);
		end -= HNS_ROCE_V1_RECREATE_LP_QP_WAIT_VALUE;
	}

	lp_qp_work->comp_flag = 0;
	if (try_wait_for_completion(&comp))
		return 0;

	dev_warn(dev, "recreate lp qp failed 20s timeout and return failed!\n");
	return -ETIMEDOUT;
}