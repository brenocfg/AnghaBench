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
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int AUDIO_OUTPUT_ENABLE (int) ; 
 int /*<<< orphan*/  HSW_AUD_PIN_ELD_CP_VLD ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_DOMAIN_AUDIO ; 
 int TRANSCODER_EDP ; 
 int /*<<< orphan*/  intel_display_power_is_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_ddi_is_audio_enabled(struct drm_i915_private *dev_priv,
				       enum transcoder cpu_transcoder)
{
	if (cpu_transcoder == TRANSCODER_EDP)
		return false;

	if (!intel_display_power_is_enabled(dev_priv, POWER_DOMAIN_AUDIO))
		return false;

	return I915_READ(HSW_AUD_PIN_ELD_CP_VLD) &
		AUDIO_OUTPUT_ENABLE(cpu_transcoder);
}