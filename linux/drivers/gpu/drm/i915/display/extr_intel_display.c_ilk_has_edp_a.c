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
 int /*<<< orphan*/  DP_A ; 
 int DP_DETECTED ; 
 int /*<<< orphan*/  FUSE_STRAP ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int ILK_eDP_A_DISABLE ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  IS_MOBILE (struct drm_i915_private*) ; 

__attribute__((used)) static bool ilk_has_edp_a(struct drm_i915_private *dev_priv)
{
	if (!IS_MOBILE(dev_priv))
		return false;

	if ((I915_READ(DP_A) & DP_DETECTED) == 0)
		return false;

	if (IS_GEN(dev_priv, 5) && (I915_READ(FUSE_STRAP) & ILK_eDP_A_DISABLE))
		return false;

	return true;
}