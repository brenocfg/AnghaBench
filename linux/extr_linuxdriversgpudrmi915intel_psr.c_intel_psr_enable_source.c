#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_dp {int dummy; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct intel_crtc_state {int cpu_transcoder; } ;
struct TYPE_6__ {scalar_t__ psr2_enabled; } ;
struct drm_i915_private {TYPE_3__ psr; } ;
struct drm_device {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  CHICKEN_TRANS (int) ; 
 int /*<<< orphan*/  EDP_PSR_DEBUG ; 
 int EDP_PSR_DEBUG_MASK_DISP_REG_WRITE ; 
 int EDP_PSR_DEBUG_MASK_HPD ; 
 int EDP_PSR_DEBUG_MASK_LPSP ; 
 int EDP_PSR_DEBUG_MASK_MAX_SLEEP ; 
 int EDP_PSR_DEBUG_MASK_MEMUP ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int PSR2_ADD_VERTICAL_LINE_COUNT ; 
 int PSR2_VSC_ENABLE_PROG_HEADER ; 
 int VSC_DATA_SEL_SOFTWARE_CONTROL ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  hsw_psr_setup_aux (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void intel_psr_enable_source(struct intel_dp *intel_dp,
				    const struct intel_crtc_state *crtc_state)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	/* Only HSW and BDW have PSR AUX registers that need to be setup. SKL+
	 * use hardcoded values PSR AUX transactions
	 */
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		hsw_psr_setup_aux(intel_dp);

	if (dev_priv->psr.psr2_enabled) {
		u32 chicken = I915_READ(CHICKEN_TRANS(cpu_transcoder));

		if (INTEL_GEN(dev_priv) == 9 && !IS_GEMINILAKE(dev_priv))
			chicken |= (PSR2_VSC_ENABLE_PROG_HEADER
				   | PSR2_ADD_VERTICAL_LINE_COUNT);

		else
			chicken &= ~VSC_DATA_SEL_SOFTWARE_CONTROL;
		I915_WRITE(CHICKEN_TRANS(cpu_transcoder), chicken);

		I915_WRITE(EDP_PSR_DEBUG,
			   EDP_PSR_DEBUG_MASK_MEMUP |
			   EDP_PSR_DEBUG_MASK_HPD |
			   EDP_PSR_DEBUG_MASK_LPSP |
			   EDP_PSR_DEBUG_MASK_MAX_SLEEP |
			   EDP_PSR_DEBUG_MASK_DISP_REG_WRITE);
	} else {
		/*
		 * Per Spec: Avoid continuous PSR exit by masking MEMUP
		 * and HPD. also mask LPSP to avoid dependency on other
		 * drivers that might block runtime_pm besides
		 * preventing  other hw tracking issues now we can rely
		 * on frontbuffer tracking.
		 */
		I915_WRITE(EDP_PSR_DEBUG,
			   EDP_PSR_DEBUG_MASK_MEMUP |
			   EDP_PSR_DEBUG_MASK_HPD |
			   EDP_PSR_DEBUG_MASK_LPSP |
			   EDP_PSR_DEBUG_MASK_DISP_REG_WRITE |
			   EDP_PSR_DEBUG_MASK_MAX_SLEEP);
	}
}