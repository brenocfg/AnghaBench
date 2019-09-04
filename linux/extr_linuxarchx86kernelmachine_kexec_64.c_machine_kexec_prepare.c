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
struct kimage {int /*<<< orphan*/  control_code_page; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int arch_update_purgatory (struct kimage*) ; 
 int init_pgtable (struct kimage*,unsigned long) ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 

int machine_kexec_prepare(struct kimage *image)
{
	unsigned long start_pgtable;
	int result;

	/* Calculate the offsets */
	start_pgtable = page_to_pfn(image->control_code_page) << PAGE_SHIFT;

	/* Setup the identity mapped 64bit page table */
	result = init_pgtable(image, start_pgtable);
	if (result)
		return result;

	/* update purgatory as needed */
	result = arch_update_purgatory(image);
	if (result)
		return result;

	return 0;
}