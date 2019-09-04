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
struct vm_area_struct {int dummy; } ;
struct gmap {TYPE_1__* mm; int /*<<< orphan*/  guest_to_host; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned long PMD_MASK ; 
 unsigned long PMD_SHIFT ; 
 unsigned long PMD_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,unsigned long) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 scalar_t__ radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_page_range (struct vm_area_struct*,unsigned long,unsigned long) ; 

void gmap_discard(struct gmap *gmap, unsigned long from, unsigned long to)
{
	unsigned long gaddr, vmaddr, size;
	struct vm_area_struct *vma;

	down_read(&gmap->mm->mmap_sem);
	for (gaddr = from; gaddr < to;
	     gaddr = (gaddr + PMD_SIZE) & PMD_MASK) {
		/* Find the vm address for the guest address */
		vmaddr = (unsigned long)
			radix_tree_lookup(&gmap->guest_to_host,
					  gaddr >> PMD_SHIFT);
		if (!vmaddr)
			continue;
		vmaddr |= gaddr & ~PMD_MASK;
		/* Find vma in the parent mm */
		vma = find_vma(gmap->mm, vmaddr);
		if (!vma)
			continue;
		/*
		 * We do not discard pages that are backed by
		 * hugetlbfs, so we don't have to refault them.
		 */
		if (is_vm_hugetlb_page(vma))
			continue;
		size = min(to - gaddr, PMD_SIZE - (gaddr & ~PMD_MASK));
		zap_page_range(vma, vmaddr, size);
	}
	up_read(&gmap->mm->mmap_sem);
}