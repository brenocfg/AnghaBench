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
 int /*<<< orphan*/  icl_get_bw_info (struct drm_i915_private*) ; 

void intel_bw_init_hw(struct drm_i915_private *dev_priv)
{
	if (IS_GEN(dev_priv, 11))
		icl_get_bw_info(dev_priv);
}