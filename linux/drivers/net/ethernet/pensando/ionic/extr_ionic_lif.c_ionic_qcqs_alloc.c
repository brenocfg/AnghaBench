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
typedef  union ionic_notifyq_comp {int dummy; } ionic_notifyq_comp ;
struct ionic_q_stats {int dummy; } ;
struct ionic_notifyq_cmd {int dummy; } ;
struct ionic_lif {int nxqs; int /*<<< orphan*/ * adminqcq; int /*<<< orphan*/ * notifyqcq; TYPE_2__* txqcqs; TYPE_2__* rxqcqs; int /*<<< orphan*/  kern_pid; TYPE_1__* ionic; } ;
struct ionic_admin_comp {int dummy; } ;
struct ionic_admin_cmd {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* stats; } ;
struct TYPE_3__ {scalar_t__ nnqs_per_lif; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IONIC_ADMINQ_LENGTH ; 
 int /*<<< orphan*/  IONIC_NOTIFYQ_LENGTH ; 
 unsigned int IONIC_QCQ_F_INTR ; 
 unsigned int IONIC_QCQ_F_NOTIFYQ ; 
 int /*<<< orphan*/  IONIC_QTYPE_ADMINQ ; 
 int /*<<< orphan*/  IONIC_QTYPE_NOTIFYQ ; 
 int /*<<< orphan*/  devm_kfree (struct device*,TYPE_2__*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_link_qcq_interrupts (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ionic_qcq_alloc (struct ionic_lif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ionic_qcq_free (struct ionic_lif*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ionic_qcqs_alloc(struct ionic_lif *lif)
{
	struct device *dev = lif->ionic->dev;
	unsigned int q_list_size;
	unsigned int flags;
	int err;
	int i;

	flags = IONIC_QCQ_F_INTR;
	err = ionic_qcq_alloc(lif, IONIC_QTYPE_ADMINQ, 0, "admin", flags,
			      IONIC_ADMINQ_LENGTH,
			      sizeof(struct ionic_admin_cmd),
			      sizeof(struct ionic_admin_comp),
			      0, lif->kern_pid, &lif->adminqcq);
	if (err)
		return err;

	if (lif->ionic->nnqs_per_lif) {
		flags = IONIC_QCQ_F_NOTIFYQ;
		err = ionic_qcq_alloc(lif, IONIC_QTYPE_NOTIFYQ, 0, "notifyq",
				      flags, IONIC_NOTIFYQ_LENGTH,
				      sizeof(struct ionic_notifyq_cmd),
				      sizeof(union ionic_notifyq_comp),
				      0, lif->kern_pid, &lif->notifyqcq);
		if (err)
			goto err_out_free_adminqcq;

		/* Let the notifyq ride on the adminq interrupt */
		ionic_link_qcq_interrupts(lif->adminqcq, lif->notifyqcq);
	}

	q_list_size = sizeof(*lif->txqcqs) * lif->nxqs;
	err = -ENOMEM;
	lif->txqcqs = devm_kzalloc(dev, q_list_size, GFP_KERNEL);
	if (!lif->txqcqs)
		goto err_out_free_notifyqcq;
	for (i = 0; i < lif->nxqs; i++) {
		lif->txqcqs[i].stats = devm_kzalloc(dev,
						    sizeof(struct ionic_q_stats),
						    GFP_KERNEL);
		if (!lif->txqcqs[i].stats)
			goto err_out_free_tx_stats;
	}

	lif->rxqcqs = devm_kzalloc(dev, q_list_size, GFP_KERNEL);
	if (!lif->rxqcqs)
		goto err_out_free_tx_stats;
	for (i = 0; i < lif->nxqs; i++) {
		lif->rxqcqs[i].stats = devm_kzalloc(dev,
						    sizeof(struct ionic_q_stats),
						    GFP_KERNEL);
		if (!lif->rxqcqs[i].stats)
			goto err_out_free_rx_stats;
	}

	return 0;

err_out_free_rx_stats:
	for (i = 0; i < lif->nxqs; i++)
		if (lif->rxqcqs[i].stats)
			devm_kfree(dev, lif->rxqcqs[i].stats);
	devm_kfree(dev, lif->rxqcqs);
	lif->rxqcqs = NULL;
err_out_free_tx_stats:
	for (i = 0; i < lif->nxqs; i++)
		if (lif->txqcqs[i].stats)
			devm_kfree(dev, lif->txqcqs[i].stats);
	devm_kfree(dev, lif->txqcqs);
	lif->txqcqs = NULL;
err_out_free_notifyqcq:
	if (lif->notifyqcq) {
		ionic_qcq_free(lif, lif->notifyqcq);
		lif->notifyqcq = NULL;
	}
err_out_free_adminqcq:
	ionic_qcq_free(lif, lif->adminqcq);
	lif->adminqcq = NULL;

	return err;
}