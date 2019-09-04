#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKL_PS_CTRL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_POS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_SZ (int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void skl_detach_scaler(struct intel_crtc *intel_crtc, int id)
{
	struct drm_device *dev = intel_crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	I915_WRITE(SKL_PS_CTRL(intel_crtc->pipe, id), 0);
	I915_WRITE(SKL_PS_WIN_POS(intel_crtc->pipe, id), 0);
	I915_WRITE(SKL_PS_WIN_SZ(intel_crtc->pipe, id), 0);
}