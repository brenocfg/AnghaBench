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
struct TYPE_5__ {scalar_t__ enabled; } ;
struct TYPE_6__ {TYPE_2__ pch_pfit; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_CTL (int) ; 
 int /*<<< orphan*/  PF_WIN_POS (int) ; 
 int /*<<< orphan*/  PF_WIN_SZ (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void ironlake_pfit_disable(struct intel_crtc *crtc, bool force)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	int pipe = crtc->pipe;

	/* To avoid upsetting the power well on haswell only disable the pfit if
	 * it's in use. The hw state code will make sure we get this right. */
	if (force || crtc->config->pch_pfit.enabled) {
		I915_WRITE(PF_CTL(pipe), 0);
		I915_WRITE(PF_WIN_POS(pipe), 0);
		I915_WRITE(PF_WIN_SZ(pipe), 0);
	}
}