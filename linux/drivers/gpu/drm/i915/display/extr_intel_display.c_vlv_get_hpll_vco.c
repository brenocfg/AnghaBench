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

/* Variables and functions */
 int CCK_FUSE_HPLL_FREQ_MASK ; 
 int /*<<< orphan*/  CCK_FUSE_REG ; 
 int vlv_cck_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

int vlv_get_hpll_vco(struct drm_i915_private *dev_priv)
{
	int hpll_freq, vco_freq[] = { 800, 1600, 2000, 2400 };

	/* Obtain SKU information */
	hpll_freq = vlv_cck_read(dev_priv, CCK_FUSE_REG) &
		CCK_FUSE_HPLL_FREQ_MASK;

	return vco_freq[hpll_freq] * 1000;
}