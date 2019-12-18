#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {int fence_y_offset; int /*<<< orphan*/  pipe; int /*<<< orphan*/  i9xx_plane; } ;
struct TYPE_8__ {TYPE_1__* format; } ;
struct intel_fbc_reg_params {int gen9_wa_cfb_stride; int flags; TYPE_6__ crtc; TYPE_4__* vma; TYPE_2__ fb; } ;
struct TYPE_11__ {int threshold; scalar_t__ false_color; struct intel_fbc_reg_params params; } ;
struct drm_i915_private {TYPE_5__ fbc; } ;
struct TYPE_10__ {TYPE_3__* fence; int /*<<< orphan*/  obj; } ;
struct TYPE_9__ {int id; } ;
struct TYPE_7__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHICKEN_MISC_4 ; 
 int /*<<< orphan*/  CHICKEN_PIPESL_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPFC_CPU_FENCE_OFFSET ; 
 int DPFC_CTL_EN ; 
 int DPFC_CTL_LIMIT_1X ; 
 int DPFC_CTL_LIMIT_2X ; 
 int DPFC_CTL_LIMIT_4X ; 
 int FBC_CTL_FALSE_COLOR ; 
 int FBC_STRIDE_MASK ; 
 int FBC_STRIDE_OVERRIDE ; 
 int HSW_FBCQ_DIS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ I915_TILING_X ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILK_DISPLAY_CHICKEN1 ; 
 int /*<<< orphan*/  ILK_DPFC_CHICKEN ; 
 int ILK_DPFC_CHICKEN_COMP_DUMMY_PIXEL ; 
 int /*<<< orphan*/  ILK_DPFC_CONTROL ; 
 int ILK_FBCQ_DIS ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int IVB_DPFC_CTL_FENCE_EN ; 
 int IVB_DPFC_CTL_PLANE (int /*<<< orphan*/ ) ; 
 int PLANE_HAS_FENCE ; 
 int SNB_CPU_FENCE_ENABLE ; 
 int /*<<< orphan*/  SNB_DPFC_CTL_SA ; 
 scalar_t__ i915_gem_object_get_tiling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_fbc_recompress (struct drm_i915_private*) ; 

__attribute__((used)) static void gen7_fbc_activate(struct drm_i915_private *dev_priv)
{
	struct intel_fbc_reg_params *params = &dev_priv->fbc.params;
	u32 dpfc_ctl;
	int threshold = dev_priv->fbc.threshold;

	/* Display WA #0529: skl, kbl, bxt. */
	if (IS_GEN(dev_priv, 9) && !IS_GEMINILAKE(dev_priv)) {
		u32 val = I915_READ(CHICKEN_MISC_4);

		val &= ~(FBC_STRIDE_OVERRIDE | FBC_STRIDE_MASK);

		if (i915_gem_object_get_tiling(params->vma->obj) !=
		    I915_TILING_X)
			val |= FBC_STRIDE_OVERRIDE | params->gen9_wa_cfb_stride;

		I915_WRITE(CHICKEN_MISC_4, val);
	}

	dpfc_ctl = 0;
	if (IS_IVYBRIDGE(dev_priv))
		dpfc_ctl |= IVB_DPFC_CTL_PLANE(params->crtc.i9xx_plane);

	if (params->fb.format->cpp[0] == 2)
		threshold++;

	switch (threshold) {
	case 4:
	case 3:
		dpfc_ctl |= DPFC_CTL_LIMIT_4X;
		break;
	case 2:
		dpfc_ctl |= DPFC_CTL_LIMIT_2X;
		break;
	case 1:
		dpfc_ctl |= DPFC_CTL_LIMIT_1X;
		break;
	}

	if (params->flags & PLANE_HAS_FENCE) {
		dpfc_ctl |= IVB_DPFC_CTL_FENCE_EN;
		I915_WRITE(SNB_DPFC_CTL_SA,
			   SNB_CPU_FENCE_ENABLE |
			   params->vma->fence->id);
		I915_WRITE(DPFC_CPU_FENCE_OFFSET, params->crtc.fence_y_offset);
	} else {
		I915_WRITE(SNB_DPFC_CTL_SA,0);
		I915_WRITE(DPFC_CPU_FENCE_OFFSET, 0);
	}

	if (dev_priv->fbc.false_color)
		dpfc_ctl |= FBC_CTL_FALSE_COLOR;

	if (IS_IVYBRIDGE(dev_priv)) {
		/* WaFbcAsynchFlipDisableFbcQueue:ivb */
		I915_WRITE(ILK_DISPLAY_CHICKEN1,
			   I915_READ(ILK_DISPLAY_CHICKEN1) |
			   ILK_FBCQ_DIS);
	} else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		/* WaFbcAsynchFlipDisableFbcQueue:hsw,bdw */
		I915_WRITE(CHICKEN_PIPESL_1(params->crtc.pipe),
			   I915_READ(CHICKEN_PIPESL_1(params->crtc.pipe)) |
			   HSW_FBCQ_DIS);
	}

	if (IS_GEN(dev_priv, 11))
		/* Wa_1409120013:icl,ehl */
		I915_WRITE(ILK_DPFC_CHICKEN, ILK_DPFC_CHICKEN_COMP_DUMMY_PIXEL);

	I915_WRITE(ILK_DPFC_CONTROL, dpfc_ctl | DPFC_CTL_EN);

	intel_fbc_recompress(dev_priv);
}