#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* vma; int /*<<< orphan*/  addr; } ;
struct intel_engine_cs {int /*<<< orphan*/  i915; TYPE_3__ status_page; TYPE_2__* gt; } ;
typedef  void i915_vma ;
typedef  void drm_i915_gem_object ;
struct TYPE_5__ {TYPE_1__* ggtt; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HWS_NEEDS_PHYSICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (void*) ; 
 void* i915_gem_object_create_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* i915_gem_object_pin_map (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (void*) ; 
 int /*<<< orphan*/  i915_gem_object_set_cache_coherency (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (void*) ; 
 void* i915_vma_instance (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pin_ggtt_status_page (struct intel_engine_cs*,void*) ; 

__attribute__((used)) static int init_status_page(struct intel_engine_cs *engine)
{
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	void *vaddr;
	int ret;

	/*
	 * Though the HWS register does support 36bit addresses, historically
	 * we have had hangs and corruption reported due to wild writes if
	 * the HWS is placed above 4G. We only allow objects to be allocated
	 * in GFP_DMA32 for i965, and no earlier physical address users had
	 * access to more than 4G.
	 */
	obj = i915_gem_object_create_internal(engine->i915, PAGE_SIZE);
	if (IS_ERR(obj)) {
		DRM_ERROR("Failed to allocate status page\n");
		return PTR_ERR(obj);
	}

	i915_gem_object_set_cache_coherency(obj, I915_CACHE_LLC);

	vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, NULL);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto err;
	}

	vaddr = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_ERR(vaddr)) {
		ret = PTR_ERR(vaddr);
		goto err;
	}

	engine->status_page.addr = memset(vaddr, 0, PAGE_SIZE);
	engine->status_page.vma = vma;

	if (!HWS_NEEDS_PHYSICAL(engine->i915)) {
		ret = pin_ggtt_status_page(engine, vma);
		if (ret)
			goto err_unpin;
	}

	return 0;

err_unpin:
	i915_gem_object_unpin_map(obj);
err:
	i915_gem_object_put(obj);
	return ret;
}