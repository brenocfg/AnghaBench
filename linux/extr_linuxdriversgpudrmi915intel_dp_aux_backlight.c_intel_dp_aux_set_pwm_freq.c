#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_2__* encoder; TYPE_1__ base; } ;
struct TYPE_7__ {int pwm_freq_hz; } ;
struct TYPE_8__ {TYPE_3__ backlight; } ;
struct drm_i915_private {TYPE_4__ vbt; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  DP_EDP_BACKLIGHT_FREQ_BASE_KHZ ; 
 int /*<<< orphan*/  DP_EDP_BACKLIGHT_FREQ_SET ; 
 int /*<<< orphan*/  DP_EDP_PWMGEN_BIT_COUNT ; 
 int /*<<< orphan*/  DP_EDP_PWMGEN_BIT_COUNT_CAP_MAX ; 
 int /*<<< orphan*/  DP_EDP_PWMGEN_BIT_COUNT_CAP_MIN ; 
 int DP_EDP_PWMGEN_BIT_COUNT_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int KHz (int /*<<< orphan*/ ) ; 
 int clamp (int,int,int) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_dp_aux_set_pwm_freq(struct intel_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_dp *intel_dp = enc_to_intel_dp(&connector->encoder->base);
	int freq, fxp, fxp_min, fxp_max, fxp_actual, f = 1;
	u8 pn, pn_min, pn_max;

	/* Find desired value of (F x P)
	 * Note that, if F x P is out of supported range, the maximum value or
	 * minimum value will applied automatically. So no need to check that.
	 */
	freq = dev_priv->vbt.backlight.pwm_freq_hz;
	DRM_DEBUG_KMS("VBT defined backlight frequency %u Hz\n", freq);
	if (!freq) {
		DRM_DEBUG_KMS("Use panel default backlight frequency\n");
		return false;
	}

	fxp = DIV_ROUND_CLOSEST(KHz(DP_EDP_BACKLIGHT_FREQ_BASE_KHZ), freq);

	/* Use highest possible value of Pn for more granularity of brightness
	 * adjustment while satifying the conditions below.
	 * - Pn is in the range of Pn_min and Pn_max
	 * - F is in the range of 1 and 255
	 * - FxP is within 25% of desired value.
	 *   Note: 25% is arbitrary value and may need some tweak.
	 */
	if (drm_dp_dpcd_readb(&intel_dp->aux,
			       DP_EDP_PWMGEN_BIT_COUNT_CAP_MIN, &pn_min) != 1) {
		DRM_DEBUG_KMS("Failed to read pwmgen bit count cap min\n");
		return false;
	}
	if (drm_dp_dpcd_readb(&intel_dp->aux,
			       DP_EDP_PWMGEN_BIT_COUNT_CAP_MAX, &pn_max) != 1) {
		DRM_DEBUG_KMS("Failed to read pwmgen bit count cap max\n");
		return false;
	}
	pn_min &= DP_EDP_PWMGEN_BIT_COUNT_MASK;
	pn_max &= DP_EDP_PWMGEN_BIT_COUNT_MASK;

	fxp_min = DIV_ROUND_CLOSEST(fxp * 3, 4);
	fxp_max = DIV_ROUND_CLOSEST(fxp * 5, 4);
	if (fxp_min < (1 << pn_min) || (255 << pn_max) < fxp_max) {
		DRM_DEBUG_KMS("VBT defined backlight frequency out of range\n");
		return false;
	}

	for (pn = pn_max; pn >= pn_min; pn--) {
		f = clamp(DIV_ROUND_CLOSEST(fxp, 1 << pn), 1, 255);
		fxp_actual = f << pn;
		if (fxp_min <= fxp_actual && fxp_actual <= fxp_max)
			break;
	}

	if (drm_dp_dpcd_writeb(&intel_dp->aux,
			       DP_EDP_PWMGEN_BIT_COUNT, pn) < 0) {
		DRM_DEBUG_KMS("Failed to write aux pwmgen bit count\n");
		return false;
	}
	if (drm_dp_dpcd_writeb(&intel_dp->aux,
			       DP_EDP_BACKLIGHT_FREQ_SET, (u8) f) < 0) {
		DRM_DEBUG_KMS("Failed to write aux backlight freq\n");
		return false;
	}
	return true;
}