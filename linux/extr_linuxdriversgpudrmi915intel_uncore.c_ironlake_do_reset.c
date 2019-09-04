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
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILK_GDSR ; 
 int ILK_GRDOM_MEDIA ; 
 int ILK_GRDOM_RENDER ; 
 int ILK_GRDOM_RESET_ENABLE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ironlake_do_reset(struct drm_i915_private *dev_priv,
			     unsigned engine_mask)
{
	int ret;

	I915_WRITE(ILK_GDSR, ILK_GRDOM_RENDER | ILK_GRDOM_RESET_ENABLE);
	ret = intel_wait_for_register(dev_priv,
				      ILK_GDSR, ILK_GRDOM_RESET_ENABLE, 0,
				      500);
	if (ret) {
		DRM_DEBUG_DRIVER("Wait for render reset failed\n");
		goto out;
	}

	I915_WRITE(ILK_GDSR, ILK_GRDOM_MEDIA | ILK_GRDOM_RESET_ENABLE);
	ret = intel_wait_for_register(dev_priv,
				      ILK_GDSR, ILK_GRDOM_RESET_ENABLE, 0,
				      500);
	if (ret) {
		DRM_DEBUG_DRIVER("Wait for media reset failed\n");
		goto out;
	}

out:
	I915_WRITE(ILK_GDSR, 0);
	POSTING_READ(ILK_GDSR);
	return ret;
}