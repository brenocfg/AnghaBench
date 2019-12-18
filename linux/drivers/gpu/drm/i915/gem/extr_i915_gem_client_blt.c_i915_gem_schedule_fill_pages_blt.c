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
typedef  int /*<<< orphan*/  u32 ;
struct sg_table {int dummy; } ;
struct intel_context {int /*<<< orphan*/  vm; } ;
struct i915_sleeve {int dummy; } ;
struct i915_page_sizes {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct clear_pages_work {int /*<<< orphan*/  wait; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  work; struct intel_context* ce; struct i915_sleeve* sleeve; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_FENCE_GFP ; 
 int /*<<< orphan*/  I915_FENCE_TIMEOUT ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_sleeve*) ; 
 int PTR_ERR (struct i915_sleeve*) ; 
 int /*<<< orphan*/  clear_pages_signal_irq_worker ; 
 int /*<<< orphan*/  clear_pages_work_notify ; 
 int /*<<< orphan*/  clear_pages_work_ops ; 
 int /*<<< orphan*/  clear_pages_worker ; 
 struct i915_sleeve* create_sleeve (int /*<<< orphan*/ ,struct drm_i915_gem_object*,struct sg_table*,struct i915_page_sizes*) ; 
 int /*<<< orphan*/  destroy_sleeve (struct i915_sleeve*) ; 
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_set_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fence_lock ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int i915_sw_fence_await_reservation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_sw_fence_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_sw_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct clear_pages_work* kmalloc (int,int /*<<< orphan*/ ) ; 

int i915_gem_schedule_fill_pages_blt(struct drm_i915_gem_object *obj,
				     struct intel_context *ce,
				     struct sg_table *pages,
				     struct i915_page_sizes *page_sizes,
				     u32 value)
{
	struct clear_pages_work *work;
	struct i915_sleeve *sleeve;
	int err;

	sleeve = create_sleeve(ce->vm, obj, pages, page_sizes);
	if (IS_ERR(sleeve))
		return PTR_ERR(sleeve);

	work = kmalloc(sizeof(*work), GFP_KERNEL);
	if (!work) {
		destroy_sleeve(sleeve);
		return -ENOMEM;
	}

	work->value = value;
	work->sleeve = sleeve;
	work->ce = ce;

	INIT_WORK(&work->work, clear_pages_worker);

	init_irq_work(&work->irq_work, clear_pages_signal_irq_worker);

	dma_fence_init(&work->dma, &clear_pages_work_ops, &fence_lock, 0, 0);
	i915_sw_fence_init(&work->wait, clear_pages_work_notify);

	i915_gem_object_lock(obj);
	err = i915_sw_fence_await_reservation(&work->wait,
					      obj->base.resv, NULL,
					      true, I915_FENCE_TIMEOUT,
					      I915_FENCE_GFP);
	if (err < 0) {
		dma_fence_set_error(&work->dma, err);
	} else {
		dma_resv_add_excl_fence(obj->base.resv, &work->dma);
		err = 0;
	}
	i915_gem_object_unlock(obj);

	dma_fence_get(&work->dma);
	i915_sw_fence_commit(&work->wait);

	return err;
}