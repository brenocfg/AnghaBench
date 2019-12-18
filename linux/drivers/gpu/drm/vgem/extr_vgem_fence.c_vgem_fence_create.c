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
struct vgem_file {int dummy; } ;
struct dma_fence {int dummy; } ;
struct vgem_fence {struct dma_fence base; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VGEM_FENCE_TIMEOUT ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 struct vgem_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgem_fence_ops ; 
 int /*<<< orphan*/  vgem_fence_timeout ; 

__attribute__((used)) static struct dma_fence *vgem_fence_create(struct vgem_file *vfile,
					   unsigned int flags)
{
	struct vgem_fence *fence;

	fence = kzalloc(sizeof(*fence), GFP_KERNEL);
	if (!fence)
		return NULL;

	spin_lock_init(&fence->lock);
	dma_fence_init(&fence->base, &vgem_fence_ops, &fence->lock,
		       dma_fence_context_alloc(1), 1);

	timer_setup(&fence->timer, vgem_fence_timeout, 0);

	/* We force the fence to expire within 10s to prevent driver hangs */
	mod_timer(&fence->timer, jiffies + VGEM_FENCE_TIMEOUT);

	return &fence->base;
}