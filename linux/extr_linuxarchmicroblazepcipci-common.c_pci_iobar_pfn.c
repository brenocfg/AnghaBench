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
struct vm_area_struct {int vm_pgoff; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {int io_base_phys; scalar_t__ io_base_virt; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 unsigned long _IO_BASE ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int pci_resource_start (struct pci_dev*,int) ; 

int pci_iobar_pfn(struct pci_dev *pdev, int bar, struct vm_area_struct *vma)
{
	struct pci_controller *hose = pci_bus_to_host(pdev->bus);
	resource_size_t ioaddr = pci_resource_start(pdev, bar);

	if (!hose)
		return -EINVAL;		/* should never happen */

	/* Convert to an offset within this PCI controller */
	ioaddr -= (unsigned long)hose->io_base_virt - _IO_BASE;

	vma->vm_pgoff += (ioaddr + hose->io_base_phys) >> PAGE_SHIFT;
	return 0;
}