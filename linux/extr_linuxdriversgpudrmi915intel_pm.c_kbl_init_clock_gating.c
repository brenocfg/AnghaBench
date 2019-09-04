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
 int GEN6_GAMUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  GEN6_UCGCTL1 ; 
 int GEN8_SDEUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  GEN8_UCGCTL6 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILK_DPFC_CHICKEN ; 
 int ILK_DPFC_NUKE_ON_ANY_MODIFICATION ; 
 scalar_t__ IS_KBL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBL_REVID_B0 ; 
 int /*<<< orphan*/  gen9_init_clock_gating (struct drm_i915_private*) ; 

__attribute__((used)) static void kbl_init_clock_gating(struct drm_i915_private *dev_priv)
{
	gen9_init_clock_gating(dev_priv);

	/* WaDisableSDEUnitClockGating:kbl */
	if (IS_KBL_REVID(dev_priv, 0, KBL_REVID_B0))
		I915_WRITE(GEN8_UCGCTL6, I915_READ(GEN8_UCGCTL6) |
			   GEN8_SDEUNIT_CLOCK_GATE_DISABLE);

	/* WaDisableGamClockGating:kbl */
	if (IS_KBL_REVID(dev_priv, 0, KBL_REVID_B0))
		I915_WRITE(GEN6_UCGCTL1, I915_READ(GEN6_UCGCTL1) |
			   GEN6_GAMUNIT_CLOCK_GATE_DISABLE);

	/* WaFbcNukeOnHostModify:kbl */
	I915_WRITE(ILK_DPFC_CHICKEN, I915_READ(ILK_DPFC_CHICKEN) |
		   ILK_DPFC_NUKE_ON_ANY_MODIFICATION);
}