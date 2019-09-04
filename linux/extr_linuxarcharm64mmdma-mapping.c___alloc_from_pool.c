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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  atomic_pool ; 
 unsigned long gen_pool_alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gen_pool_virt_to_phys (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 struct page* phys_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *__alloc_from_pool(size_t size, struct page **ret_page, gfp_t flags)
{
	unsigned long val;
	void *ptr = NULL;

	if (!atomic_pool) {
		WARN(1, "coherent pool not initialised!\n");
		return NULL;
	}

	val = gen_pool_alloc(atomic_pool, size);
	if (val) {
		phys_addr_t phys = gen_pool_virt_to_phys(atomic_pool, val);

		*ret_page = phys_to_page(phys);
		ptr = (void *)val;
		memset(ptr, 0, size);
	}

	return ptr;
}