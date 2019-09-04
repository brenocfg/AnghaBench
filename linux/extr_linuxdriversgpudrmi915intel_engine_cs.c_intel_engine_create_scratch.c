#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_cs {struct i915_vma* scratch; TYPE_2__* i915; } ;
struct i915_vma {int dummy; } ;
typedef  struct i915_vma drm_i915_gem_object ;
struct TYPE_4__ {int /*<<< orphan*/  vm; } ;
struct TYPE_5__ {TYPE_1__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PIN_GLOBAL ; 
 int PIN_HIGH ; 
 int PTR_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  WARN_ON (struct i915_vma*) ; 
 struct i915_vma* i915_gem_object_create_internal (TYPE_2__*,unsigned int) ; 
 struct i915_vma* i915_gem_object_create_stolen (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int,int) ; 

int intel_engine_create_scratch(struct intel_engine_cs *engine,
				unsigned int size)
{
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	int ret;

	WARN_ON(engine->scratch);

	obj = i915_gem_object_create_stolen(engine->i915, size);
	if (!obj)
		obj = i915_gem_object_create_internal(engine->i915, size);
	if (IS_ERR(obj)) {
		DRM_ERROR("Failed to allocate scratch page\n");
		return PTR_ERR(obj);
	}

	vma = i915_vma_instance(obj, &engine->i915->ggtt.vm, NULL);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto err_unref;
	}

	ret = i915_vma_pin(vma, 0, 4096, PIN_GLOBAL | PIN_HIGH);
	if (ret)
		goto err_unref;

	engine->scratch = vma;
	return 0;

err_unref:
	i915_gem_object_put(obj);
	return ret;
}