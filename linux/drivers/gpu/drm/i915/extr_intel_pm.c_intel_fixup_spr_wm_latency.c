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
typedef  int u16 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 

__attribute__((used)) static void intel_fixup_spr_wm_latency(struct drm_i915_private *dev_priv,
				       u16 wm[5])
{
	/* ILK sprite LP0 latency is 1300 ns */
	if (IS_GEN(dev_priv, 5))
		wm[0] = 13;
}