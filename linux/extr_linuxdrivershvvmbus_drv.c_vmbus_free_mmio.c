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
struct resource {scalar_t__ start; scalar_t__ end; struct resource* sibling; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  __release_region (struct resource*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct resource* hyperv_mmio ; 
 int /*<<< orphan*/  hyperv_mmio_lock ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void vmbus_free_mmio(resource_size_t start, resource_size_t size)
{
	struct resource *iter;

	down(&hyperv_mmio_lock);
	for (iter = hyperv_mmio; iter; iter = iter->sibling) {
		if ((iter->start >= start + size) || (iter->end <= start))
			continue;

		__release_region(iter, start, size);
	}
	release_mem_region(start, size);
	up(&hyperv_mmio_lock);

}