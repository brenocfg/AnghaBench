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
struct ttm_mem_zone {int /*<<< orphan*/  kobj; } ;
struct ttm_mem_global {unsigned int num_zones; int /*<<< orphan*/  kobj; struct ttm_mem_zone** zones; int /*<<< orphan*/ * swap_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ttm_mem_global*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_dma_page_alloc_fini () ; 
 int /*<<< orphan*/  ttm_page_alloc_fini () ; 

void ttm_mem_global_release(struct ttm_mem_global *glob)
{
	struct ttm_mem_zone *zone;
	unsigned int i;

	/* let the page allocator first stop the shrink work. */
	ttm_page_alloc_fini();
	ttm_dma_page_alloc_fini();

	flush_workqueue(glob->swap_queue);
	destroy_workqueue(glob->swap_queue);
	glob->swap_queue = NULL;
	for (i = 0; i < glob->num_zones; ++i) {
		zone = glob->zones[i];
		kobject_del(&zone->kobj);
		kobject_put(&zone->kobj);
	}
	kobject_del(&glob->kobj);
	kobject_put(&glob->kobj);
	memset(glob, 0, sizeof(*glob));
}