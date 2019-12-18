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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_fence_obj {void (* destroy ) (struct vmw_fence_obj*) ;int /*<<< orphan*/  head; int /*<<< orphan*/  seq_passed_actions; int /*<<< orphan*/  base; } ;
struct vmw_fence_manager {int /*<<< orphan*/  lock; int /*<<< orphan*/  num_fence_objects; int /*<<< orphan*/  fence_list; int /*<<< orphan*/  fifo_down; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fence_ops ; 

__attribute__((used)) static int vmw_fence_obj_init(struct vmw_fence_manager *fman,
			      struct vmw_fence_obj *fence, u32 seqno,
			      void (*destroy) (struct vmw_fence_obj *fence))
{
	int ret = 0;

	dma_fence_init(&fence->base, &vmw_fence_ops, &fman->lock,
		       fman->ctx, seqno);
	INIT_LIST_HEAD(&fence->seq_passed_actions);
	fence->destroy = destroy;

	spin_lock(&fman->lock);
	if (unlikely(fman->fifo_down)) {
		ret = -EBUSY;
		goto out_unlock;
	}
	list_add_tail(&fence->head, &fman->fence_list);
	++fman->num_fence_objects;

out_unlock:
	spin_unlock(&fman->lock);
	return ret;

}