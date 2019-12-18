#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc4_dev {int /*<<< orphan*/  bo_lock; } ;
struct drm_gem_object {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct drm_gem_object base; } ;
struct vc4_bo {TYPE_2__* validated_shader; TYPE_1__ base; } ;
struct TYPE_4__ {struct TYPE_4__* texture_samples; struct TYPE_4__* uniform_addr_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_cma_free_object (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_bo_set_label (struct drm_gem_object*,int) ; 

__attribute__((used)) static void vc4_bo_destroy(struct vc4_bo *bo)
{
	struct drm_gem_object *obj = &bo->base.base;
	struct vc4_dev *vc4 = to_vc4_dev(obj->dev);

	lockdep_assert_held(&vc4->bo_lock);

	vc4_bo_set_label(obj, -1);

	if (bo->validated_shader) {
		kfree(bo->validated_shader->uniform_addr_offsets);
		kfree(bo->validated_shader->texture_samples);
		kfree(bo->validated_shader);
		bo->validated_shader = NULL;
	}

	drm_gem_cma_free_object(obj);
}