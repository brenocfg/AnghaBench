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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  D_COMP_BDW ; 
 int /*<<< orphan*/  GEN6_PCODE_WRITE_D_COMP ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ sandybridge_pcode_write (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsw_write_dcomp(struct drm_i915_private *dev_priv, u32 val)
{
	if (IS_HASWELL(dev_priv)) {
		if (sandybridge_pcode_write(dev_priv,
					    GEN6_PCODE_WRITE_D_COMP, val))
			DRM_DEBUG_KMS("Failed to write to D_COMP\n");
	} else {
		I915_WRITE(D_COMP_BDW, val);
		POSTING_READ(D_COMP_BDW);
	}
}