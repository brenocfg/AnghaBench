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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int /*<<< orphan*/  type; TYPE_1__ base; } ;
struct intel_dp {int /*<<< orphan*/  link_rate; } ;
struct intel_digital_port {struct intel_encoder base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  icl_ddi_vswing_sequence (struct intel_encoder*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int intel_ddi_dp_level (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

u32 bxt_signal_levels(struct intel_dp *intel_dp)
{
	struct intel_digital_port *dport = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = to_i915(dport->base.base.dev);
	struct intel_encoder *encoder = &dport->base;
	int level = intel_ddi_dp_level(intel_dp);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_ddi_vswing_sequence(encoder, intel_dp->link_rate,
					level, encoder->type);
	else if (IS_CANNONLAKE(dev_priv))
		cnl_ddi_vswing_sequence(encoder, level, encoder->type);
	else
		bxt_ddi_vswing_sequence(encoder, level, encoder->type);

	return 0;
}