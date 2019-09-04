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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long PFN_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PTI_LEVEL_KERNEL_IMAGE ; 
 scalar_t__ __end_rodata_aligned ; 
 scalar_t__ __stop___ex_table ; 
 unsigned long _text ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pti_clone_pgtable (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pti_kernel_image_global_ok () ; 
 int /*<<< orphan*/  set_memory_global (unsigned long,unsigned long) ; 

__attribute__((used)) static void pti_clone_kernel_text(void)
{
	/*
	 * rodata is part of the kernel image and is normally
	 * readable on the filesystem or on the web.  But, do not
	 * clone the areas past rodata, they might contain secrets.
	 */
	unsigned long start = PFN_ALIGN(_text);
	unsigned long end_clone  = (unsigned long)__end_rodata_aligned;
	unsigned long end_global = PFN_ALIGN((unsigned long)__stop___ex_table);

	if (!pti_kernel_image_global_ok())
		return;

	pr_debug("mapping partial kernel image into user address space\n");

	/*
	 * Note that this will undo _some_ of the work that
	 * pti_set_kernel_image_nonglobal() did to clear the
	 * global bit.
	 */
	pti_clone_pgtable(start, end_clone, PTI_LEVEL_KERNEL_IMAGE);

	/*
	 * pti_clone_pgtable() will set the global bit in any PMDs
	 * that it clones, but we also need to get any PTEs in
	 * the last level for areas that are not huge-page-aligned.
	 */

	/* Set the global bit for normal non-__init kernel text: */
	set_memory_global(start, (end_global - start) >> PAGE_SHIFT);
}