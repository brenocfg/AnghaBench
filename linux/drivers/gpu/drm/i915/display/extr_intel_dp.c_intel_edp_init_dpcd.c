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
struct intel_dp {scalar_t__* dpcd; scalar_t__* edp_dpcd; int* sink_rates; int num_sink_rates; int use_rate_select; int /*<<< orphan*/  aux; int /*<<< orphan*/  desc; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  sink_rates ;
typedef  scalar_t__ __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct TYPE_6__ {TYPE_2__ base; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 size_t DP_DPCD_REV ; 
 scalar_t__ DP_EDP_14 ; 
 int /*<<< orphan*/  DP_EDP_DPCD_REV ; 
 int DP_MAX_SUPPORTED_RATES ; 
 int /*<<< orphan*/  DP_SUPPORTED_LINK_RATES ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,scalar_t__*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_3__* dp_to_dig_port (struct intel_dp*) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  drm_dp_is_branch (scalar_t__*) ; 
 int /*<<< orphan*/  drm_dp_read_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_get_dsc_sink_cap (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_read_dpcd (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_set_common_rates (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_set_sink_rates (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_init_dpcd (struct intel_dp*) ; 
 int le16_to_cpu (scalar_t__) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
intel_edp_init_dpcd(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv =
		to_i915(dp_to_dig_port(intel_dp)->base.base.dev);

	/* this function is meant to be called only once */
	WARN_ON(intel_dp->dpcd[DP_DPCD_REV] != 0);

	if (!intel_dp_read_dpcd(intel_dp))
		return false;

	drm_dp_read_desc(&intel_dp->aux, &intel_dp->desc,
			 drm_dp_is_branch(intel_dp->dpcd));

	/*
	 * Read the eDP display control registers.
	 *
	 * Do this independent of DP_DPCD_DISPLAY_CONTROL_CAPABLE bit in
	 * DP_EDP_CONFIGURATION_CAP, because some buggy displays do not have it
	 * set, but require eDP 1.4+ detection (e.g. for supported link rates
	 * method). The display control registers should read zero if they're
	 * not supported anyway.
	 */
	if (drm_dp_dpcd_read(&intel_dp->aux, DP_EDP_DPCD_REV,
			     intel_dp->edp_dpcd, sizeof(intel_dp->edp_dpcd)) ==
			     sizeof(intel_dp->edp_dpcd))
		DRM_DEBUG_KMS("eDP DPCD: %*ph\n", (int) sizeof(intel_dp->edp_dpcd),
			      intel_dp->edp_dpcd);

	/*
	 * This has to be called after intel_dp->edp_dpcd is filled, PSR checks
	 * for SET_POWER_CAPABLE bit in intel_dp->edp_dpcd[1]
	 */
	intel_psr_init_dpcd(intel_dp);

	/* Read the eDP 1.4+ supported link rates. */
	if (intel_dp->edp_dpcd[0] >= DP_EDP_14) {
		__le16 sink_rates[DP_MAX_SUPPORTED_RATES];
		int i;

		drm_dp_dpcd_read(&intel_dp->aux, DP_SUPPORTED_LINK_RATES,
				sink_rates, sizeof(sink_rates));

		for (i = 0; i < ARRAY_SIZE(sink_rates); i++) {
			int val = le16_to_cpu(sink_rates[i]);

			if (val == 0)
				break;

			/* Value read multiplied by 200kHz gives the per-lane
			 * link rate in kHz. The source rates are, however,
			 * stored in terms of LS_Clk kHz. The full conversion
			 * back to symbols is
			 * (val * 200kHz)*(8/10 ch. encoding)*(1/8 bit to Byte)
			 */
			intel_dp->sink_rates[i] = (val * 200) / 10;
		}
		intel_dp->num_sink_rates = i;
	}

	/*
	 * Use DP_LINK_RATE_SET if DP_SUPPORTED_LINK_RATES are available,
	 * default to DP_MAX_LINK_RATE and DP_LINK_BW_SET otherwise.
	 */
	if (intel_dp->num_sink_rates)
		intel_dp->use_rate_select = true;
	else
		intel_dp_set_sink_rates(intel_dp);

	intel_dp_set_common_rates(intel_dp);

	/* Read the eDP DSC DPCD registers */
	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		intel_dp_get_dsc_sink_cap(intel_dp);

	return true;
}