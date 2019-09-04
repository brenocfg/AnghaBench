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
struct intel_engine_cs {int dummy; } ;
struct drm_i915_private {struct intel_engine_cs** engine; } ;
struct drm_i915_gem_execbuffer2 {unsigned int flags; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int) ; 
 scalar_t__ HAS_BSD2 (struct drm_i915_private*) ; 
 unsigned int I915_EXEC_BSD ; 
 unsigned int I915_EXEC_BSD_DEFAULT ; 
 unsigned int I915_EXEC_BSD_MASK ; 
 unsigned int I915_EXEC_BSD_RING1 ; 
 unsigned int I915_EXEC_BSD_RING2 ; 
 unsigned int I915_EXEC_BSD_SHIFT ; 
 unsigned int I915_EXEC_RING_MASK ; 
 unsigned int I915_USER_RINGS ; 
 size_t _VCS (unsigned int) ; 
 unsigned int gen8_dispatch_bsd_engine (struct drm_i915_private*,struct drm_file*) ; 
 size_t* user_ring_map ; 

__attribute__((used)) static struct intel_engine_cs *
eb_select_engine(struct drm_i915_private *dev_priv,
		 struct drm_file *file,
		 struct drm_i915_gem_execbuffer2 *args)
{
	unsigned int user_ring_id = args->flags & I915_EXEC_RING_MASK;
	struct intel_engine_cs *engine;

	if (user_ring_id > I915_USER_RINGS) {
		DRM_DEBUG("execbuf with unknown ring: %u\n", user_ring_id);
		return NULL;
	}

	if ((user_ring_id != I915_EXEC_BSD) &&
	    ((args->flags & I915_EXEC_BSD_MASK) != 0)) {
		DRM_DEBUG("execbuf with non bsd ring but with invalid "
			  "bsd dispatch flags: %d\n", (int)(args->flags));
		return NULL;
	}

	if (user_ring_id == I915_EXEC_BSD && HAS_BSD2(dev_priv)) {
		unsigned int bsd_idx = args->flags & I915_EXEC_BSD_MASK;

		if (bsd_idx == I915_EXEC_BSD_DEFAULT) {
			bsd_idx = gen8_dispatch_bsd_engine(dev_priv, file);
		} else if (bsd_idx >= I915_EXEC_BSD_RING1 &&
			   bsd_idx <= I915_EXEC_BSD_RING2) {
			bsd_idx >>= I915_EXEC_BSD_SHIFT;
			bsd_idx--;
		} else {
			DRM_DEBUG("execbuf with unknown bsd ring: %u\n",
				  bsd_idx);
			return NULL;
		}

		engine = dev_priv->engine[_VCS(bsd_idx)];
	} else {
		engine = dev_priv->engine[user_ring_map[user_ring_id]];
	}

	if (!engine) {
		DRM_DEBUG("execbuf with invalid ring: %u\n", user_ring_id);
		return NULL;
	}

	return engine;
}