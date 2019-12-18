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
struct TYPE_2__ {scalar_t__ batch; int /*<<< orphan*/  seeks; int /*<<< orphan*/  scan_objects; int /*<<< orphan*/  count_objects; } ;
struct ion_heap {TYPE_1__ shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int /*<<< orphan*/  ion_heap_shrink_count ; 
 int /*<<< orphan*/  ion_heap_shrink_scan ; 
 int register_shrinker (TYPE_1__*) ; 

int ion_heap_init_shrinker(struct ion_heap *heap)
{
	heap->shrinker.count_objects = ion_heap_shrink_count;
	heap->shrinker.scan_objects = ion_heap_shrink_scan;
	heap->shrinker.seeks = DEFAULT_SEEKS;
	heap->shrinker.batch = 0;

	return register_shrinker(&heap->shrinker);
}