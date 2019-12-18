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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_private_data; } ;
struct remap_pfn {int /*<<< orphan*/  prot; int /*<<< orphan*/  pages; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int apply_to_page_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ,struct remap_pfn*) ; 
 int /*<<< orphan*/  remap_pfn_fn ; 

int xen_remap_vma_range(struct vm_area_struct *vma, unsigned long addr, unsigned long len)
{
	struct remap_pfn r = {
		.mm = vma->vm_mm,
		.pages = vma->vm_private_data,
		.prot = vma->vm_page_prot,
	};

	return apply_to_page_range(vma->vm_mm, addr, len, remap_pfn_fn, &r);
}