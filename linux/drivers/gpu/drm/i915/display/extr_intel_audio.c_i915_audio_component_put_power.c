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
struct drm_i915_private {scalar_t__ audio_power_refcount; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_AUDIO ; 
 int /*<<< orphan*/  glk_force_audio_cdclk (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,unsigned long) ; 
 struct drm_i915_private* kdev_to_i915 (struct device*) ; 

__attribute__((used)) static void i915_audio_component_put_power(struct device *kdev,
					   unsigned long cookie)
{
	struct drm_i915_private *dev_priv = kdev_to_i915(kdev);

	/* Stop forcing CDCLK to 2*BCLK if no need for audio to be powered. */
	if (--dev_priv->audio_power_refcount == 0)
		if (IS_CANNONLAKE(dev_priv) || IS_GEMINILAKE(dev_priv))
			glk_force_audio_cdclk(dev_priv, false);

	intel_display_power_put(dev_priv, POWER_DOMAIN_AUDIO, cookie);
}