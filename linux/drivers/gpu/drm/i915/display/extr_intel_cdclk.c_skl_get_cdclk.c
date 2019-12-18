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
struct intel_cdclk_state {int cdclk; int bypass; int ref; int vco; int /*<<< orphan*/  voltage_level; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDCLK_CTL ; 
#define  CDCLK_FREQ_337_308 131 
#define  CDCLK_FREQ_450_432 130 
#define  CDCLK_FREQ_540 129 
#define  CDCLK_FREQ_675_617 128 
 int CDCLK_FREQ_SEL_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  skl_calc_voltage_level (int) ; 
 int /*<<< orphan*/  skl_dpll0_update (struct drm_i915_private*,struct intel_cdclk_state*) ; 

__attribute__((used)) static void skl_get_cdclk(struct drm_i915_private *dev_priv,
			  struct intel_cdclk_state *cdclk_state)
{
	u32 cdctl;

	skl_dpll0_update(dev_priv, cdclk_state);

	cdclk_state->cdclk = cdclk_state->bypass = cdclk_state->ref;

	if (cdclk_state->vco == 0)
		goto out;

	cdctl = I915_READ(CDCLK_CTL);

	if (cdclk_state->vco == 8640000) {
		switch (cdctl & CDCLK_FREQ_SEL_MASK) {
		case CDCLK_FREQ_450_432:
			cdclk_state->cdclk = 432000;
			break;
		case CDCLK_FREQ_337_308:
			cdclk_state->cdclk = 308571;
			break;
		case CDCLK_FREQ_540:
			cdclk_state->cdclk = 540000;
			break;
		case CDCLK_FREQ_675_617:
			cdclk_state->cdclk = 617143;
			break;
		default:
			MISSING_CASE(cdctl & CDCLK_FREQ_SEL_MASK);
			break;
		}
	} else {
		switch (cdctl & CDCLK_FREQ_SEL_MASK) {
		case CDCLK_FREQ_450_432:
			cdclk_state->cdclk = 450000;
			break;
		case CDCLK_FREQ_337_308:
			cdclk_state->cdclk = 337500;
			break;
		case CDCLK_FREQ_540:
			cdclk_state->cdclk = 540000;
			break;
		case CDCLK_FREQ_675_617:
			cdclk_state->cdclk = 675000;
			break;
		default:
			MISSING_CASE(cdctl & CDCLK_FREQ_SEL_MASK);
			break;
		}
	}

 out:
	/*
	 * Can't read this out :( Let's assume it's
	 * at least what the CDCLK frequency requires.
	 */
	cdclk_state->voltage_level =
		skl_calc_voltage_level(cdclk_state->cdclk);
}