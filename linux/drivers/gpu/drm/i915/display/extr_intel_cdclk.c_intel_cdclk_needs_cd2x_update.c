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
struct intel_cdclk_state {scalar_t__ cdclk; scalar_t__ vco; scalar_t__ ref; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEN9_LP (struct drm_i915_private*) ; 

bool intel_cdclk_needs_cd2x_update(struct drm_i915_private *dev_priv,
				   const struct intel_cdclk_state *a,
				   const struct intel_cdclk_state *b)
{
	/* Older hw doesn't have the capability */
	if (INTEL_GEN(dev_priv) < 10 && !IS_GEN9_LP(dev_priv))
		return false;

	return a->cdclk != b->cdclk &&
		a->vco == b->vco &&
		a->ref == b->ref;
}