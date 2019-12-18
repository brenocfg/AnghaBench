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
struct TYPE_3__ {int /*<<< orphan*/  vector; int /*<<< orphan*/  index; } ;
struct ionic_qcq {int flags; int /*<<< orphan*/  napi; TYPE_1__ intr; } ;
struct ionic_lif {TYPE_2__* ionic; } ;
struct ionic_dev {int /*<<< orphan*/  intr_ctrl; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; struct ionic_dev idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_INTR_MASK_SET ; 
 int IONIC_QCQ_F_INITED ; 
 int IONIC_QCQ_F_INTR ; 
 int /*<<< orphan*/  devm_free_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ionic_debugfs_del_qcq (struct ionic_qcq*) ; 
 int /*<<< orphan*/  ionic_intr_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ionic_lif_qcq_deinit(struct ionic_lif *lif, struct ionic_qcq *qcq)
{
	struct ionic_dev *idev = &lif->ionic->idev;
	struct device *dev = lif->ionic->dev;

	if (!qcq)
		return;

	ionic_debugfs_del_qcq(qcq);

	if (!(qcq->flags & IONIC_QCQ_F_INITED))
		return;

	if (qcq->flags & IONIC_QCQ_F_INTR) {
		ionic_intr_mask(idev->intr_ctrl, qcq->intr.index,
				IONIC_INTR_MASK_SET);
		devm_free_irq(dev, qcq->intr.vector, &qcq->napi);
		netif_napi_del(&qcq->napi);
	}

	qcq->flags &= ~IONIC_QCQ_F_INITED;
}