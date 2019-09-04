#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hns_roce_des_qp {int /*<<< orphan*/  qp_wq; scalar_t__ requeue_flag; } ;
struct hns_roce_v1_priv {struct hns_roce_des_qp des_qp; } ;
struct hns_roce_dev {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_des_qp_free(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v1_priv *priv;
	struct hns_roce_des_qp *des_qp;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	des_qp = &priv->des_qp;

	des_qp->requeue_flag = 0;
	flush_workqueue(des_qp->qp_wq);
	destroy_workqueue(des_qp->qp_wq);
}