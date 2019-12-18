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
struct i915_execbuffer {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_execbuffer2 {unsigned int flags; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int) ; 
 unsigned int I915_EXEC_BSD ; 
 unsigned int I915_EXEC_BSD_DEFAULT ; 
 unsigned int I915_EXEC_BSD_MASK ; 
 unsigned int I915_EXEC_BSD_RING1 ; 
 unsigned int I915_EXEC_BSD_RING2 ; 
 unsigned int I915_EXEC_BSD_SHIFT ; 
 unsigned int I915_EXEC_RING_MASK ; 
 unsigned int _VCS (unsigned int) ; 
 unsigned int gen8_dispatch_bsd_engine (struct drm_i915_private*,struct drm_file*) ; 
 int num_vcs_engines (struct drm_i915_private*) ; 
 unsigned int* user_ring_map ; 

__attribute__((used)) static unsigned int
eb_select_legacy_ring(struct i915_execbuffer *eb,
		      struct drm_file *file,
		      struct drm_i915_gem_execbuffer2 *args)
{
	struct drm_i915_private *i915 = eb->i915;
	unsigned int user_ring_id = args->flags & I915_EXEC_RING_MASK;

	if (user_ring_id != I915_EXEC_BSD &&
	    (args->flags & I915_EXEC_BSD_MASK)) {
		DRM_DEBUG("execbuf with non bsd ring but with invalid "
			  "bsd dispatch flags: %d\n", (int)(args->flags));
		return -1;
	}

	if (user_ring_id == I915_EXEC_BSD && num_vcs_engines(i915) > 1) {
		unsigned int bsd_idx = args->flags & I915_EXEC_BSD_MASK;

		if (bsd_idx == I915_EXEC_BSD_DEFAULT) {
			bsd_idx = gen8_dispatch_bsd_engine(i915, file);
		} else if (bsd_idx >= I915_EXEC_BSD_RING1 &&
			   bsd_idx <= I915_EXEC_BSD_RING2) {
			bsd_idx >>= I915_EXEC_BSD_SHIFT;
			bsd_idx--;
		} else {
			DRM_DEBUG("execbuf with unknown bsd ring: %u\n",
				  bsd_idx);
			return -1;
		}

		return _VCS(bsd_idx);
	}

	if (user_ring_id >= ARRAY_SIZE(user_ring_map)) {
		DRM_DEBUG("execbuf with unknown ring: %u\n", user_ring_id);
		return -1;
	}

	return user_ring_map[user_ring_id];
}