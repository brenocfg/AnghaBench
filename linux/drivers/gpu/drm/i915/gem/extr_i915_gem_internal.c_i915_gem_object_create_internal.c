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
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct drm_i915_gem_object {void* write_domain; void* read_domains; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_i915_gem_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 unsigned int I915_CACHE_LLC ; 
 unsigned int I915_CACHE_NONE ; 
 void* I915_GEM_DOMAIN_CPU ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  drm_gem_private_object_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* i915_gem_object_alloc () ; 
 int /*<<< orphan*/  i915_gem_object_init (struct drm_i915_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_internal_ops ; 
 int /*<<< orphan*/  i915_gem_object_set_cache_coherency (struct drm_i915_gem_object*,unsigned int) ; 
 scalar_t__ overflows_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct drm_i915_gem_object *
i915_gem_object_create_internal(struct drm_i915_private *i915,
				phys_addr_t size)
{
	struct drm_i915_gem_object *obj;
	unsigned int cache_level;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, PAGE_SIZE));

	if (overflows_type(size, obj->base.size))
		return ERR_PTR(-E2BIG);

	obj = i915_gem_object_alloc();
	if (!obj)
		return ERR_PTR(-ENOMEM);

	drm_gem_private_object_init(&i915->drm, &obj->base, size);
	i915_gem_object_init(obj, &i915_gem_object_internal_ops);

	obj->read_domains = I915_GEM_DOMAIN_CPU;
	obj->write_domain = I915_GEM_DOMAIN_CPU;

	cache_level = HAS_LLC(i915) ? I915_CACHE_LLC : I915_CACHE_NONE;
	i915_gem_object_set_cache_coherency(obj, cache_level);

	return obj;
}