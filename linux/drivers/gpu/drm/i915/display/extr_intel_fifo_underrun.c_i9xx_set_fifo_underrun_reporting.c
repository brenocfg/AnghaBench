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
typedef  int u32 ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPESTAT (int) ; 
 int PIPE_FIFO_UNDERRUN_STATUS ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int i915_pipestat_enable_mask (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i9xx_set_fifo_underrun_reporting(struct drm_device *dev,
					     enum pipe pipe,
					     bool enable, bool old)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	i915_reg_t reg = PIPESTAT(pipe);

	lockdep_assert_held(&dev_priv->irq_lock);

	if (enable) {
		u32 enable_mask = i915_pipestat_enable_mask(dev_priv, pipe);

		I915_WRITE(reg, enable_mask | PIPE_FIFO_UNDERRUN_STATUS);
		POSTING_READ(reg);
	} else {
		if (old && I915_READ(reg) & PIPE_FIFO_UNDERRUN_STATUS)
			DRM_ERROR("pipe %c underrun\n", pipe_name(pipe));
	}
}