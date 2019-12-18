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
 unsigned long __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void lkdtm_SLAB_FREE_PAGE(void)
{
	unsigned long p = __get_free_page(GFP_KERNEL);

	pr_info("Attempting non-Slab slab free ...\n");
	kmem_cache_free(NULL, (void *)p);
	free_page(p);
}