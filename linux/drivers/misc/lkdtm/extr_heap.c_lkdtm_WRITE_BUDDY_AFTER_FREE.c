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
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  schedule () ; 

void lkdtm_WRITE_BUDDY_AFTER_FREE(void)
{
	unsigned long p = __get_free_page(GFP_KERNEL);
	if (!p) {
		pr_info("Unable to allocate free page\n");
		return;
	}

	pr_info("Writing to the buddy page before free\n");
	memset((void *)p, 0x3, PAGE_SIZE);
	free_page(p);
	schedule();
	pr_info("Attempting bad write to the buddy page after free\n");
	memset((void *)p, 0x78, PAGE_SIZE);
	/* Attempt to notice the overwrite. */
	p = __get_free_page(GFP_KERNEL);
	free_page(p);
	schedule();
}