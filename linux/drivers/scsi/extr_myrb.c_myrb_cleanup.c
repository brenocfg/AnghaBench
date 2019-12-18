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
struct pci_dev {int dummy; } ;
struct myrb_hba {int /*<<< orphan*/  host; scalar_t__ io_addr; scalar_t__ irq; scalar_t__ mmio_base; int /*<<< orphan*/  io_base; int /*<<< orphan*/  (* disable_intr ) (int /*<<< orphan*/ ) ;struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct myrb_hba*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  myrb_unmap (struct myrb_hba*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myrb_cleanup(struct myrb_hba *cb)
{
	struct pci_dev *pdev = cb->pdev;

	/* Free the memory mailbox, status, and related structures */
	myrb_unmap(cb);

	if (cb->mmio_base) {
		cb->disable_intr(cb->io_base);
		iounmap(cb->mmio_base);
	}
	if (cb->irq)
		free_irq(cb->irq, cb);
	if (cb->io_addr)
		release_region(cb->io_addr, 0x80);
	pci_set_drvdata(pdev, NULL);
	pci_disable_device(pdev);
	scsi_host_put(cb->host);
}