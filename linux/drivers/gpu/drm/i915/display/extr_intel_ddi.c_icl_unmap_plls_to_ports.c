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
struct drm_i915_private {int /*<<< orphan*/  dpll_lock; } ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICL_DPCLKA_CFGCR0 ; 
 int /*<<< orphan*/  icl_dpclka_cfgcr0_clk_off (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_unmap_plls_to_ports(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum phy phy = intel_port_to_phy(dev_priv, encoder->port);
	u32 val;

	mutex_lock(&dev_priv->dpll_lock);

	val = I915_READ(ICL_DPCLKA_CFGCR0);
	val |= icl_dpclka_cfgcr0_clk_off(dev_priv, phy);
	I915_WRITE(ICL_DPCLKA_CFGCR0, val);

	mutex_unlock(&dev_priv->dpll_lock);
}