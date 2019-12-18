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
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  icl_max_bw (struct drm_i915_private*,int,int) ; 
 unsigned int min3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int intel_max_data_rate(struct drm_i915_private *dev_priv,
					int num_planes)
{
	if (IS_GEN(dev_priv, 11))
		/*
		 * FIXME with SAGV disabled maybe we can assume
		 * point 1 will always be used? Seems to match
		 * the behaviour observed in the wild.
		 */
		return min3(icl_max_bw(dev_priv, num_planes, 0),
			    icl_max_bw(dev_priv, num_planes, 1),
			    icl_max_bw(dev_priv, num_planes, 2));
	else
		return UINT_MAX;
}