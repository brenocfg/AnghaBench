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
typedef  int u64 ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {TYPE_1__* filp; int /*<<< orphan*/  size; } ;
struct drm_i915_gem_object {void* read_domains; void* write_domain; TYPE_2__ base; } ;
struct address_space {int dummy; } ;
typedef  int gfp_t ;
struct TYPE_3__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 struct drm_i915_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GFP_HIGHUSER ; 
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 unsigned int I915_CACHE_LLC ; 
 unsigned int I915_CACHE_NONE ; 
 void* I915_GEM_DOMAIN_CPU ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ IS_I965G (struct drm_i915_private*) ; 
 scalar_t__ IS_I965GM (struct drm_i915_private*) ; 
 scalar_t__ PAGE_SHIFT ; 
 int __GFP_DMA32 ; 
 int __GFP_HIGHMEM ; 
 int __GFP_RECLAIM ; 
 int __GFP_RECLAIMABLE ; 
 int create_shmem (struct drm_i915_private*,TYPE_2__*,int) ; 
 struct drm_i915_gem_object* i915_gem_object_alloc () ; 
 int /*<<< orphan*/  i915_gem_object_free (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_init (struct drm_i915_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_set_cache_coherency (struct drm_i915_gem_object*,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_shmem_ops ; 
 int mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (struct address_space*,int) ; 
 scalar_t__ overflows_type (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_i915_gem_object_create (struct drm_i915_gem_object*) ; 

struct drm_i915_gem_object *
i915_gem_object_create_shmem(struct drm_i915_private *i915, u64 size)
{
	struct drm_i915_gem_object *obj;
	struct address_space *mapping;
	unsigned int cache_level;
	gfp_t mask;
	int ret;

	/* There is a prevalence of the assumption that we fit the object's
	 * page count inside a 32bit _signed_ variable. Let's document this and
	 * catch if we ever need to fix it. In the meantime, if you do spot
	 * such a local variable, please consider fixing!
	 */
	if (size >> PAGE_SHIFT > INT_MAX)
		return ERR_PTR(-E2BIG);

	if (overflows_type(size, obj->base.size))
		return ERR_PTR(-E2BIG);

	obj = i915_gem_object_alloc();
	if (!obj)
		return ERR_PTR(-ENOMEM);

	ret = create_shmem(i915, &obj->base, size);
	if (ret)
		goto fail;

	mask = GFP_HIGHUSER | __GFP_RECLAIMABLE;
	if (IS_I965GM(i915) || IS_I965G(i915)) {
		/* 965gm cannot relocate objects above 4GiB. */
		mask &= ~__GFP_HIGHMEM;
		mask |= __GFP_DMA32;
	}

	mapping = obj->base.filp->f_mapping;
	mapping_set_gfp_mask(mapping, mask);
	GEM_BUG_ON(!(mapping_gfp_mask(mapping) & __GFP_RECLAIM));

	i915_gem_object_init(obj, &i915_gem_shmem_ops);

	obj->write_domain = I915_GEM_DOMAIN_CPU;
	obj->read_domains = I915_GEM_DOMAIN_CPU;

	if (HAS_LLC(i915))
		/* On some devices, we can have the GPU use the LLC (the CPU
		 * cache) for about a 10% performance improvement
		 * compared to uncached.  Graphics requests other than
		 * display scanout are coherent with the CPU in
		 * accessing this cache.  This means in this mode we
		 * don't need to clflush on the CPU side, and on the
		 * GPU side we only need to flush internal caches to
		 * get data visible to the CPU.
		 *
		 * However, we maintain the display planes as UC, and so
		 * need to rebind when first used as such.
		 */
		cache_level = I915_CACHE_LLC;
	else
		cache_level = I915_CACHE_NONE;

	i915_gem_object_set_cache_coherency(obj, cache_level);

	trace_i915_gem_object_create(obj);

	return obj;

fail:
	i915_gem_object_free(obj);
	return ERR_PTR(ret);
}