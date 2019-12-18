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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {scalar_t__ hpll_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlv_cck_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_cck_put (struct drm_i915_private*) ; 
 int vlv_get_cck_clock (struct drm_i915_private*,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vlv_get_hpll_vco (struct drm_i915_private*) ; 

int vlv_get_cck_clock_hpll(struct drm_i915_private *dev_priv,
			   const char *name, u32 reg)
{
	int hpll;

	vlv_cck_get(dev_priv);

	if (dev_priv->hpll_freq == 0)
		dev_priv->hpll_freq = vlv_get_hpll_vco(dev_priv);

	hpll = vlv_get_cck_clock(dev_priv, name, reg, dev_priv->hpll_freq);

	vlv_cck_put(dev_priv);

	return hpll;
}