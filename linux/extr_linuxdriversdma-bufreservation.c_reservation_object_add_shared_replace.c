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
struct reservation_object_list {int shared_count; unsigned int shared_max; scalar_t__ context; int /*<<< orphan*/ * shared; } ;
struct reservation_object {int /*<<< orphan*/  seq; int /*<<< orphan*/  fence; } ;
struct dma_fence {int shared_count; unsigned int shared_max; scalar_t__ context; int /*<<< orphan*/ * shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct reservation_object_list*) ; 
 int /*<<< orphan*/  dma_fence_get (struct reservation_object_list*) ; 
 scalar_t__ dma_fence_is_signaled (struct reservation_object_list*) ; 
 int /*<<< orphan*/  dma_fence_put (struct reservation_object_list*) ; 
 int /*<<< orphan*/  kfree_rcu (struct reservation_object_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu ; 
 struct reservation_object_list* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reservation_object_held (struct reservation_object*) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
reservation_object_add_shared_replace(struct reservation_object *obj,
				      struct reservation_object_list *old,
				      struct reservation_object_list *fobj,
				      struct dma_fence *fence)
{
	unsigned i, j, k;

	dma_fence_get(fence);

	if (!old) {
		RCU_INIT_POINTER(fobj->shared[0], fence);
		fobj->shared_count = 1;
		goto done;
	}

	/*
	 * no need to bump fence refcounts, rcu_read access
	 * requires the use of kref_get_unless_zero, and the
	 * references from the old struct are carried over to
	 * the new.
	 */
	for (i = 0, j = 0, k = fobj->shared_max; i < old->shared_count; ++i) {
		struct dma_fence *check;

		check = rcu_dereference_protected(old->shared[i],
						reservation_object_held(obj));

		if (check->context == fence->context ||
		    dma_fence_is_signaled(check))
			RCU_INIT_POINTER(fobj->shared[--k], check);
		else
			RCU_INIT_POINTER(fobj->shared[j++], check);
	}
	fobj->shared_count = j;
	RCU_INIT_POINTER(fobj->shared[fobj->shared_count], fence);
	fobj->shared_count++;

done:
	preempt_disable();
	write_seqcount_begin(&obj->seq);
	/*
	 * RCU_INIT_POINTER can be used here,
	 * seqcount provides the necessary barriers
	 */
	RCU_INIT_POINTER(obj->fence, fobj);
	write_seqcount_end(&obj->seq);
	preempt_enable();

	if (!old)
		return;

	/* Drop the references to the signaled fences */
	for (i = k; i < fobj->shared_max; ++i) {
		struct dma_fence *f;

		f = rcu_dereference_protected(fobj->shared[i],
					      reservation_object_held(obj));
		dma_fence_put(f);
	}
	kfree_rcu(old, rcu);
}