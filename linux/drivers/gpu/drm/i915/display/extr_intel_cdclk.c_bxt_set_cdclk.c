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
typedef  int u32 ;
struct intel_cdclk_state {int cdclk; int vco; int voltage_level; } ;
struct TYPE_3__ {int bypass; int vco; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int BXT_CDCLK_CD2X_DIV_SEL_1 ; 
 int BXT_CDCLK_CD2X_DIV_SEL_1_5 ; 
 int BXT_CDCLK_CD2X_DIV_SEL_2 ; 
 int BXT_CDCLK_CD2X_DIV_SEL_4 ; 
 int BXT_CDCLK_CD2X_PIPE (int) ; 
 int BXT_CDCLK_CD2X_PIPE_NONE ; 
 int BXT_CDCLK_SSA_PRECHARGE_ENABLE ; 
 int /*<<< orphan*/  CDCLK_CTL ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  HSW_PCODE_DE_WRITE_FREQ_REQ ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INVALID_PIPE ; 
 int /*<<< orphan*/  IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bxt_de_pll_disable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_de_pll_enable (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_update_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int) ; 
 int sandybridge_pcode_write_timeout (struct drm_i915_private*,int /*<<< orphan*/ ,int,int,int) ; 
 int skl_cdclk_decimal (int) ; 

__attribute__((used)) static void bxt_set_cdclk(struct drm_i915_private *dev_priv,
			  const struct intel_cdclk_state *cdclk_state,
			  enum pipe pipe)
{
	int cdclk = cdclk_state->cdclk;
	int vco = cdclk_state->vco;
	u32 val, divider;
	int ret;

	/* cdclk = vco / 2 / div{1,1.5,2,4} */
	switch (DIV_ROUND_CLOSEST(vco, cdclk)) {
	default:
		WARN_ON(cdclk != dev_priv->cdclk.hw.bypass);
		WARN_ON(vco != 0);
		/* fall through */
	case 2:
		divider = BXT_CDCLK_CD2X_DIV_SEL_1;
		break;
	case 3:
		WARN(IS_GEMINILAKE(dev_priv), "Unsupported divider\n");
		divider = BXT_CDCLK_CD2X_DIV_SEL_1_5;
		break;
	case 4:
		divider = BXT_CDCLK_CD2X_DIV_SEL_2;
		break;
	case 8:
		divider = BXT_CDCLK_CD2X_DIV_SEL_4;
		break;
	}

	/*
	 * Inform power controller of upcoming frequency change. BSpec
	 * requires us to wait up to 150usec, but that leads to timeouts;
	 * the 2ms used here is based on experiment.
	 */
	ret = sandybridge_pcode_write_timeout(dev_priv,
					      HSW_PCODE_DE_WRITE_FREQ_REQ,
					      0x80000000, 150, 2);
	if (ret) {
		DRM_ERROR("PCode CDCLK freq change notify failed (err %d, freq %d)\n",
			  ret, cdclk);
		return;
	}

	if (dev_priv->cdclk.hw.vco != 0 &&
	    dev_priv->cdclk.hw.vco != vco)
		bxt_de_pll_disable(dev_priv);

	if (dev_priv->cdclk.hw.vco != vco)
		bxt_de_pll_enable(dev_priv, vco);

	val = divider | skl_cdclk_decimal(cdclk);
	if (pipe == INVALID_PIPE)
		val |= BXT_CDCLK_CD2X_PIPE_NONE;
	else
		val |= BXT_CDCLK_CD2X_PIPE(pipe);
	/*
	 * Disable SSA Precharge when CD clock frequency < 500 MHz,
	 * enable otherwise.
	 */
	if (cdclk >= 500000)
		val |= BXT_CDCLK_SSA_PRECHARGE_ENABLE;
	I915_WRITE(CDCLK_CTL, val);

	if (pipe != INVALID_PIPE)
		intel_wait_for_vblank(dev_priv, pipe);

	/*
	 * The timeout isn't specified, the 2ms used here is based on
	 * experiment.
	 * FIXME: Waiting for the request completion could be delayed until
	 * the next PCODE request based on BSpec.
	 */
	ret = sandybridge_pcode_write_timeout(dev_priv,
					      HSW_PCODE_DE_WRITE_FREQ_REQ,
					      cdclk_state->voltage_level, 150, 2);
	if (ret) {
		DRM_ERROR("PCode CDCLK freq set failed, (err %d, freq %d)\n",
			  ret, cdclk);
		return;
	}

	intel_update_cdclk(dev_priv);
}