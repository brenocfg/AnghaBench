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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ntb_transport_qp {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  link_is_up; TYPE_1__* ndev; } ;
struct ntb_queue_entry {int /*<<< orphan*/  flags; scalar_t__ len; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * cb_data; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_DOWN_FLAG ; 
 int NTB_LINK_DOWN_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ntb_queue_entry* ntb_list_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntb_process_tx (struct ntb_transport_qp*,struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  ntb_qp_link_down_reset (struct ntb_transport_qp*) ; 

__attribute__((used)) static void ntb_send_link_down(struct ntb_transport_qp *qp)
{
	struct pci_dev *pdev = qp->ndev->pdev;
	struct ntb_queue_entry *entry;
	int i, rc;

	if (!qp->link_is_up)
		return;

	dev_info(&pdev->dev, "qp %d: Send Link Down\n", qp->qp_num);

	for (i = 0; i < NTB_LINK_DOWN_TIMEOUT; i++) {
		entry = ntb_list_rm(&qp->ntb_tx_free_q_lock, &qp->tx_free_q);
		if (entry)
			break;
		msleep(100);
	}

	if (!entry)
		return;

	entry->cb_data = NULL;
	entry->buf = NULL;
	entry->len = 0;
	entry->flags = LINK_DOWN_FLAG;

	rc = ntb_process_tx(qp, entry);
	if (rc)
		dev_err(&pdev->dev, "ntb: QP%d unable to send linkdown msg\n",
			qp->qp_num);

	ntb_qp_link_down_reset(qp);
}