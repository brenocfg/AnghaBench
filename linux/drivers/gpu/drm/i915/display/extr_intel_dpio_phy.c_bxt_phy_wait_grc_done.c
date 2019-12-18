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
struct drm_i915_private {int dummy; } ;
typedef  enum dpio_phy { ____Placeholder_dpio_phy } dpio_phy ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_PORT_REF_DW3 (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  GRC_DONE ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bxt_phy_wait_grc_done(struct drm_i915_private *dev_priv,
				  enum dpio_phy phy)
{
	if (intel_de_wait_for_set(dev_priv, BXT_PORT_REF_DW3(phy),
				  GRC_DONE, 10))
		DRM_ERROR("timeout waiting for PHY%d GRC\n", phy);
}