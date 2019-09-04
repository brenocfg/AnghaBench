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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPESTAT (int /*<<< orphan*/ ) ; 
 int PIPE_FIFO_UNDERRUN_STATUS ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int i915_pipestat_enable_mask (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_intel_cpu_fifo_underrun (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_check_fifo_underruns(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	i915_reg_t reg = PIPESTAT(crtc->pipe);
	u32 enable_mask;

	lockdep_assert_held(&dev_priv->irq_lock);

	if ((I915_READ(reg) & PIPE_FIFO_UNDERRUN_STATUS) == 0)
		return;

	enable_mask = i915_pipestat_enable_mask(dev_priv, crtc->pipe);
	I915_WRITE(reg, enable_mask | PIPE_FIFO_UNDERRUN_STATUS);
	POSTING_READ(reg);

	trace_intel_cpu_fifo_underrun(dev_priv, crtc->pipe);
	DRM_ERROR("pipe %c underrun\n", pipe_name(crtc->pipe));
}