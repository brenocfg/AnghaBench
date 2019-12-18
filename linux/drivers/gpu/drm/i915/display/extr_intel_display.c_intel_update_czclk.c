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
struct drm_i915_private {int /*<<< orphan*/  czclk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_CZ_CLOCK_CONTROL ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_get_cck_clock_hpll (struct drm_i915_private*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_update_czclk(struct drm_i915_private *dev_priv)
{
	if (!(IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)))
		return;

	dev_priv->czclk_freq = vlv_get_cck_clock_hpll(dev_priv, "czclk",
						      CCK_CZ_CLOCK_CONTROL);

	DRM_DEBUG_DRIVER("CZ clock rate: %d kHz\n", dev_priv->czclk_freq);
}