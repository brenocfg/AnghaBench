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
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i915_gem_suspend (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int i915_drm_prepare(struct drm_device *dev)
{
	struct drm_i915_private *i915 = to_i915(dev);
	int err;

	/*
	 * NB intel_display_suspend() may issue new requests after we've
	 * ostensibly marked the GPU as ready-to-sleep here. We need to
	 * split out that work and pull it forward so that after point,
	 * the GPU is not woken again.
	 */
	err = i915_gem_suspend(i915);
	if (err)
		dev_err(&i915->drm.pdev->dev,
			"GEM idle failed, suspend/resume might fail\n");

	return err;
}