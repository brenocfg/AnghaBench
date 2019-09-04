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
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_3__* config; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  control; } ;
struct TYPE_6__ {TYPE_2__ gmch_pfit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFIT_CONTROL ; 
 int /*<<< orphan*/  assert_pipe_disabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i9xx_pfit_disable(struct intel_crtc *crtc)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (!crtc->config->gmch_pfit.control)
		return;

	assert_pipe_disabled(dev_priv, crtc->pipe);

	DRM_DEBUG_DRIVER("disabling pfit, current: 0x%08x\n",
			 I915_READ(PFIT_CONTROL));
	I915_WRITE(PFIT_CONTROL, 0);
}