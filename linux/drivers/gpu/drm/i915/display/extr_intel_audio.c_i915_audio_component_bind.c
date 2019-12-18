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
struct TYPE_2__ {struct device* dev; int /*<<< orphan*/ * ops; } ;
struct i915_audio_component {scalar_t__* aud_sample_rate; TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; struct i915_audio_component* audio_component; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DL_FLAG_STATELESS ; 
 int EEXIST ; 
 int ENOMEM ; 
 scalar_t__ I915_MAX_PORTS ; 
 scalar_t__ MAX_PORTS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  device_link_add (struct device*,struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_audio_component_ops ; 
 struct drm_i915_private* kdev_to_i915 (struct device*) ; 

__attribute__((used)) static int i915_audio_component_bind(struct device *i915_kdev,
				     struct device *hda_kdev, void *data)
{
	struct i915_audio_component *acomp = data;
	struct drm_i915_private *dev_priv = kdev_to_i915(i915_kdev);
	int i;

	if (WARN_ON(acomp->base.ops || acomp->base.dev))
		return -EEXIST;

	if (WARN_ON(!device_link_add(hda_kdev, i915_kdev, DL_FLAG_STATELESS)))
		return -ENOMEM;

	drm_modeset_lock_all(&dev_priv->drm);
	acomp->base.ops = &i915_audio_component_ops;
	acomp->base.dev = i915_kdev;
	BUILD_BUG_ON(MAX_PORTS != I915_MAX_PORTS);
	for (i = 0; i < ARRAY_SIZE(acomp->aud_sample_rate); i++)
		acomp->aud_sample_rate[i] = 0;
	dev_priv->audio_component = acomp;
	drm_modeset_unlock_all(&dev_priv->drm);

	return 0;
}