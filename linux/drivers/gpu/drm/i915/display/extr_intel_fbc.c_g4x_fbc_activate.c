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
struct TYPE_8__ {TYPE_1__* format; } ;
struct intel_fbc_reg_params {int flags; TYPE_5__ crtc; TYPE_4__* vma; TYPE_2__ fb; } ;
struct TYPE_12__ {struct intel_fbc_reg_params params; } ;
struct drm_i915_private {TYPE_6__ fbc; } ;
struct TYPE_10__ {TYPE_3__* fence; } ;
struct TYPE_9__ {int id; } ;
struct TYPE_7__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPFC_CONTROL ; 
 int DPFC_CTL_EN ; 
 int DPFC_CTL_FENCE_EN ; 
 int DPFC_CTL_LIMIT_1X ; 
 int DPFC_CTL_LIMIT_2X ; 
 int DPFC_CTL_PLANE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPFC_FENCE_YOFF ; 
 int DPFC_SR_EN ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PLANE_HAS_FENCE ; 

__attribute__((used)) static void g4x_fbc_activate(struct drm_i915_private *dev_priv)
{
	struct intel_fbc_reg_params *params = &dev_priv->fbc.params;
	u32 dpfc_ctl;

	dpfc_ctl = DPFC_CTL_PLANE(params->crtc.i9xx_plane) | DPFC_SR_EN;
	if (params->fb.format->cpp[0] == 2)
		dpfc_ctl |= DPFC_CTL_LIMIT_2X;
	else
		dpfc_ctl |= DPFC_CTL_LIMIT_1X;

	if (params->flags & PLANE_HAS_FENCE) {
		dpfc_ctl |= DPFC_CTL_FENCE_EN | params->vma->fence->id;
		I915_WRITE(DPFC_FENCE_YOFF, params->crtc.fence_y_offset);
	} else {
		I915_WRITE(DPFC_FENCE_YOFF, 0);
	}

	/* enable it... */
	I915_WRITE(DPFC_CONTROL, dpfc_ctl | DPFC_CTL_EN);
}