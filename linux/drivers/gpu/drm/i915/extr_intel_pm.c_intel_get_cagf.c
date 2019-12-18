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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int GEN6_CAGF_MASK ; 
 int GEN6_CAGF_SHIFT ; 
 int GEN9_CAGF_MASK ; 
 int GEN9_CAGF_SHIFT ; 
 int HSW_CAGF_MASK ; 
 int HSW_CAGF_SHIFT ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 

u32 intel_get_cagf(struct drm_i915_private *dev_priv, u32 rpstat)
{
	u32 cagf;

	if (INTEL_GEN(dev_priv) >= 9)
		cagf = (rpstat & GEN9_CAGF_MASK) >> GEN9_CAGF_SHIFT;
	else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		cagf = (rpstat & HSW_CAGF_MASK) >> HSW_CAGF_SHIFT;
	else
		cagf = (rpstat & GEN6_CAGF_MASK) >> GEN6_CAGF_SHIFT;

	return  cagf;
}