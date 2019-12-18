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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_CLK_SEL (int) ; 
 int DDI_CLK_SEL_NONE ; 
 int /*<<< orphan*/  DPCLKA_CFGCR0 ; 
 int DPCLKA_CFGCR0_DDI_CLK_OFF (int) ; 
 int /*<<< orphan*/  DPLL_CTRL2 ; 
 int DPLL_CTRL2_DDI_CLK_OFF (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 int PORT_C ; 
 int /*<<< orphan*/  PORT_CLK_SEL (int) ; 
 int PORT_CLK_SEL_NONE ; 
 int /*<<< orphan*/  intel_phy_is_combo (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_clk_disable(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	enum phy phy = intel_port_to_phy(dev_priv, port);

	if (INTEL_GEN(dev_priv) >= 11) {
		if (!intel_phy_is_combo(dev_priv, phy) ||
		    (IS_ELKHARTLAKE(dev_priv) && port >= PORT_C))
			I915_WRITE(DDI_CLK_SEL(port), DDI_CLK_SEL_NONE);
	} else if (IS_CANNONLAKE(dev_priv)) {
		I915_WRITE(DPCLKA_CFGCR0, I915_READ(DPCLKA_CFGCR0) |
			   DPCLKA_CFGCR0_DDI_CLK_OFF(port));
	} else if (IS_GEN9_BC(dev_priv)) {
		I915_WRITE(DPLL_CTRL2, I915_READ(DPLL_CTRL2) |
			   DPLL_CTRL2_DDI_CLK_OFF(port));
	} else if (INTEL_GEN(dev_priv) < 9) {
		I915_WRITE(PORT_CLK_SEL(port), PORT_CLK_SEL_NONE);
	}
}