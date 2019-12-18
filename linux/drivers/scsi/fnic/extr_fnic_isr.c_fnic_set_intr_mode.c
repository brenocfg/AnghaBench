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
struct fnic {unsigned int rq_count; unsigned int raw_wq_count; unsigned int wq_copy_count; unsigned int cq_count; unsigned int wq_count; int intr_count; int /*<<< orphan*/  vdev; TYPE_1__* lport; scalar_t__ err_intr_offset; int /*<<< orphan*/  pdev; int /*<<< orphan*/  wq_copy; int /*<<< orphan*/  wq; int /*<<< orphan*/  rq; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FNIC_ISR_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ FNIC_MSIX_ERR_NOTIFY ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  VNIC_DEV_INTR_MODE_INTX ; 
 int /*<<< orphan*/  VNIC_DEV_INTR_MODE_MSI ; 
 int /*<<< orphan*/  VNIC_DEV_INTR_MODE_MSIX ; 
 int /*<<< orphan*/  VNIC_DEV_INTR_MODE_UNKNOWN ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_set_intr_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fnic_set_intr_mode(struct fnic *fnic)
{
	unsigned int n = ARRAY_SIZE(fnic->rq);
	unsigned int m = ARRAY_SIZE(fnic->wq);
	unsigned int o = ARRAY_SIZE(fnic->wq_copy);

	/*
	 * Set interrupt mode (INTx, MSI, MSI-X) depending
	 * system capabilities.
	 *
	 * Try MSI-X first
	 *
	 * We need n RQs, m WQs, o Copy WQs, n+m+o CQs, and n+m+o+1 INTRs
	 * (last INTR is used for WQ/RQ errors and notification area)
	 */
	if (fnic->rq_count >= n &&
	    fnic->raw_wq_count >= m &&
	    fnic->wq_copy_count >= o &&
	    fnic->cq_count >= n + m + o) {
		int vecs = n + m + o + 1;

		if (pci_alloc_irq_vectors(fnic->pdev, vecs, vecs,
				PCI_IRQ_MSIX) == vecs) {
			fnic->rq_count = n;
			fnic->raw_wq_count = m;
			fnic->wq_copy_count = o;
			fnic->wq_count = m + o;
			fnic->cq_count = n + m + o;
			fnic->intr_count = vecs;
			fnic->err_intr_offset = FNIC_MSIX_ERR_NOTIFY;

			FNIC_ISR_DBG(KERN_DEBUG, fnic->lport->host,
				     "Using MSI-X Interrupts\n");
			vnic_dev_set_intr_mode(fnic->vdev,
					       VNIC_DEV_INTR_MODE_MSIX);
			return 0;
		}
	}

	/*
	 * Next try MSI
	 * We need 1 RQ, 1 WQ, 1 WQ_COPY, 3 CQs, and 1 INTR
	 */
	if (fnic->rq_count >= 1 &&
	    fnic->raw_wq_count >= 1 &&
	    fnic->wq_copy_count >= 1 &&
	    fnic->cq_count >= 3 &&
	    fnic->intr_count >= 1 &&
	    pci_alloc_irq_vectors(fnic->pdev, 1, 1, PCI_IRQ_MSI) == 1) {
		fnic->rq_count = 1;
		fnic->raw_wq_count = 1;
		fnic->wq_copy_count = 1;
		fnic->wq_count = 2;
		fnic->cq_count = 3;
		fnic->intr_count = 1;
		fnic->err_intr_offset = 0;

		FNIC_ISR_DBG(KERN_DEBUG, fnic->lport->host,
			     "Using MSI Interrupts\n");
		vnic_dev_set_intr_mode(fnic->vdev, VNIC_DEV_INTR_MODE_MSI);

		return 0;
	}

	/*
	 * Next try INTx
	 * We need 1 RQ, 1 WQ, 1 WQ_COPY, 3 CQs, and 3 INTRs
	 * 1 INTR is used for all 3 queues, 1 INTR for queue errors
	 * 1 INTR for notification area
	 */

	if (fnic->rq_count >= 1 &&
	    fnic->raw_wq_count >= 1 &&
	    fnic->wq_copy_count >= 1 &&
	    fnic->cq_count >= 3 &&
	    fnic->intr_count >= 3) {

		fnic->rq_count = 1;
		fnic->raw_wq_count = 1;
		fnic->wq_copy_count = 1;
		fnic->cq_count = 3;
		fnic->intr_count = 3;

		FNIC_ISR_DBG(KERN_DEBUG, fnic->lport->host,
			     "Using Legacy Interrupts\n");
		vnic_dev_set_intr_mode(fnic->vdev, VNIC_DEV_INTR_MODE_INTX);

		return 0;
	}

	vnic_dev_set_intr_mode(fnic->vdev, VNIC_DEV_INTR_MODE_UNKNOWN);

	return -EINVAL;
}