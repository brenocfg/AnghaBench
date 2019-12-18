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
typedef  int u32 ;
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_LPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_NOP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDEIIR ; 
 int /*<<< orphan*/  SDEIMR ; 
 int SDE_AUX_MASK ; 
 int SDE_AUX_MASK_CPT ; 
 int SDE_GMBUS ; 
 int SDE_GMBUS_CPT ; 
 int SDE_POISON ; 
 int /*<<< orphan*/  gen3_assert_iir_is_zero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibx_hpd_detection_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spt_hpd_detection_setup (struct drm_i915_private*) ; 

__attribute__((used)) static void ibx_irq_postinstall(struct drm_i915_private *dev_priv)
{
	u32 mask;

	if (HAS_PCH_NOP(dev_priv))
		return;

	if (HAS_PCH_IBX(dev_priv))
		mask = SDE_GMBUS | SDE_AUX_MASK | SDE_POISON;
	else if (HAS_PCH_CPT(dev_priv) || HAS_PCH_LPT(dev_priv))
		mask = SDE_GMBUS_CPT | SDE_AUX_MASK_CPT;
	else
		mask = SDE_GMBUS_CPT;

	gen3_assert_iir_is_zero(&dev_priv->uncore, SDEIIR);
	I915_WRITE(SDEIMR, ~mask);

	if (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv) ||
	    HAS_PCH_LPT(dev_priv))
		ibx_hpd_detection_setup(dev_priv);
	else
		spt_hpd_detection_setup(dev_priv);
}