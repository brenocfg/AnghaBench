#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hns_roce_free_mr {TYPE_3__* mr_free_pd; TYPE_2__* mr_free_cq; struct hns_roce_qp** mr_free_qp; } ;
struct hns_roce_v1_priv {struct hns_roce_free_mr free_mr; } ;
struct hns_roce_qp {int /*<<< orphan*/  ibqp; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ibpd; } ;
struct TYPE_5__ {int /*<<< orphan*/  ib_cq; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int HNS_ROCE_V1_RESV_QP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  hns_roce_dealloc_pd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_ib_destroy_cq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hns_roce_v1_destroy_qp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_v1_release_lp_qp(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_free_mr *free_mr;
	struct hns_roce_v1_priv *priv;
	struct hns_roce_qp *hr_qp;
	int ret;
	int i;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	free_mr = &priv->free_mr;

	for (i = 0; i < HNS_ROCE_V1_RESV_QP; i++) {
		hr_qp = free_mr->mr_free_qp[i];
		if (!hr_qp)
			continue;

		ret = hns_roce_v1_destroy_qp(&hr_qp->ibqp, NULL);
		if (ret)
			dev_err(dev, "Destroy qp %d for mr free failed(%d)!\n",
				i, ret);
	}

	hns_roce_ib_destroy_cq(&free_mr->mr_free_cq->ib_cq, NULL);
	kfree(&free_mr->mr_free_cq->ib_cq);
	hns_roce_dealloc_pd(&free_mr->mr_free_pd->ibpd, NULL);
	kfree(&free_mr->mr_free_pd->ibpd);
}