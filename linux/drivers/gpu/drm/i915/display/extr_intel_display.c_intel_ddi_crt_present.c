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
struct TYPE_2__ {int /*<<< orphan*/  int_crt_support; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;

/* Variables and functions */
 int DDI_A_4_LANES ; 
 int /*<<< orphan*/  DDI_BUF_CTL (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_LPT_H (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BDW_ULT (struct drm_i915_private*) ; 
 scalar_t__ IS_HSW_ULT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PORT_A ; 
 int /*<<< orphan*/  SFUSE_STRAP ; 
 int SFUSE_STRAP_CRT_DISABLED ; 

__attribute__((used)) static bool intel_ddi_crt_present(struct drm_i915_private *dev_priv)
{
	if (INTEL_GEN(dev_priv) >= 9)
		return false;

	if (IS_HSW_ULT(dev_priv) || IS_BDW_ULT(dev_priv))
		return false;

	if (HAS_PCH_LPT_H(dev_priv) &&
	    I915_READ(SFUSE_STRAP) & SFUSE_STRAP_CRT_DISABLED)
		return false;

	/* DDI E can't be used if DDI A requires 4 lanes */
	if (I915_READ(DDI_BUF_CTL(PORT_A)) & DDI_A_4_LANES)
		return false;

	if (!dev_priv->vbt.int_crt_support)
		return false;

	return true;
}