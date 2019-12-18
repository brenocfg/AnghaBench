#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct intel_dp {int* train_set; int DP; int /*<<< orphan*/  output_reg; } ;
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int DDI_BUF_EMP_MASK ; 
 int DP_PRE_EMPHASIS_MASK ; 
 int DP_TRAIN_PRE_EMPHASIS_MASK ; 
 int DP_TRAIN_PRE_EMPHASIS_SHIFT ; 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int DP_VOLTAGE_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int EDP_LINK_TRAIN_VOL_EMP_MASK_IVB ; 
 int EDP_LINK_TRAIN_VOL_EMP_MASK_SNB ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int PORT_A ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int bxt_signal_levels (struct intel_dp*) ; 
 int chv_signal_levels (struct intel_dp*) ; 
 int ddi_signal_levels (struct intel_dp*) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int g4x_signal_levels (int) ; 
 int ivb_cpu_edp_signal_levels (int) ; 
 int snb_cpu_edp_signal_levels (int) ; 
 int vlv_signal_levels (struct intel_dp*) ; 

void
intel_dp_set_signal_levels(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	enum port port = intel_dig_port->base.port;
	u32 signal_levels, mask = 0;
	u8 train_set = intel_dp->train_set[0];

	if (IS_GEN9_LP(dev_priv) || INTEL_GEN(dev_priv) >= 10) {
		signal_levels = bxt_signal_levels(intel_dp);
	} else if (HAS_DDI(dev_priv)) {
		signal_levels = ddi_signal_levels(intel_dp);
		mask = DDI_BUF_EMP_MASK;
	} else if (IS_CHERRYVIEW(dev_priv)) {
		signal_levels = chv_signal_levels(intel_dp);
	} else if (IS_VALLEYVIEW(dev_priv)) {
		signal_levels = vlv_signal_levels(intel_dp);
	} else if (IS_IVYBRIDGE(dev_priv) && port == PORT_A) {
		signal_levels = ivb_cpu_edp_signal_levels(train_set);
		mask = EDP_LINK_TRAIN_VOL_EMP_MASK_IVB;
	} else if (IS_GEN(dev_priv, 6) && port == PORT_A) {
		signal_levels = snb_cpu_edp_signal_levels(train_set);
		mask = EDP_LINK_TRAIN_VOL_EMP_MASK_SNB;
	} else {
		signal_levels = g4x_signal_levels(train_set);
		mask = DP_VOLTAGE_MASK | DP_PRE_EMPHASIS_MASK;
	}

	if (mask)
		DRM_DEBUG_KMS("Using signal levels %08x\n", signal_levels);

	DRM_DEBUG_KMS("Using vswing level %d\n",
		train_set & DP_TRAIN_VOLTAGE_SWING_MASK);
	DRM_DEBUG_KMS("Using pre-emphasis level %d\n",
		(train_set & DP_TRAIN_PRE_EMPHASIS_MASK) >>
			DP_TRAIN_PRE_EMPHASIS_SHIFT);

	intel_dp->DP = (intel_dp->DP & ~mask) | signal_levels;

	I915_WRITE(intel_dp->output_reg, intel_dp->DP);
	POSTING_READ(intel_dp->output_reg);
}