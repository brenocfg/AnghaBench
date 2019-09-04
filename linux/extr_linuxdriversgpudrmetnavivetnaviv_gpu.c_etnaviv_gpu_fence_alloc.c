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
struct etnaviv_gpu {int /*<<< orphan*/  next_fence; int /*<<< orphan*/  fence_context; int /*<<< orphan*/  fence_spinlock; int /*<<< orphan*/  lock; } ;
struct dma_fence {int dummy; } ;
struct etnaviv_fence {struct dma_fence base; struct etnaviv_gpu* gpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_fence_ops ; 
 struct etnaviv_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dma_fence *etnaviv_gpu_fence_alloc(struct etnaviv_gpu *gpu)
{
	struct etnaviv_fence *f;

	/*
	 * GPU lock must already be held, otherwise fence completion order might
	 * not match the seqno order assigned here.
	 */
	lockdep_assert_held(&gpu->lock);

	f = kzalloc(sizeof(*f), GFP_KERNEL);
	if (!f)
		return NULL;

	f->gpu = gpu;

	dma_fence_init(&f->base, &etnaviv_fence_ops, &gpu->fence_spinlock,
		       gpu->fence_context, ++gpu->next_fence);

	return &f->base;
}