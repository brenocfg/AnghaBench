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
struct intel_crtc_state {int /*<<< orphan*/  nv12_planes; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 

__attribute__((used)) static bool needs_nv12_wa(struct drm_i915_private *dev_priv,
			  const struct intel_crtc_state *crtc_state)
{
	if (!crtc_state->nv12_planes)
		return false;

	if (IS_SKYLAKE(dev_priv) || IS_BROXTON(dev_priv))
		return false;

	if ((INTEL_GEN(dev_priv) == 9 && !IS_GEMINILAKE(dev_priv)) ||
	    IS_CANNONLAKE(dev_priv))
		return true;

	return false;
}