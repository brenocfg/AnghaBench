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
struct TYPE_4__ {int vco; scalar_t__ cdclk; scalar_t__ bypass; } ;
struct TYPE_3__ {TYPE_2__ hw; } ;
struct drm_i915_private {TYPE_1__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDCLK_CTL ; 
 int CDCLK_FREQ_SEL_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWF_ILK (int) ; 
 int /*<<< orphan*/  intel_dump_cdclk_state (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  intel_update_cdclk (struct drm_i915_private*) ; 
 int skl_cdclk_decimal (scalar_t__) ; 

__attribute__((used)) static void skl_sanitize_cdclk(struct drm_i915_private *dev_priv)
{
	u32 cdctl, expected;

	/*
	 * check if the pre-os initialized the display
	 * There is SWF18 scratchpad register defined which is set by the
	 * pre-os which can be used by the OS drivers to check the status
	 */
	if ((I915_READ(SWF_ILK(0x18)) & 0x00FFFFFF) == 0)
		goto sanitize;

	intel_update_cdclk(dev_priv);
	intel_dump_cdclk_state(&dev_priv->cdclk.hw, "Current CDCLK");

	/* Is PLL enabled and locked ? */
	if (dev_priv->cdclk.hw.vco == 0 ||
	    dev_priv->cdclk.hw.cdclk == dev_priv->cdclk.hw.bypass)
		goto sanitize;

	/* DPLL okay; verify the cdclock
	 *
	 * Noticed in some instances that the freq selection is correct but
	 * decimal part is programmed wrong from BIOS where pre-os does not
	 * enable display. Verify the same as well.
	 */
	cdctl = I915_READ(CDCLK_CTL);
	expected = (cdctl & CDCLK_FREQ_SEL_MASK) |
		skl_cdclk_decimal(dev_priv->cdclk.hw.cdclk);
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