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
struct TYPE_11__ {int fence_y_offset; int /*<<< orphan*/  i9xx_plane; } ;
struct TYPE_9__ {TYPE_2__* format; } ;
struct intel_fbc_reg_params {int flags; TYPE_6__* vma; TYPE_5__ crtc; TYPE_3__ fb; } ;
struct TYPE_7__ {int threshold; struct intel_fbc_reg_params params; } ;
struct drm_i915_private {TYPE_1__ fbc; } ;
struct TYPE_12__ {TYPE_4__* fence; } ;
struct TYPE_10__ {int id; } ;
struct TYPE_8__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPFC_CPU_FENCE_OFFSET ; 
 int DPFC_CTL_EN ; 
 int DPFC_CTL_FENCE_EN ; 
 int DPFC_CTL_LIMIT_1X ; 
 int DPFC_CTL_LIMIT_2X ; 
 int DPFC_CTL_LIMIT_4X ; 
 int DPFC_CTL_PLANE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILK_DPFC_CONTROL ; 
 int /*<<< orphan*/  ILK_DPFC_FENCE_YOFF ; 
 int /*<<< orphan*/  ILK_FBC_RT_BASE ; 
 int ILK_FBC_RT_VALID ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int PLANE_HAS_FENCE ; 
 int SNB_CPU_FENCE_ENABLE ; 
 int /*<<< orphan*/  SNB_DPFC_CTL_SA ; 
 int i915_ggtt_offset (TYPE_6__*) ; 
 int /*<<< orphan*/  intel_fbc_recompress (struct drm_i915_private*) ; 

__attribute__((used)) static void ilk_fbc_activate(struct drm_i915_private *dev_priv)
{
	struct intel_fbc_reg_params *params = &dev_priv->fbc.params;
	u32 dpfc_ctl;
	int threshold = dev_priv->fbc.threshold;

	dpfc_ctl = DPFC_CTL_PLANE(params->crtc.i9xx_plane);
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
		dpfc_ctl |= DPFC_CTL_FENCE_EN;
		if (IS_GEN(dev_priv, 5))
			dpfc_ctl |= params->vma->fence->id;
		if (IS_GEN(dev_priv, 6)) {
			I915_WRITE(SNB_DPFC_CTL_SA,
				   SNB_CPU_FENCE_ENABLE |
				   params->vma->fence->id);
			I915_WRITE(DPFC_CPU_FENCE_OFFSET,
				   params->crtc.fence_y_offset);
		}
	} else {
		if (IS_GEN(dev_priv, 6)) {
			I915_WRITE(SNB_DPFC_CTL_SA, 0);
			I915_WRITE(DPFC_CPU_FENCE_OFFSET, 0);
		}
	}

	I915_WRITE(ILK_DPFC_FENCE_YOFF, params->crtc.fence_y_offset);
	I915_WRITE(ILK_FBC_RT_BASE,
		   i915_ggtt_offset(params->vma) | ILK_FBC_RT_VALID);
	/* enable it... */
	I915_WRITE(ILK_DPFC_CONTROL, dpfc_ctl | DPFC_CTL_EN);

	intel_fbc_recompress(dev_priv);
}