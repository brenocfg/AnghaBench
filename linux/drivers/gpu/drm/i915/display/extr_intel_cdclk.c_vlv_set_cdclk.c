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
struct drm_i915_private {int hpll_freq; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUNIT_REG_BISOC ; 
 int /*<<< orphan*/  CCK_DISPLAY_CLOCK_CONTROL ; 
 int CCK_FREQUENCY_STATUS ; 
 int CCK_FREQUENCY_STATUS_SHIFT ; 
 int CCK_FREQUENCY_VALUES ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DSPFREQGUAR_MASK ; 
 int DSPFREQGUAR_SHIFT ; 
 int DSPFREQSTAT_MASK ; 
 int DSPFREQSTAT_SHIFT ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  POWER_DOMAIN_DISPLAY_CORE ; 
 int /*<<< orphan*/  PUNIT_REG_DSPSSPM ; 
 int /*<<< orphan*/  VLV_IOSF_SB_BUNIT ; 
 int /*<<< orphan*/  VLV_IOSF_SB_CCK ; 
 int /*<<< orphan*/  VLV_IOSF_SB_PUNIT ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_update_cdclk (struct drm_i915_private*) ; 
 int vlv_bunit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_bunit_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int vlv_cck_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_cck_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlv_iosf_sb_get (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_iosf_sb_put (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_program_pfi_credits (struct drm_i915_private*) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_punit_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void vlv_set_cdclk(struct drm_i915_private *dev_priv,
			  const struct intel_cdclk_state *cdclk_state,
			  enum pipe pipe)
{
	int cdclk = cdclk_state->cdclk;
	u32 val, cmd = cdclk_state->voltage_level;
	intel_wakeref_t wakeref;

	switch (cdclk) {
	case 400000:
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

	vlv_iosf_sb_get(dev_priv,
			BIT(VLV_IOSF_SB_CCK) |
			BIT(VLV_IOSF_SB_BUNIT) |
			BIT(VLV_IOSF_SB_PUNIT));

	val = vlv_punit_read(dev_priv, PUNIT_REG_DSPSSPM);
	val &= ~DSPFREQGUAR_MASK;
	val |= (cmd << DSPFREQGUAR_SHIFT);
	vlv_punit_write(dev_priv, PUNIT_REG_DSPSSPM, val);
	if (wait_for((vlv_punit_read(dev_priv, PUNIT_REG_DSPSSPM) &
		      DSPFREQSTAT_MASK) == (cmd << DSPFREQSTAT_SHIFT),
		     50)) {
		DRM_ERROR("timed out waiting for CDclk change\n");
	}

	if (cdclk == 400000) {
		u32 divider;

		divider = DIV_ROUND_CLOSEST(dev_priv->hpll_freq << 1,
					    cdclk) - 1;

		/* adjust cdclk divider */
		val = vlv_cck_read(dev_priv, CCK_DISPLAY_CLOCK_CONTROL);
		val &= ~CCK_FREQUENCY_VALUES;
		val |= divider;
		vlv_cck_write(dev_priv, CCK_DISPLAY_CLOCK_CONTROL, val);

		if (wait_for((vlv_cck_read(dev_priv, CCK_DISPLAY_CLOCK_CONTROL) &
			      CCK_FREQUENCY_STATUS) == (divider << CCK_FREQUENCY_STATUS_SHIFT),
			     50))
			DRM_ERROR("timed out waiting for CDclk change\n");
	}

	/* adjust self-refresh exit latency value */
	val = vlv_bunit_read(dev_priv, BUNIT_REG_BISOC);
	val &= ~0x7f;

	/*
	 * For high bandwidth configs, we set a higher latency in the bunit
	 * so that the core display fetch happens in time to avoid underruns.
	 */
	if (cdclk == 400000)
		val |= 4500 / 250; /* 4.5 usec */
	else
		val |= 3000 / 250; /* 3.0 usec */
	vlv_bunit_write(dev_priv, BUNIT_REG_BISOC, val);

	vlv_iosf_sb_put(dev_priv,
			BIT(VLV_IOSF_SB_CCK) |
			BIT(VLV_IOSF_SB_BUNIT) |
			BIT(VLV_IOSF_SB_PUNIT));

	intel_update_cdclk(dev_priv);

	vlv_program_pfi_credits(dev_priv);

	intel_display_power_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);
}