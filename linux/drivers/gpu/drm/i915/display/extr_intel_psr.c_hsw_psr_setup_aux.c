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
typedef  int u8 ;
typedef  int u32 ;
struct intel_dp {int (* get_aux_clock_divider ) (struct intel_dp*,int /*<<< orphan*/ ) ;int (* get_aux_send_ctl ) (struct intel_dp*,int,int) ;} ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  aux_msg ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
#define  DP_AUX_NATIVE_WRITE 130 
#define  DP_SET_POWER 129 
#define  DP_SET_POWER_D0 128 
 int /*<<< orphan*/  EDP_PSR_AUX_CTL ; 
 int EDP_PSR_AUX_CTL_BIT_CLOCK_2X_MASK ; 
 int EDP_PSR_AUX_CTL_MESSAGE_SIZE_MASK ; 
 int EDP_PSR_AUX_CTL_PRECHARGE_2US_MASK ; 
 int EDP_PSR_AUX_CTL_TIME_OUT_MASK ; 
 int /*<<< orphan*/  EDP_PSR_AUX_DATA (int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int intel_dp_pack_aux (int const*,int) ; 
 int stub1 (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int stub2 (struct intel_dp*,int,int) ; 

__attribute__((used)) static void hsw_psr_setup_aux(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	u32 aux_clock_divider, aux_ctl;
	int i;
	static const u8 aux_msg[] = {
		[0] = DP_AUX_NATIVE_WRITE << 4,
		[1] = DP_SET_POWER >> 8,
		[2] = DP_SET_POWER & 0xff,
		[3] = 1 - 1,
		[4] = DP_SET_POWER_D0,
	};
	u32 psr_aux_mask = EDP_PSR_AUX_CTL_TIME_OUT_MASK |
			   EDP_PSR_AUX_CTL_MESSAGE_SIZE_MASK |
			   EDP_PSR_AUX_CTL_PRECHARGE_2US_MASK |
			   EDP_PSR_AUX_CTL_BIT_CLOCK_2X_MASK;

	BUILD_BUG_ON(sizeof(aux_msg) > 20);
	for (i = 0; i < sizeof(aux_msg); i += 4)
		I915_WRITE(EDP_PSR_AUX_DATA(i >> 2),
			   intel_dp_pack_aux(&aux_msg[i], sizeof(aux_msg) - i));

	aux_clock_divider = intel_dp->get_aux_clock_divider(intel_dp, 0);

	/* Start with bits set for DDI_AUX_CTL register */
	aux_ctl = intel_dp->get_aux_send_ctl(intel_dp, sizeof(aux_msg),
					     aux_clock_divider);

	/* Select only valid bits for SRD_AUX_CTL */
	aux_ctl &= psr_aux_mask;
	I915_WRITE(EDP_PSR_AUX_CTL, aux_ctl);
}