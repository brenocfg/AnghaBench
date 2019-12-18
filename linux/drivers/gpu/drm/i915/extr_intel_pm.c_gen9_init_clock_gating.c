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
 int /*<<< orphan*/  CHICKEN_PAR1_1 ; 
 int /*<<< orphan*/  DISP_ARB_CTL ; 
 int DISP_FBC_MEMORY_WAKE ; 
 int DISP_FBC_WM_DIS ; 
 int GEN7_DOP_CLOCK_GATE_ENABLE ; 
 int /*<<< orphan*/  GEN7_MISCCPCTL ; 
 int /*<<< orphan*/  GEN8_CHICKEN_DCPR_1 ; 
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILK_DPFC_CHICKEN ; 
 int ILK_DPFC_DISABLE_DUMMY0 ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int MASK_WAKEMEM ; 
 int SKL_DE_COMPRESSED_HASH_MODE ; 
 int SKL_EDP_PSR_FIX_RDWRAP ; 

__attribute__((used)) static void gen9_init_clock_gating(struct drm_i915_private *dev_priv)
{
	if (HAS_LLC(dev_priv)) {
		/*
		 * WaCompressedResourceDisplayNewHashMode:skl,kbl
		 * Display WA #0390: skl,kbl
		 *
		 * Must match Sampler, Pixel Back End, and Media. See
		 * WaCompressedResourceSamplerPbeMediaNewHashMode.
		 */
		I915_WRITE(CHICKEN_PAR1_1,
			   I915_READ(CHICKEN_PAR1_1) |
			   SKL_DE_COMPRESSED_HASH_MODE);
	}

	/* See Bspec note for PSR2_CTL bit 31, Wa#828:skl,bxt,kbl,cfl */
	I915_WRITE(CHICKEN_PAR1_1,
		   I915_READ(CHICKEN_PAR1_1) | SKL_EDP_PSR_FIX_RDWRAP);

	/* WaEnableChickenDCPR:skl,bxt,kbl,glk,cfl */
	I915_WRITE(GEN8_CHICKEN_DCPR_1,
		   I915_READ(GEN8_CHICKEN_DCPR_1) | MASK_WAKEMEM);

	/* WaFbcTurnOffFbcWatermark:skl,bxt,kbl,cfl */
	/* WaFbcWakeMemOn:skl,bxt,kbl,glk,cfl */
	I915_WRITE(DISP_ARB_CTL, I915_READ(DISP_ARB_CTL) |
		   DISP_FBC_WM_DIS |
		   DISP_FBC_MEMORY_WAKE);

	/* WaFbcHighMemBwCorruptionAvoidance:skl,bxt,kbl,cfl */
	I915_WRITE(ILK_DPFC_CHICKEN, I915_READ(ILK_DPFC_CHICKEN) |
		   ILK_DPFC_DISABLE_DUMMY0);

	if (IS_SKYLAKE(dev_priv)) {
		/* WaDisableDopClockGating */
		I915_WRITE(GEN7_MISCCPCTL, I915_READ(GEN7_MISCCPCTL)
			   & ~GEN7_DOP_CLOCK_GATE_ENABLE);
	}
}