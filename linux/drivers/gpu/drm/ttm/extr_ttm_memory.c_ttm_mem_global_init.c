#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_zone {scalar_t__ max_mem; int /*<<< orphan*/  name; } ;
struct ttm_mem_global {int num_zones; TYPE_1__* zone_kernel; struct ttm_mem_zone** zones; scalar_t__ lower_mem_limit; int /*<<< orphan*/  kobj; int /*<<< orphan*/  work; int /*<<< orphan*/  swap_queue; int /*<<< orphan*/  lock; } ;
struct sysinfo {int dummy; } ;
struct TYPE_2__ {int max_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_dma_page_alloc_init (struct ttm_mem_global*,int) ; 
 int /*<<< orphan*/  ttm_get_kobj () ; 
 int /*<<< orphan*/  ttm_mem_glob_kobj_type ; 
 int /*<<< orphan*/  ttm_mem_global_release (struct ttm_mem_global*) ; 
 int ttm_mem_init_dma32_zone (struct ttm_mem_global*,struct sysinfo*) ; 
 int ttm_mem_init_highmem_zone (struct ttm_mem_global*,struct sysinfo*) ; 
 int ttm_mem_init_kernel_zone (struct ttm_mem_global*,struct sysinfo*) ; 
 int /*<<< orphan*/  ttm_page_alloc_init (struct ttm_mem_global*,int) ; 
 int /*<<< orphan*/  ttm_shrink_work ; 
 scalar_t__ unlikely (int) ; 

int ttm_mem_global_init(struct ttm_mem_global *glob)
{
	struct sysinfo si;
	int ret;
	int i;
	struct ttm_mem_zone *zone;

	spin_lock_init(&glob->lock);
	glob->swap_queue = create_singlethread_workqueue("ttm_swap");
	INIT_WORK(&glob->work, ttm_shrink_work);
	ret = kobject_init_and_add(
		&glob->kobj, &ttm_mem_glob_kobj_type, ttm_get_kobj(), "memory_accounting");
	if (unlikely(ret != 0)) {
		kobject_put(&glob->kobj);
		return ret;
	}

	si_meminfo(&si);

	/* set it as 0 by default to keep original behavior of OOM */
	glob->lower_mem_limit = 0;

	ret = ttm_mem_init_kernel_zone(glob, &si);
	if (unlikely(ret != 0))
		goto out_no_zone;
#ifdef CONFIG_HIGHMEM
	ret = ttm_mem_init_highmem_zone(glob, &si);
	if (unlikely(ret != 0))
		goto out_no_zone;
#else
	ret = ttm_mem_init_dma32_zone(glob, &si);
	if (unlikely(ret != 0))
		goto out_no_zone;
#endif
	for (i = 0; i < glob->num_zones; ++i) {
		zone = glob->zones[i];
		pr_info("Zone %7s: Available graphics memory: %llu KiB\n",
			zone->name, (unsigned long long)zone->max_mem >> 10);
	}
	ttm_page_alloc_init(glob, glob->zone_kernel->max_mem/(2*PAGE_SIZE));
	ttm_dma_page_alloc_init(glob, glob->zone_kernel->max_mem/(2*PAGE_SIZE));
	return 0;
out_no_zone:
	ttm_mem_global_release(glob);
	return ret;
}