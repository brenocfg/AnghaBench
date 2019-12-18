#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dma_fence {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {TYPE_1__ wait; } ;
struct stub_fence {struct dma_fence dma; TYPE_3__ chain; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct drm_i915_gem_object {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_FENCE_GFP ; 
 int /*<<< orphan*/  I915_FENCE_TIMEOUT ; 
 int /*<<< orphan*/  assert_object_held (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,struct dma_fence*) ; 
 scalar_t__ i915_sw_fence_await_reservation (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_sw_fence_init (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct stub_fence* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub_fence_ops ; 
 int /*<<< orphan*/  stub_notify ; 
 int /*<<< orphan*/  stub_release (struct dma_fence*) ; 

struct dma_fence *
i915_gem_object_lock_fence(struct drm_i915_gem_object *obj)
{
	struct stub_fence *stub;

	assert_object_held(obj);

	stub = kmalloc(sizeof(*stub), GFP_KERNEL);
	if (!stub)
		return NULL;

	i915_sw_fence_init(&stub->chain, stub_notify);
	dma_fence_init(&stub->dma, &stub_fence_ops, &stub->chain.wait.lock,
		       0, 0);

	if (i915_sw_fence_await_reservation(&stub->chain,
					    obj->base.resv, NULL,
					    true, I915_FENCE_TIMEOUT,
					    I915_FENCE_GFP) < 0)
		goto err;

	dma_resv_add_excl_fence(obj->base.resv, &stub->dma);

	return &stub->dma;

err:
	stub_release(&stub->dma);
	return NULL;
}