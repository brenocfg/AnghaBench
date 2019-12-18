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
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_audio_component_bind_ops ; 

__attribute__((used)) static void i915_audio_component_cleanup(struct drm_i915_private *dev_priv)
{
	if (!dev_priv->audio_component_registered)
		return;

	component_del(dev_priv->drm.dev, &i915_audio_component_bind_ops);
	dev_priv->audio_component_registered = false;
}