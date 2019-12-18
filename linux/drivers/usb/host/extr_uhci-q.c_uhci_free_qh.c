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
struct uhci_qh {scalar_t__ state; int /*<<< orphan*/  dma_handle; scalar_t__ dummy_td; TYPE_1__* hep; scalar_t__ udev; int /*<<< orphan*/  node; int /*<<< orphan*/  queue; } ;
struct uhci_hcd {int /*<<< orphan*/  qh_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/ * hcpriv; } ;

/* Variables and functions */
 scalar_t__ QH_STATE_IDLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*,struct uhci_qh*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct uhci_qh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhci_dev (struct uhci_hcd*) ; 
 int /*<<< orphan*/  uhci_free_td (struct uhci_hcd*,scalar_t__) ; 

__attribute__((used)) static void uhci_free_qh(struct uhci_hcd *uhci, struct uhci_qh *qh)
{
	WARN_ON(qh->state != QH_STATE_IDLE && qh->udev);
	if (!list_empty(&qh->queue))
		dev_WARN(uhci_dev(uhci), "qh %p list not empty!\n", qh);

	list_del(&qh->node);
	if (qh->udev) {
		qh->hep->hcpriv = NULL;
		if (qh->dummy_td)
			uhci_free_td(uhci, qh->dummy_td);
	}
	dma_pool_free(uhci->qh_pool, qh, qh->dma_handle);
}