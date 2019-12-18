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
struct TYPE_2__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; } ;
struct i915_audio_component {TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; int /*<<< orphan*/ * audio_component; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_link_remove (struct device*,struct device*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* kdev_to_i915 (struct device*) ; 

__attribute__((used)) static void i915_audio_component_unbind(struct device *i915_kdev,
					struct device *hda_kdev, void *data)
{
	struct i915_audio_component *acomp = data;
	struct drm_i915_private *dev_priv = kdev_to_i915(i915_kdev);

	drm_modeset_lock_all(&dev_priv->drm);
	acomp->base.ops = NULL;
	acomp->base.dev = NULL;
	dev_priv->audio_component = NULL;
	drm_modeset_unlock_all(&dev_priv->drm);

	device_link_remove(hda_kdev, i915_kdev);
}