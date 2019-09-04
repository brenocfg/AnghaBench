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

/* Variables and functions */
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * drbd_al_ext_cache ; 
 int /*<<< orphan*/ * drbd_bm_ext_cache ; 
 int /*<<< orphan*/ * drbd_ee_cache ; 
 int /*<<< orphan*/  drbd_ee_mempool ; 
 int /*<<< orphan*/  drbd_io_bio_set ; 
 int /*<<< orphan*/  drbd_md_io_bio_set ; 
 int /*<<< orphan*/  drbd_md_io_page_pool ; 
 struct page* drbd_pp_pool ; 
 int /*<<< orphan*/  drbd_pp_vacant ; 
 int /*<<< orphan*/ * drbd_request_cache ; 
 int /*<<< orphan*/  drbd_request_mempool ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ page_private (struct page*) ; 

__attribute__((used)) static void drbd_destroy_mempools(void)
{
	struct page *page;

	while (drbd_pp_pool) {
		page = drbd_pp_pool;
		drbd_pp_pool = (struct page *)page_private(page);
		__free_page(page);
		drbd_pp_vacant--;
	}

	/* D_ASSERT(device, atomic_read(&drbd_pp_vacant)==0); */

	bioset_exit(&drbd_io_bio_set);
	bioset_exit(&drbd_md_io_bio_set);
	mempool_exit(&drbd_md_io_page_pool);
	mempool_exit(&drbd_ee_mempool);
	mempool_exit(&drbd_request_mempool);
	kmem_cache_destroy(drbd_ee_cache);
	kmem_cache_destroy(drbd_request_cache);
	kmem_cache_destroy(drbd_bm_ext_cache);
	kmem_cache_destroy(drbd_al_ext_cache);

	drbd_ee_cache        = NULL;
	drbd_request_cache   = NULL;
	drbd_bm_ext_cache    = NULL;
	drbd_al_ext_cache    = NULL;

	return;
}