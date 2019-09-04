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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/  vm_pgoff; } ;
struct pci_dev {int dummy; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */
 int __pci_mmap_make_offset (struct pci_dev*,struct vm_area_struct*,int) ; 
 int /*<<< orphan*/  __pci_mmap_set_pgprot (struct pci_dev*,struct vm_area_struct*,int) ; 
 int io_remap_pfn_range (struct vm_area_struct*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 

int pci_mmap_page_range(struct pci_dev *dev, int bar,
			struct vm_area_struct *vma,
			enum pci_mmap_state mmap_state, int write_combine)
{
	int ret;

	ret = __pci_mmap_make_offset(dev, vma, mmap_state);
	if (ret < 0)
		return ret;

	__pci_mmap_set_pgprot(dev, vma, mmap_state);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	ret = io_remap_pfn_range(vma, vma->vm_start,
				 vma->vm_pgoff,
				 vma->vm_end - vma->vm_start,
				 vma->vm_page_prot);
	if (ret)
		return ret;

	return 0;
}