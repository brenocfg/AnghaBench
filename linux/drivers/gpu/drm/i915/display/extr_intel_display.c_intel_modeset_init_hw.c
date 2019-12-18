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
struct TYPE_2__ {int /*<<< orphan*/  hw; int /*<<< orphan*/  actual; int /*<<< orphan*/  logical; } ;
struct drm_i915_private {TYPE_1__ cdclk; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_dump_cdclk_state (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  intel_update_cdclk (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_modeset_init_hw(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	intel_update_cdclk(dev_priv);
	intel_dump_cdclk_state(&dev_priv->cdclk.hw, "Current CDCLK");
	dev_priv->cdclk.logical = dev_priv->cdclk.actual = dev_priv->cdclk.hw;
}