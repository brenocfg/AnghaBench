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
struct resource {int dummy; } ;

/* Variables and functions */
 unsigned long atari_stram_to_phys (void*) ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* lookup_resource (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,void*) ; 
 int /*<<< orphan*/  pr_err (char*,void*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 unsigned long resource_size (struct resource*) ; 
 int /*<<< orphan*/  stram_pool ; 

void atari_stram_free(void *addr)
{
	unsigned long start = atari_stram_to_phys(addr);
	struct resource *res;
	unsigned long size;

	res = lookup_resource(&stram_pool, start);
	if (!res) {
		pr_err("atari_stram_free: trying to free nonexistent region "
		       "at %p\n", addr);
		return;
	}

	size = resource_size(res);
	pr_debug("atari_stram_free: free %lu bytes at %p\n", size, addr);
	release_resource(res);
	kfree(res);
}