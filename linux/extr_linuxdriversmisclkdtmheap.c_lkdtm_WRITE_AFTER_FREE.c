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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

void lkdtm_WRITE_AFTER_FREE(void)
{
	int *base, *again;
	size_t len = 1024;
	/*
	 * The slub allocator uses the first word to store the free
	 * pointer in some configurations. Use the middle of the
	 * allocation to avoid running into the freelist
	 */
	size_t offset = (len / sizeof(*base)) / 2;

	base = kmalloc(len, GFP_KERNEL);
	if (!base)
		return;
	pr_info("Allocated memory %p-%p\n", base, &base[offset * 2]);
	pr_info("Attempting bad write to freed memory at %p\n",
		&base[offset]);
	kfree(base);
	base[offset] = 0x0abcdef0;
	/* Attempt to notice the overwrite. */
	again = kmalloc(len, GFP_KERNEL);
	kfree(again);
	if (again != base)
		pr_info("Hmm, didn't get the same memory range.\n");
}