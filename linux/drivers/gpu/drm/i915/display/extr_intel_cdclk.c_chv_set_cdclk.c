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
typedef  int u32 ;
struct intel_cdclk_state {int cdclk; int voltage_level; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DSPFREQGUAR_MASK_CHV ; 
 int DSPFREQGUAR_SHIFT_CHV ; 
 int DSPFREQSTAT_MASK_CHV ; 
 int DSPFREQSTAT_SHIFT_CHV ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  POWER_DOMAIN_DISPLAY_CORE ; 
 int /*<<< orphan*/  PUNIT_REG_DSPSSPM ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_update_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_program_pfi_credits (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_punit_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_punit_put (struct drm_i915_private*) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_punit_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void chv_set_cdclk(struct drm_i915_private *dev_priv,
			  const struct intel_cdclk_state *cdclk_state,
			  enum pipe pipe)
{
	int cdclk = cdclk_state->cdclk;
	u32 val, cmd = cdclk_state->voltage_level;
	intel_wakeref_t wakeref;

	switch (cdclk) {
	case 333333:
	case 320000:
	case 266667:
	case 200000:
		break;
	default:
		MISSING_CASE(cdclk);
		return;
	}

	/* There are cases where we can end up here with power domains
	 * off and a CDCLK frequency other than the minimum, like when
	 * issuing a modeset without actually changing any display after
	 * a system suspend.  So grab the display core domain, which covers
	 * the HW blocks needed for the following programming.
	 */
	wakeref = intel_display_power_get(dev_priv, POWER_DOMAIN_DISPLAY_CORE);

	vlv_punit_get(dev_priv);
	val = vlv_punit_read(dev_priv, PUNIT_REG_DSPSSPM);
	val &= ~DSPFREQGUAR_MASK_CHV;
	val |= (cmd << DSPFREQGUAR_SHIFT_CHV);
	vlv_punit_write(dev_priv, PUNIT_REG_DSPSSPM, val);
	if (wait_for((vlv_punit_read(dev_priv, PUNIT_REG_DSPSSPM) &
		      DSPFREQSTAT_MASK_CHV) == (cmd << DSPFREQSTAT_SHIFT_CHV),
		     50)) {
		DRM_ERROR("timed out waiting for CDclk change\n");
	}

	vlv_punit_put(dev_priv);

	intel_update_cdclk(dev_priv);

	vlv_program_pfi_credits(dev_priv);

	intel_display_power_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);
}