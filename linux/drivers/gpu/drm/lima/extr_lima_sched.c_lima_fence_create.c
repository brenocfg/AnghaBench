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
struct lima_sched_pipe {int /*<<< orphan*/  fence_seqno; int /*<<< orphan*/  fence_context; int /*<<< orphan*/  fence_lock; } ;
struct lima_fence {int /*<<< orphan*/  base; struct lima_sched_pipe* pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lima_fence* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_fence_ops ; 
 int /*<<< orphan*/  lima_fence_slab ; 

__attribute__((used)) static struct lima_fence *lima_fence_create(struct lima_sched_pipe *pipe)
{
	struct lima_fence *fence;

	fence = kmem_cache_zalloc(lima_fence_slab, GFP_KERNEL);
	if (!fence)
		return NULL;

	fence->pipe = pipe;
	dma_fence_init(&fence->base, &lima_fence_ops, &pipe->fence_lock,
		       pipe->fence_context, ++pipe->fence_seqno);

	return fence;
}