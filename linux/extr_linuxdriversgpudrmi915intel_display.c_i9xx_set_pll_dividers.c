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
struct intel_crtc {TYPE_3__* config; int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  fp1; int /*<<< orphan*/  fp0; } ;
struct TYPE_6__ {TYPE_2__ dpll_hw_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i9xx_set_pll_dividers(struct intel_crtc *crtc)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	I915_WRITE(FP0(crtc->pipe), crtc->config->dpll_hw_state.fp0);
	I915_WRITE(FP1(crtc->pipe), crtc->config->dpll_hw_state.fp1);
}