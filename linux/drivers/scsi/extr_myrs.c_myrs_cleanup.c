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
struct myrs_hba {int /*<<< orphan*/  host; scalar_t__ mmio_base; scalar_t__ io_addr; scalar_t__ irq; int /*<<< orphan*/  (* disable_intr ) (struct myrs_hba*) ;struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct myrs_hba*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  myrs_unmap (struct myrs_hba*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct myrs_hba*) ; 

__attribute__((used)) static void myrs_cleanup(struct myrs_hba *cs)
{
	struct pci_dev *pdev = cs->pdev;

	/* Free the memory mailbox, status, and related structures */
	myrs_unmap(cs);

	if (cs->mmio_base) {
		cs->disable_intr(cs);
		iounmap(cs->mmio_base);
	}
	if (cs->irq)
		free_irq(cs->irq, cs);
	if (cs->io_addr)
		release_region(cs->io_addr, 0x80);
	iounmap(cs->mmio_base);
	pci_set_drvdata(pdev, NULL);
	pci_disable_device(pdev);
	scsi_host_put(cs->host);
}