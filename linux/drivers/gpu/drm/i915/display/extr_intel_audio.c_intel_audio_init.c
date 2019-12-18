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
 int /*<<< orphan*/  i915_audio_component_init (struct drm_i915_private*) ; 
 scalar_t__ intel_lpe_audio_init (struct drm_i915_private*) ; 

void intel_audio_init(struct drm_i915_private *dev_priv)
{
	if (intel_lpe_audio_init(dev_priv) < 0)
		i915_audio_component_init(dev_priv);
}