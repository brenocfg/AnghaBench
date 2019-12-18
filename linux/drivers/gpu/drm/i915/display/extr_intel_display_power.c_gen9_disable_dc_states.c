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
struct intel_cdclk_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_cdclk ) (struct drm_i915_private*,struct intel_cdclk_state*) ;} ;
struct drm_i915_private {TYPE_2__ cdclk; TYPE_1__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_DISABLE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxt_verify_ddi_phy_power_wells (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_assert_dbuf_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_set_dc_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_cdclk_needs_modeset (int /*<<< orphan*/ *,struct intel_cdclk_state*) ; 
 int /*<<< orphan*/  intel_combo_phy_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,struct intel_cdclk_state*) ; 

__attribute__((used)) static void gen9_disable_dc_states(struct drm_i915_private *dev_priv)
{
	struct intel_cdclk_state cdclk_state = {};

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	dev_priv->display.get_cdclk(dev_priv, &cdclk_state);
	/* Can't read out voltage_level so can't use intel_cdclk_changed() */
	WARN_ON(intel_cdclk_needs_modeset(&dev_priv->cdclk.hw, &cdclk_state));

	gen9_assert_dbuf_enabled(dev_priv);

	if (IS_GEN9_LP(dev_priv))
		bxt_verify_ddi_phy_power_wells(dev_priv);

	if (INTEL_GEN(dev_priv) >= 11)
		/*
		 * DMC retains HW context only for port A, the other combo
		 * PHY's HW context for port B is lost after DC transitions,
		 * so we need to restore it manually.
		 */
		intel_combo_phy_init(dev_priv);
}