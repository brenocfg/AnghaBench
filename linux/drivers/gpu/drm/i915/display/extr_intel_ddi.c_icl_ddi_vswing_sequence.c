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
struct intel_encoder {int /*<<< orphan*/  port; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum phy { ____Placeholder_phy } phy ;
typedef  enum intel_output_type { ____Placeholder_intel_output_type } intel_output_type ;

/* Variables and functions */
 int /*<<< orphan*/  icl_combo_phy_ddi_vswing_sequence (struct intel_encoder*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  icl_mg_phy_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_phy_is_combo (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_ddi_vswing_sequence(struct intel_encoder *encoder,
				    int link_clock,
				    u32 level,
				    enum intel_output_type type)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum phy phy = intel_port_to_phy(dev_priv, encoder->port);

	if (intel_phy_is_combo(dev_priv, phy))
		icl_combo_phy_ddi_vswing_sequence(encoder, level, type);
	else
		icl_mg_phy_ddi_vswing_sequence(encoder, link_clock, level);
}