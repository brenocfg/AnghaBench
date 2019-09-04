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
struct TYPE_6__ {int /*<<< orphan*/  page_addr; int /*<<< orphan*/  ggtt_offset; void* vma; } ;
struct intel_engine_cs {TYPE_2__ status_page; TYPE_3__* i915; } ;
typedef  void i915_vma ;
typedef  void drm_i915_gem_object ;
struct TYPE_5__ {int /*<<< orphan*/  vm; } ;
struct TYPE_7__ {TYPE_1__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HAS_LLC (TYPE_3__*) ; 
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int PIN_GLOBAL ; 
 unsigned int PIN_HIGH ; 
 unsigned int PIN_MAPPABLE ; 
 int PTR_ERR (void*) ; 
 void* i915_gem_object_create_internal (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* i915_gem_object_pin_map (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (void*) ; 
 int i915_gem_object_set_cache_level (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_ggtt_offset (void*) ; 
 void* i915_vma_instance (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i915_vma_pin (void*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  i915_vma_unpin (void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_status_page(struct intel_engine_cs *engine)
{
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	unsigned int flags;
	void *vaddr;
	int ret;

	obj = i915_gem_object_create_internal(engine->i915, PAGE_SIZE);
	if (IS_ERR(obj)) {
		DRM_ERROR("Failed to allocate status page\n");
		return PTR_ERR(obj);
	}

	ret = i915_gem_object_set_cache_level(obj, I915_CACHE_LLC);
	if (ret)
		goto err;

	vma = i915_vma_instance(obj, &engine->i915->ggtt.vm, NULL);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto err;
	}

	flags = PIN_GLOBAL;
	if (!HAS_LLC(engine->i915))
		/* On g33, we cannot place HWS above 256MiB, so
		 * restrict its pinning to the low mappable arena.
		 * Though this restriction is not documented for
		 * gen4, gen5, or byt, they also behave similarly
		 * and hang if the HWS is placed at the top of the
		 * GTT. To generalise, it appears that all !llc
		 * platforms have issues with us placing the HWS
		 * above the mappable region (even though we never
		 * actually map it).
		 */
		flags |= PIN_MAPPABLE;
	else
		flags |= PIN_HIGH;
	ret = i915_vma_pin(vma, 0, 4096, flags);
	if (ret)
		goto err;

	vaddr = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_ERR(vaddr)) {
		ret = PTR_ERR(vaddr);
		goto err_unpin;
	}

	engine->status_page.vma = vma;
	engine->status_page.ggtt_offset = i915_ggtt_offset(vma);
	engine->status_page.page_addr = memset(vaddr, 0, PAGE_SIZE);
	return 0;

err_unpin:
	i915_vma_unpin(vma);
err:
	i915_gem_object_put(obj);
	return ret;
}