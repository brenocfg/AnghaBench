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
typedef  size_t u32 ;
struct reservation_object_list {size_t shared_count; scalar_t__ shared_max; int /*<<< orphan*/ * shared; } ;
struct reservation_object {int /*<<< orphan*/  seq; } ;
struct dma_fence {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 scalar_t__ dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reservation_object_held (struct reservation_object*) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
reservation_object_add_shared_inplace(struct reservation_object *obj,
				      struct reservation_object_list *fobj,
				      struct dma_fence *fence)
{
	struct dma_fence *signaled = NULL;
	u32 i, signaled_idx;

	dma_fence_get(fence);

	preempt_disable();
	write_seqcount_begin(&obj->seq);

	for (i = 0; i < fobj->shared_count; ++i) {
		struct dma_fence *old_fence;

		old_fence = rcu_dereference_protected(fobj->shared[i],
						reservation_object_held(obj));

		if (old_fence->context == fence->context) {
			/* memory barrier is added by write_seqcount_begin */
			RCU_INIT_POINTER(fobj->shared[i], fence);
			write_seqcount_end(&obj->seq);
			preempt_enable();

			dma_fence_put(old_fence);
			return;
		}

		if (!signaled && dma_fence_is_signaled(old_fence)) {
			signaled = old_fence;
			signaled_idx = i;
		}
	}

	/*
	 * memory barrier is added by write_seqcount_begin,
	 * fobj->shared_count is protected by this lock too
	 */
	if (signaled) {
		RCU_INIT_POINTER(fobj->shared[signaled_idx], fence);
	} else {
		BUG_ON(fobj->shared_count >= fobj->shared_max);
		RCU_INIT_POINTER(fobj->shared[fobj->shared_count], fence);
		fobj->shared_count++;
	}

	write_seqcount_end(&obj->seq);
	preempt_enable();

	dma_fence_put(signaled);
}