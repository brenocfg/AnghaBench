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
struct drm_i915_gem_execbuffer2 {int flags; int DR4; int batch_start_offset; int batch_len; scalar_t__ DR1; scalar_t__ cliprects_ptr; scalar_t__ num_cliprects; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int I915_EXEC_FENCE_ARRAY ; 
 int __I915_EXEC_ILLEGAL_FLAGS ; 

__attribute__((used)) static bool i915_gem_check_execbuffer(struct drm_i915_gem_execbuffer2 *exec)
{
	if (exec->flags & __I915_EXEC_ILLEGAL_FLAGS)
		return false;

	/* Kernel clipping was a DRI1 misfeature */
	if (!(exec->flags & I915_EXEC_FENCE_ARRAY)) {
		if (exec->num_cliprects || exec->cliprects_ptr)
			return false;
	}

	if (exec->DR4 == 0xffffffff) {
		DRM_DEBUG("UXA submitting garbage DR4, fixing up\n");
		exec->DR4 = 0;
	}
	if (exec->DR1 || exec->DR4)
		return false;

	if ((exec->batch_start_offset | exec->batch_len) & 0x7)
		return false;

	return true;
}