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
struct TYPE_2__ {int seeks; int /*<<< orphan*/  scan_objects; int /*<<< orphan*/  count_objects; } ;
struct ttm_pool_manager {TYPE_1__ mm_shrink; } ;

/* Variables and functions */
 int register_shrinker (TYPE_1__*) ; 
 int /*<<< orphan*/  ttm_pool_shrink_count ; 
 int /*<<< orphan*/  ttm_pool_shrink_scan ; 

__attribute__((used)) static int ttm_pool_mm_shrink_init(struct ttm_pool_manager *manager)
{
	manager->mm_shrink.count_objects = ttm_pool_shrink_count;
	manager->mm_shrink.scan_objects = ttm_pool_shrink_scan;
	manager->mm_shrink.seeks = 1;
	return register_shrinker(&manager->mm_shrink);
}