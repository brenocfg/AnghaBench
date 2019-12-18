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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {int audio_component_registered; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  I915_COMPONENT_AUDIO ; 
 int component_add_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_audio_component_bind_ops ; 

__attribute__((used)) static void i915_audio_component_init(struct drm_i915_private *dev_priv)
{
	int ret;

	ret = component_add_typed(dev_priv->drm.dev,
				  &i915_audio_component_bind_ops,
				  I915_COMPONENT_AUDIO);
	if (ret < 0) {
		DRM_ERROR("failed to add audio component (%d)\n", ret);
		/* continue with reduced functionality */
		return;
	}

	dev_priv->audio_component_registered = true;
}