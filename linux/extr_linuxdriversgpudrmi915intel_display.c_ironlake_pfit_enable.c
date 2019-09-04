#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; TYPE_3__* config; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_5__ {int pos; int size; scalar_t__ enabled; } ;
struct TYPE_6__ {TYPE_2__ pch_pfit; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PF_CTL (int) ; 
 int PF_ENABLE ; 
 int PF_FILTER_MED_3x3 ; 
 int PF_PIPE_SEL_IVB (int) ; 
 int /*<<< orphan*/  PF_WIN_POS (int) ; 
 int /*<<< orphan*/  PF_WIN_SZ (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void ironlake_pfit_enable(struct intel_crtc *crtc)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	int pipe = crtc->pipe;

	if (crtc->config->pch_pfit.enabled) {
		/* Force use of hard-coded filter coefficients
		 * as some pre-programmed values are broken,
		 * e.g. x201.
		 */
		if (IS_IVYBRIDGE(dev_priv) || IS_HASWELL(dev_priv))
			I915_WRITE(PF_CTL(pipe), PF_ENABLE | PF_FILTER_MED_3x3 |
						 PF_PIPE_SEL_IVB(pipe));
		else
			I915_WRITE(PF_CTL(pipe), PF_ENABLE | PF_FILTER_MED_3x3);
		I915_WRITE(PF_WIN_POS(pipe), crtc->config->pch_pfit.pos);
		I915_WRITE(PF_WIN_SZ(pipe), crtc->config->pch_pfit.size);
	}
}