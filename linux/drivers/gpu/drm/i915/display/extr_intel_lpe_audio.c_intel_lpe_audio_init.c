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
 int ENODEV ; 
 scalar_t__ lpe_audio_detect (struct drm_i915_private*) ; 
 int lpe_audio_setup (struct drm_i915_private*) ; 

int intel_lpe_audio_init(struct drm_i915_private *dev_priv)
{
	int ret = -ENODEV;

	if (lpe_audio_detect(dev_priv)) {
		ret = lpe_audio_setup(dev_priv);
		if (ret < 0)
			DRM_ERROR("failed to setup LPE Audio bridge\n");
	}
	return ret;
}