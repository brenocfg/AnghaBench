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
struct TYPE_4__ {TYPE_1__* ddi_port_info; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;
struct TYPE_3__ {int hdmi_level_shift; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int HDMI_LEVEL_SHIFT_UNKNOWN ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bxt_get_buf_trans_hdmi (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  cnl_get_buf_trans_hdmi (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  icl_get_combo_buf_trans (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  icl_mg_phy_ddi_translations ; 
 int /*<<< orphan*/  intel_ddi_get_buf_trans_hdmi (struct drm_i915_private*,int*) ; 
 scalar_t__ intel_phy_is_combo (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 

__attribute__((used)) static int intel_ddi_hdmi_level(struct drm_i915_private *dev_priv, enum port port)
{
	int n_entries, level, default_entry;
	enum phy phy = intel_port_to_phy(dev_priv, port);

	level = dev_priv->vbt.ddi_port_info[port].hdmi_level_shift;

	if (INTEL_GEN(dev_priv) >= 11) {
		if (intel_phy_is_combo(dev_priv, phy))
			icl_get_combo_buf_trans(dev_priv, INTEL_OUTPUT_HDMI,
						0, &n_entries);
		else
			n_entries = ARRAY_SIZE(icl_mg_phy_ddi_translations);
		default_entry = n_entries - 1;
	} else if (IS_CANNONLAKE(dev_priv)) {
		cnl_get_buf_trans_hdmi(dev_priv, &n_entries);
		default_entry = n_entries - 1;
	} else if (IS_GEN9_LP(dev_priv)) {
		bxt_get_buf_trans_hdmi(dev_priv, &n_entries);
		default_entry = n_entries - 1;
	} else if (IS_GEN9_BC(dev_priv)) {
		intel_ddi_get_buf_trans_hdmi(dev_priv, &n_entries);
		default_entry = 8;
	} else if (IS_BROADWELL(dev_priv)) {
		intel_ddi_get_buf_trans_hdmi(dev_priv, &n_entries);
		default_entry = 7;
	} else if (IS_HASWELL(dev_priv)) {
		intel_ddi_get_buf_trans_hdmi(dev_priv, &n_entries);
		default_entry = 6;
	} else {
		WARN(1, "ddi translation table missing\n");
		return 0;
	}

	/* Choose a good default if VBT is badly populated */
	if (level == HDMI_LEVEL_SHIFT_UNKNOWN || level >= n_entries)
		level = default_entry;

	if (WARN_ON_ONCE(n_entries == 0))
		return 0;
	if (WARN_ON_ONCE(level >= n_entries))
		level = n_entries - 1;

	return level;
}