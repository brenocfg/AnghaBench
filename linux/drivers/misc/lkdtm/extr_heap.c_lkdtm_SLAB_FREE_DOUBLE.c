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
 int /*<<< orphan*/  double_free_cache ; 
 int* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void lkdtm_SLAB_FREE_DOUBLE(void)
{
	int *val;

	val = kmem_cache_alloc(double_free_cache, GFP_KERNEL);
	if (!val) {
		pr_info("Unable to allocate double_free_cache memory.\n");
		return;
	}

	/* Just make sure we got real memory. */
	*val = 0x12345678;
	pr_info("Attempting double slab free ...\n");
	kmem_cache_free(double_free_cache, val);
	kmem_cache_free(double_free_cache, val);
}