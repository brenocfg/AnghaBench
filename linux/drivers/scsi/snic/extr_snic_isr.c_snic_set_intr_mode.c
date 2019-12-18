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
struct snic {unsigned int wq_count; unsigned int cq_count; unsigned int intr_count; int /*<<< orphan*/  vdev; int /*<<< orphan*/  shost; int /*<<< orphan*/  err_intr_offset; int /*<<< orphan*/  pdev; int /*<<< orphan*/  intr; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 unsigned int SNIC_CQ_IO_CMPL_MAX ; 
 int /*<<< orphan*/  SNIC_ISR_DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNIC_MSIX_ERR_NOTIFY ; 
 int /*<<< orphan*/  VNIC_DEV_INTR_MODE_MSIX ; 
 int /*<<< orphan*/  VNIC_DEV_INTR_MODE_UNKNOWN ; 
 scalar_t__ pci_alloc_irq_vectors (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svnic_dev_set_intr_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
snic_set_intr_mode(struct snic *snic)
{
	unsigned int n = ARRAY_SIZE(snic->wq);
	unsigned int m = SNIC_CQ_IO_CMPL_MAX;
	unsigned int vecs = n + m + 1;

	/*
	 * We need n WQs, m CQs, and n+m+1 INTRs
	 * (last INTR is used for WQ/CQ errors and notification area
	 */
	BUILD_BUG_ON((ARRAY_SIZE(snic->wq) + SNIC_CQ_IO_CMPL_MAX) >
			ARRAY_SIZE(snic->intr));

	if (snic->wq_count < n || snic->cq_count < n + m)
		goto fail;

	if (pci_alloc_irq_vectors(snic->pdev, vecs, vecs, PCI_IRQ_MSIX) < 0)
		goto fail;

	snic->wq_count = n;
	snic->cq_count = n + m;
	snic->intr_count = vecs;
	snic->err_intr_offset = SNIC_MSIX_ERR_NOTIFY;

	SNIC_ISR_DBG(snic->shost, "Using MSI-X Interrupts\n");
	svnic_dev_set_intr_mode(snic->vdev, VNIC_DEV_INTR_MODE_MSIX);
	return 0;
fail:
	svnic_dev_set_intr_mode(snic->vdev, VNIC_DEV_INTR_MODE_UNKNOWN);
	return -EINVAL;
}