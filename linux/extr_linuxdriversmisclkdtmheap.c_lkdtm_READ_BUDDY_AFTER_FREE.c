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
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

void lkdtm_READ_BUDDY_AFTER_FREE(void)
{
	unsigned long p = __get_free_page(GFP_KERNEL);
	int saw, *val;
	int *base;

	if (!p) {
		pr_info("Unable to allocate free page\n");
		return;
	}

	val = kmalloc(1024, GFP_KERNEL);
	if (!val) {
		pr_info("Unable to allocate val memory.\n");
		free_page(p);
		return;
	}

	base = (int *)p;

	*val = 0x12345678;
	base[0] = *val;
	pr_info("Value in memory before free: %x\n", base[0]);
	free_page(p);
	pr_info("Attempting to read from freed memory\n");
	saw = base[0];
	if (saw != *val) {
		/* Good! Poisoning happened, so declare a win. */
		pr_info("Memory correctly poisoned (%x)\n", saw);
		BUG();
	}
	pr_info("Buddy page was not poisoned\n");

	kfree(val);
}