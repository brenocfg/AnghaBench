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
struct vm_area_struct {unsigned long vm_pgoff; } ;
struct pci_controller {int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,char*,unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__* current ; 
 unsigned long vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int __legacy_mmap_fits(struct pci_controller *hose,
			      struct vm_area_struct *vma,
			      unsigned long res_size, int sparse)
{
	unsigned long nr, start, size;

	nr = vma_pages(vma);
	start = vma->vm_pgoff;
	size = ((res_size - 1) >> PAGE_SHIFT) + 1;

	if (start < size && size - start >= nr)
		return 1;
	WARN(1, "process \"%s\" tried to map%s 0x%08lx-0x%08lx on hose %d "
		"(size 0x%08lx)\n",
		current->comm, sparse ? " sparse" : "", start, start + nr,
		hose->index, size);
	return 0;
}