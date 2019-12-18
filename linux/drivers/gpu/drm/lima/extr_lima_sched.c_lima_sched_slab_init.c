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
struct lima_fence {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 scalar_t__ kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ lima_fence_slab ; 
 int /*<<< orphan*/  lima_fence_slab_refcnt ; 

int lima_sched_slab_init(void)
{
	if (!lima_fence_slab) {
		lima_fence_slab = kmem_cache_create(
			"lima_fence", sizeof(struct lima_fence), 0,
			SLAB_HWCACHE_ALIGN, NULL);
		if (!lima_fence_slab)
			return -ENOMEM;
	}

	lima_fence_slab_refcnt++;
	return 0;
}