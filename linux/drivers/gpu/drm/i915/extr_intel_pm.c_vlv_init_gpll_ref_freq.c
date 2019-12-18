#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gpll_ref_freq; } ;
struct TYPE_4__ {TYPE_1__ rps; } ;
struct drm_i915_private {TYPE_2__ gt_pm; int /*<<< orphan*/  czclk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_GPLL_CLOCK_CONTROL ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_get_cck_clock (struct drm_i915_private*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlv_init_gpll_ref_freq(struct drm_i915_private *dev_priv)
{
	dev_priv->gt_pm.rps.gpll_ref_freq =
		vlv_get_cck_clock(dev_priv, "GPLL ref",
				  CCK_GPLL_CLOCK_CONTROL,
				  dev_priv->czclk_freq);

	DRM_DEBUG_DRIVER("GPLL reference freq: %d kHz\n",
			 dev_priv->gt_pm.rps.gpll_ref_freq);
}