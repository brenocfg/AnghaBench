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
struct genwqe_dev {int /*<<< orphan*/  mmio; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 

__attribute__((used)) static void genwqe_pci_remove(struct genwqe_dev *cd)
{
	struct pci_dev *pci_dev = cd->pci_dev;

	if (cd->mmio)
		pci_iounmap(pci_dev, cd->mmio);

	pci_release_mem_regions(pci_dev);
	pci_disable_device(pci_dev);
}