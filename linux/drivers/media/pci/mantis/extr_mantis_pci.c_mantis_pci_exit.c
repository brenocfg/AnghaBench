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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct mantis_pci {scalar_t__ mmio; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_NOTICE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mantis_pci*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mantis_pci_exit(struct mantis_pci *mantis)
{
	struct pci_dev *pdev = mantis->pdev;

	dprintk(MANTIS_NOTICE, 1, " mem: 0x%p", mantis->mmio);
	free_irq(pdev->irq, mantis);
	if (mantis->mmio) {
		iounmap(mantis->mmio);
		release_mem_region(pci_resource_start(pdev, 0),
				   pci_resource_len(pdev, 0));
	}

	pci_disable_device(pdev);
}