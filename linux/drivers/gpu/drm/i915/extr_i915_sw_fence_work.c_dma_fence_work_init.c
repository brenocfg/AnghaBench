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
struct dma_fence_work_ops {int dummy; } ;
struct dma_fence_work {struct dma_fence_work_ops const* ops; int /*<<< orphan*/  work; int /*<<< orphan*/  chain; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fence_notify ; 
 int /*<<< orphan*/  fence_ops ; 
 int /*<<< orphan*/  fence_work ; 
 int /*<<< orphan*/  i915_sw_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void dma_fence_work_init(struct dma_fence_work *f,
			 const struct dma_fence_work_ops *ops)
{
	spin_lock_init(&f->lock);
	dma_fence_init(&f->dma, &fence_ops, &f->lock, 0, 0);
	i915_sw_fence_init(&f->chain, fence_notify);
	INIT_WORK(&f->work, fence_work);

	f->ops = ops;
}