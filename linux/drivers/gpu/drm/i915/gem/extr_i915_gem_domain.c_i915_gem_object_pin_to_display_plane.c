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
struct i915_vma {int /*<<< orphan*/  display_alignment; } ;
struct i915_ggtt_view {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  pin_global; int /*<<< orphan*/  read_domains; TYPE_1__ base; } ;

/* Variables and functions */
 int ENOSPC ; 
 struct i915_vma* ERR_PTR (int) ; 
 scalar_t__ HAS_WT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_CACHE_NONE ; 
 int /*<<< orphan*/  I915_CACHE_WT ; 
 int /*<<< orphan*/  I915_GEM_DOMAIN_GTT ; 
 scalar_t__ I915_GGTT_VIEW_NORMAL ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 unsigned int PIN_MAPPABLE ; 
 unsigned int PIN_NONBLOCK ; 
 int /*<<< orphan*/  __i915_gem_object_flush_for_display (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  assert_object_held (struct drm_i915_gem_object*) ; 
 struct i915_vma* i915_gem_object_ggtt_pin (struct drm_i915_gem_object*,struct i915_ggtt_view const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int i915_gem_object_set_cache_level (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

struct i915_vma *
i915_gem_object_pin_to_display_plane(struct drm_i915_gem_object *obj,
				     u32 alignment,
				     const struct i915_ggtt_view *view,
				     unsigned int flags)
{
	struct i915_vma *vma;
	int ret;

	assert_object_held(obj);

	/* Mark the global pin early so that we account for the
	 * display coherency whilst setting up the cache domains.
	 */
	obj->pin_global++;

	/* The display engine is not coherent with the LLC cache on gen6.  As
	 * a result, we make sure that the pinning that is about to occur is
	 * done with uncached PTEs. This is lowest common denominator for all
	 * chipsets.
	 *
	 * However for gen6+, we could do better by using the GFDT bit instead
	 * of uncaching, which would allow us to flush all the LLC-cached data
	 * with that bit in the PTE to main memory with just one PIPE_CONTROL.
	 */
	ret = i915_gem_object_set_cache_level(obj,
					      HAS_WT(to_i915(obj->base.dev)) ?
					      I915_CACHE_WT : I915_CACHE_NONE);
	if (ret) {
		vma = ERR_PTR(ret);
		goto err_unpin_global;
	}

	/* As the user may map the buffer once pinned in the display plane
	 * (e.g. libkms for the bootup splash), we have to ensure that we
	 * always use map_and_fenceable for all scanout buffers. However,
	 * it may simply be too big to fit into mappable, in which case
	 * put it anyway and hope that userspace can cope (but always first
	 * try to preserve the existing ABI).
	 */
	vma = ERR_PTR(-ENOSPC);
	if ((flags & PIN_MAPPABLE) == 0 &&
	    (!view || view->type == I915_GGTT_VIEW_NORMAL))
		vma = i915_gem_object_ggtt_pin(obj, view, 0, alignment,
					       flags |
					       PIN_MAPPABLE |
					       PIN_NONBLOCK);
	if (IS_ERR(vma))
		vma = i915_gem_object_ggtt_pin(obj, view, 0, alignment, flags);
	if (IS_ERR(vma))
		goto err_unpin_global;

	vma->display_alignment = max_t(u64, vma->display_alignment, alignment);

	__i915_gem_object_flush_for_display(obj);

	/* It should now be out of any other write domains, and we can update
	 * the domain values for our changes.
	 */
	obj->read_domains |= I915_GEM_DOMAIN_GTT;

	return vma;

err_unpin_global:
	obj->pin_global--;
	return vma;
}