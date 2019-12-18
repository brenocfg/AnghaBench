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
struct TYPE_4__ {TYPE_1__* crtc; } ;
struct intel_crtc_state {int cpu_transcoder; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int POWER_DOMAIN_TRANSCODER (int) ; 
 int POWER_DOMAIN_TRANSCODER_VDSC_PW2 ; 
 int TRANSCODER_A ; 
 int TRANSCODER_EDP ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

enum intel_display_power_domain
intel_dsc_power_domain(const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *i915 = to_i915(crtc_state->base.crtc->dev);
	enum transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	/*
	 * On ICL VDSC/joining for eDP transcoder uses a separate power well,
	 * PW2. This requires POWER_DOMAIN_TRANSCODER_VDSC_PW2 power domain.
	 * For any other transcoder, VDSC/joining uses the power well associated
	 * with the pipe/transcoder in use. Hence another reference on the
	 * transcoder power domain will suffice.
	 *
	 * On TGL we have the same mapping, but for transcoder A (the special
	 * TRANSCODER_EDP is gone).
	 */
	if (INTEL_GEN(i915) >= 12 && cpu_transcoder == TRANSCODER_A)
		return POWER_DOMAIN_TRANSCODER_VDSC_PW2;
	else if (cpu_transcoder == TRANSCODER_EDP)
		return POWER_DOMAIN_TRANSCODER_VDSC_PW2;
	else
		return POWER_DOMAIN_TRANSCODER(cpu_transcoder);
}