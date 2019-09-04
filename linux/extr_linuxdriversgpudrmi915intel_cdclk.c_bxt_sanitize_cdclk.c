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
struct TYPE_4__ {int vco; int cdclk; int bypass; } ;
struct TYPE_3__ {TYPE_2__ hw; } ;
struct drm_i915_private {TYPE_1__ cdclk; } ;

/* Variables and functions */
 int BXT_CDCLK_CD2X_DIV_SEL_MASK ; 
 int BXT_CDCLK_CD2X_PIPE_NONE ; 
 int BXT_CDCLK_SSA_PRECHARGE_ENABLE ; 
 int /*<<< orphan*/  CDCLK_CTL ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dump_cdclk_state (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  intel_update_cdclk (struct drm_i915_private*) ; 
 int skl_cdclk_decimal (int) ; 

__attribute__((used)) static void bxt_sanitize_cdclk(struct drm_i915_private *dev_priv)
{
	u32 cdctl, expected;

	intel_update_cdclk(dev_priv);
	intel_dump_cdclk_state(&dev_priv->cdclk.hw, "Current CDCLK");

	if (dev_priv->cdclk.hw.vco == 0 ||
	    dev_priv->cdclk.hw.cdclk == dev_priv->cdclk.hw.bypass)
		goto sanitize;

	/* DPLL okay; verify the cdclock
	 *
	 * Some BIOS versions leave an incorrect decimal frequency value and
	 * set reserved MBZ bits in CDCLK_CTL at least during exiting from S4,
	 * so sanitize this register.
	 */
	cdctl = I915_READ(CDCLK_CTL);
	/*
	 * Let's ignore the pipe field, since BIOS could have configured the
	 * dividers both synching to an active pipe, or asynchronously
	 * (PIPE_NONE).
	 */
	cdctl &= ~BXT_CDCLK_CD2X_PIPE_NONE;

	expected = (cdctl & BXT_CDCLK_CD2X_DIV_SEL_MASK) |
		skl_cdclk_decimal(dev_priv->cdclk.hw.cdclk);
	/*
	 * Disable SSA Precharge when CD clock frequency < 500 MHz,
	 * enable otherwise.
	 */
	if (dev_priv->cdclk.hw.cdclk >= 500000)
		expected |= BXT_CDCLK_SSA_PRECHARGE_ENABLE;

	if (cdctl == expected)
		/* All well; nothing to sanitize */
		return;

sanitize:
	DRM_DEBUG_KMS("Sanitizing cdclk programmed by pre-os\n");

	/* force cdclk programming */
	dev_priv->cdclk.hw.cdclk = 0;

	/* force full PLL disable + enable */
	dev_priv->cdclk.hw.vco = -1;
}