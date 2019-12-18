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
 int /*<<< orphan*/  BXT_REVID_B_LAST ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int IS_BXT_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IS_HSW_EARLY_SDV (struct drm_i915_private*) ; 
 int IS_KBL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IS_SKL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBL_REVID_A0 ; 
 int /*<<< orphan*/  LOCKDEP_STILL_OK ; 
 int /*<<< orphan*/  SKL_REVID_F0 ; 
 int /*<<< orphan*/  TAINT_MACHINE_CHECK ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_detect_preproduction_hw(struct drm_i915_private *dev_priv)
{
	bool pre = false;

	pre |= IS_HSW_EARLY_SDV(dev_priv);
	pre |= IS_SKL_REVID(dev_priv, 0, SKL_REVID_F0);
	pre |= IS_BXT_REVID(dev_priv, 0, BXT_REVID_B_LAST);
	pre |= IS_KBL_REVID(dev_priv, 0, KBL_REVID_A0);

	if (pre) {
		DRM_ERROR("This is a pre-production stepping. "
			  "It may not be fully functional.\n");
		add_taint(TAINT_MACHINE_CHECK, LOCKDEP_STILL_OK);
	}
}