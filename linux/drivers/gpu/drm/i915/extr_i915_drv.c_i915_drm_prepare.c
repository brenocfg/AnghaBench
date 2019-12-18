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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_suspend (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int i915_drm_prepare(struct drm_device *dev)
{
	struct drm_i915_private *i915 = to_i915(dev);

	/*
	 * NB intel_display_suspend() may issue new requests after we've
	 * ostensibly marked the GPU as ready-to-sleep here. We need to
	 * split out that work and pull it forward so that after point,
	 * the GPU is not woken again.
	 */
	i915_gem_suspend(i915);

	return 0;
}