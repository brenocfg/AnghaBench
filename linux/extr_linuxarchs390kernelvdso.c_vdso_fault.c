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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_special_mapping {int dummy; } ;
struct vm_fault {unsigned long pgoff; struct page* page; } ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page** vdso64_pagelist ; 
 unsigned long vdso64_pages ; 

__attribute__((used)) static vm_fault_t vdso_fault(const struct vm_special_mapping *sm,
		      struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct page **vdso_pagelist;
	unsigned long vdso_pages;

	vdso_pagelist = vdso64_pagelist;
	vdso_pages = vdso64_pages;
#ifdef CONFIG_COMPAT
	if (is_compat_task()) {
		vdso_pagelist = vdso32_pagelist;
		vdso_pages = vdso32_pages;
	}
#endif

	if (vmf->pgoff >= vdso_pages)
		return VM_FAULT_SIGBUS;

	vmf->page = vdso_pagelist[vmf->pgoff];
	get_page(vmf->page);
	return 0;
}