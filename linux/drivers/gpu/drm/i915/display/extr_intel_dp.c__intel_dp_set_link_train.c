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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int /*<<< orphan*/  dpcd; } ;
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int DP_LINK_SCRAMBLING_DISABLE ; 
 int /*<<< orphan*/  DP_LINK_TRAIN_MASK ; 
 int /*<<< orphan*/  DP_LINK_TRAIN_MASK_CPT ; 
 int /*<<< orphan*/  DP_LINK_TRAIN_OFF ; 
 int /*<<< orphan*/  DP_LINK_TRAIN_OFF_CPT ; 
 int /*<<< orphan*/  DP_LINK_TRAIN_PAT_1 ; 
 int /*<<< orphan*/  DP_LINK_TRAIN_PAT_1_CPT ; 
 int /*<<< orphan*/  DP_LINK_TRAIN_PAT_2 ; 
 int /*<<< orphan*/  DP_LINK_TRAIN_PAT_2_CPT ; 
 int /*<<< orphan*/  DP_TP_CTL (int) ; 
 int /*<<< orphan*/  DP_TP_CTL_LINK_TRAIN_MASK ; 
 int /*<<< orphan*/  DP_TP_CTL_LINK_TRAIN_NORMAL ; 
 int /*<<< orphan*/  DP_TP_CTL_LINK_TRAIN_PAT1 ; 
 int /*<<< orphan*/  DP_TP_CTL_LINK_TRAIN_PAT2 ; 
 int /*<<< orphan*/  DP_TP_CTL_LINK_TRAIN_PAT3 ; 
 int /*<<< orphan*/  DP_TP_CTL_LINK_TRAIN_PAT4 ; 
 int /*<<< orphan*/  DP_TP_CTL_SCRAMBLE_DISABLE ; 
#define  DP_TRAINING_PATTERN_1 132 
#define  DP_TRAINING_PATTERN_2 131 
#define  DP_TRAINING_PATTERN_3 130 
#define  DP_TRAINING_PATTERN_4 129 
#define  DP_TRAINING_PATTERN_DISABLE 128 
 int DP_TRAINING_PATTERN_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int PORT_A ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int drm_dp_training_pattern_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_intel_dp_set_link_train(struct intel_dp *intel_dp,
			 u32 *DP,
			 u8 dp_train_pat)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	enum port port = intel_dig_port->base.port;
	u8 train_pat_mask = drm_dp_training_pattern_mask(intel_dp->dpcd);

	if (dp_train_pat & train_pat_mask)
		DRM_DEBUG_KMS("Using DP training pattern TPS%d\n",
			      dp_train_pat & train_pat_mask);

	if (HAS_DDI(dev_priv)) {
		u32 temp = I915_READ(DP_TP_CTL(port));

		if (dp_train_pat & DP_LINK_SCRAMBLING_DISABLE)
			temp |= DP_TP_CTL_SCRAMBLE_DISABLE;
		else
			temp &= ~DP_TP_CTL_SCRAMBLE_DISABLE;

		temp &= ~DP_TP_CTL_LINK_TRAIN_MASK;
		switch (dp_train_pat & train_pat_mask) {
		case DP_TRAINING_PATTERN_DISABLE:
			temp |= DP_TP_CTL_LINK_TRAIN_NORMAL;

			break;
		case DP_TRAINING_PATTERN_1:
			temp |= DP_TP_CTL_LINK_TRAIN_PAT1;
			break;
		case DP_TRAINING_PATTERN_2:
			temp |= DP_TP_CTL_LINK_TRAIN_PAT2;
			break;
		case DP_TRAINING_PATTERN_3:
			temp |= DP_TP_CTL_LINK_TRAIN_PAT3;
			break;
		case DP_TRAINING_PATTERN_4:
			temp |= DP_TP_CTL_LINK_TRAIN_PAT4;
			break;
		}
		I915_WRITE(DP_TP_CTL(port), temp);

	} else if ((IS_IVYBRIDGE(dev_priv) && port == PORT_A) ||
		   (HAS_PCH_CPT(dev_priv) && port != PORT_A)) {
		*DP &= ~DP_LINK_TRAIN_MASK_CPT;

		switch (dp_train_pat & DP_TRAINING_PATTERN_MASK) {
		case DP_TRAINING_PATTERN_DISABLE:
			*DP |= DP_LINK_TRAIN_OFF_CPT;
			break;
		case DP_TRAINING_PATTERN_1:
			*DP |= DP_LINK_TRAIN_PAT_1_CPT;
			break;
		case DP_TRAINING_PATTERN_2:
			*DP |= DP_LINK_TRAIN_PAT_2_CPT;
			break;
		case DP_TRAINING_PATTERN_3:
			DRM_DEBUG_KMS("TPS3 not supported, using TPS2 instead\n");
			*DP |= DP_LINK_TRAIN_PAT_2_CPT;
			break;
		}

	} else {
		*DP &= ~DP_LINK_TRAIN_MASK;

		switch (dp_train_pat & DP_TRAINING_PATTERN_MASK) {
		case DP_TRAINING_PATTERN_DISABLE:
			*DP |= DP_LINK_TRAIN_OFF;
			break;
		case DP_TRAINING_PATTERN_1:
			*DP |= DP_LINK_TRAIN_PAT_1;
			break;
		case DP_TRAINING_PATTERN_2:
			*DP |= DP_LINK_TRAIN_PAT_2;
			break;
		case DP_TRAINING_PATTERN_3:
			DRM_DEBUG_KMS("TPS3 not supported, using TPS2 instead\n");
			*DP |= DP_LINK_TRAIN_PAT_2;
			break;
		}
	}
}