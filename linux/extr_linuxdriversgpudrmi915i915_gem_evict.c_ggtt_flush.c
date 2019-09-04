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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 int I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  ggtt_is_idle (struct drm_i915_private*) ; 
 int i915_gem_switch_to_kernel_context (struct drm_i915_private*) ; 
 int i915_gem_wait_for_idle (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ggtt_flush(struct drm_i915_private *i915)
{
	int err;

	/* Not everything in the GGTT is tracked via vma (otherwise we
	 * could evict as required with minimal stalling) so we are forced
	 * to idle the GPU and explicitly retire outstanding requests in
	 * the hopes that we can then remove contexts and the like only
	 * bound by their active reference.
	 */
	err = i915_gem_switch_to_kernel_context(i915);
	if (err)
		return err;

	err = i915_gem_wait_for_idle(i915,
				     I915_WAIT_INTERRUPTIBLE |
				     I915_WAIT_LOCKED,
				     MAX_SCHEDULE_TIMEOUT);
	if (err)
		return err;

	GEM_BUG_ON(!ggtt_is_idle(i915));
	return 0;
}