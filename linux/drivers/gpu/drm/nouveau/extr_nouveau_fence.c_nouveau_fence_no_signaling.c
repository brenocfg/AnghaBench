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
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct nouveau_fence {TYPE_1__ base; int /*<<< orphan*/  head; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dma_fence_put (TYPE_1__*) ; 
 struct nouveau_fence* from_fence (struct dma_fence*) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ nouveau_fence_is_signaled (struct dma_fence*) ; 

__attribute__((used)) static bool nouveau_fence_no_signaling(struct dma_fence *f)
{
	struct nouveau_fence *fence = from_fence(f);

	/*
	 * caller should have a reference on the fence,
	 * else fence could get freed here
	 */
	WARN_ON(kref_read(&fence->base.refcount) <= 1);

	/*
	 * This needs uevents to work correctly, but dma_fence_add_callback relies on
	 * being able to enable signaling. It will still get signaled eventually,
	 * just not right away.
	 */
	if (nouveau_fence_is_signaled(f)) {
		list_del(&fence->head);

		dma_fence_put(&fence->base);
		return false;
	}

	return true;
}