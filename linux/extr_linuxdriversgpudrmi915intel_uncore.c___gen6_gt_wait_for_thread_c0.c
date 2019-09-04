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
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int GEN6_GT_THREAD_STATUS_CORE_MASK ; 
 int /*<<< orphan*/  GEN6_GT_THREAD_STATUS_REG ; 
 int __raw_i915_read32 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_atomic_us (int,int) ; 

__attribute__((used)) static void __gen6_gt_wait_for_thread_c0(struct drm_i915_private *dev_priv)
{
	/* w/a for a sporadic read returning 0 by waiting for the GT
	 * thread to wake up.
	 */
	if (wait_for_atomic_us((__raw_i915_read32(dev_priv, GEN6_GT_THREAD_STATUS_REG) &
				GEN6_GT_THREAD_STATUS_CORE_MASK) == 0, 500))
		DRM_ERROR("GT thread status wait timed out\n");
}