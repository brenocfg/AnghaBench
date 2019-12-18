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
 int /*<<< orphan*/  CNL_REVID_A0 ; 
 int /*<<< orphan*/  CNL_REVID_B0 ; 
 int /*<<< orphan*/  DISP_ARB_CTL ; 
 int DISP_FBC_MEMORY_WAKE ; 
 int /*<<< orphan*/  GEN8_CHICKEN_DCPR_1 ; 
 int GWUNIT_CLKGATE_DIS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_CNL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MASK_WAKEMEM ; 
 int RCCUNIT_CLKGATE_DIS ; 
 int SARBUNIT_CLKGATE_DIS ; 
 int /*<<< orphan*/  SLICE_UNIT_LEVEL_CLKGATE ; 
 int /*<<< orphan*/  SUBSLICE_UNIT_LEVEL_CLKGATE ; 
 int /*<<< orphan*/  UNSLICE_UNIT_LEVEL_CLKGATE ; 
 int VFUNIT_CLKGATE_DIS ; 
 int /*<<< orphan*/  _3D_CHICKEN3 ; 
 int /*<<< orphan*/  _3D_CHICKEN3_AA_LINE_QUALITY_FIX_ENABLE ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnp_init_clock_gating (struct drm_i915_private*) ; 

__attribute__((used)) static void cnl_init_clock_gating(struct drm_i915_private *dev_priv)
{
	u32 val;
	cnp_init_clock_gating(dev_priv);

	/* This is not an Wa. Enable for better image quality */
	I915_WRITE(_3D_CHICKEN3,
		   _MASKED_BIT_ENABLE(_3D_CHICKEN3_AA_LINE_QUALITY_FIX_ENABLE));

	/* WaEnableChickenDCPR:cnl */
	I915_WRITE(GEN8_CHICKEN_DCPR_1,
		   I915_READ(GEN8_CHICKEN_DCPR_1) | MASK_WAKEMEM);

	/* WaFbcWakeMemOn:cnl */
	I915_WRITE(DISP_ARB_CTL, I915_READ(DISP_ARB_CTL) |
		   DISP_FBC_MEMORY_WAKE);

	val = I915_READ(SLICE_UNIT_LEVEL_CLKGATE);
	/* ReadHitWriteOnlyDisable:cnl */
	val |= RCCUNIT_CLKGATE_DIS;
	/* WaSarbUnitClockGatingDisable:cnl (pre-prod) */
	if (IS_CNL_REVID(dev_priv, CNL_REVID_A0, CNL_REVID_B0))
		val |= SARBUNIT_CLKGATE_DIS;
	I915_WRITE(SLICE_UNIT_LEVEL_CLKGATE, val);

	/* Wa_2201832410:cnl */
	val = I915_READ(SUBSLICE_UNIT_LEVEL_CLKGATE);
	val |= GWUNIT_CLKGATE_DIS;
	I915_WRITE(SUBSLICE_UNIT_LEVEL_CLKGATE, val);

	/* WaDisableVFclkgate:cnl */
	/* WaVFUnitClockGatingDisable:cnl */
	val = I915_READ(UNSLICE_UNIT_LEVEL_CLKGATE);
	val |= VFUNIT_CLKGATE_DIS;
	I915_WRITE(UNSLICE_UNIT_LEVEL_CLKGATE, val);
}