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
struct vm_area_struct {int dummy; } ;
struct pci_dev {int dummy; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */

__attribute__((used)) static void __pci_mmap_set_pgprot(struct pci_dev *dev, struct vm_area_struct *vma,
					     enum pci_mmap_state mmap_state)
{
	/* Our io_remap_pfn_range takes care of this, do nothing.  */
}