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
struct intel_dp {int dummy; } ;
struct intel_digital_port {int aux_ch; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum aux_ch { ____Placeholder_aux_ch } aux_ch ;

/* Variables and functions */
#define  AUX_CH_B 130 
#define  AUX_CH_C 129 
#define  AUX_CH_D 128 
 int /*<<< orphan*/  DP_AUX_CH_DATA (int const,int) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 

__attribute__((used)) static i915_reg_t g4x_aux_data_reg(struct intel_dp *intel_dp, int index)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	enum aux_ch aux_ch = dig_port->aux_ch;

	switch (aux_ch) {
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
		return DP_AUX_CH_DATA(aux_ch, index);
	default:
		MISSING_CASE(aux_ch);
		return DP_AUX_CH_DATA(AUX_CH_B, index);
	}
}