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
 int /*<<< orphan*/  a_cache ; 
 int /*<<< orphan*/  b_cache ; 
 int* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void lkdtm_SLAB_FREE_CROSS(void)
{
	int *val;

	val = kmem_cache_alloc(a_cache, GFP_KERNEL);
	if (!val) {
		pr_info("Unable to allocate a_cache memory.\n");
		return;
	}

	/* Just make sure we got real memory. */
	*val = 0x12345679;
	pr_info("Attempting cross-cache slab free ...\n");
	kmem_cache_free(b_cache, val);
}