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
struct TYPE_2__ {unsigned int* pri_latency; } ;
struct drm_i915_private {TYPE_1__ wm; } ;

/* Variables and functions */
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 

__attribute__((used)) static unsigned int ilk_wm_lp_latency(struct drm_i915_private *dev_priv,
				      int level)
{
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		return 2 * level;
	else
		return dev_priv->wm.pri_latency[level];
}