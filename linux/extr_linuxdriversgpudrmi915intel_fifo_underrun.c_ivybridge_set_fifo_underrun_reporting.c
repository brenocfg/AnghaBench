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
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ERR_INT_IVB ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int ERR_INT_FIFO_UNDERRUN (int) ; 
 int /*<<< orphan*/  GEN7_ERR_INT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ilk_disable_display_irq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilk_enable_display_irq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivb_can_enable_err_int (struct drm_device*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void ivybridge_set_fifo_underrun_reporting(struct drm_device *dev,
						  enum pipe pipe,
						  bool enable, bool old)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	if (enable) {
		I915_WRITE(GEN7_ERR_INT, ERR_INT_FIFO_UNDERRUN(pipe));

		if (!ivb_can_enable_err_int(dev))
			return;

		ilk_enable_display_irq(dev_priv, DE_ERR_INT_IVB);
	} else {
		ilk_disable_display_irq(dev_priv, DE_ERR_INT_IVB);

		if (old &&
		    I915_READ(GEN7_ERR_INT) & ERR_INT_FIFO_UNDERRUN(pipe)) {
			DRM_ERROR("uncleared fifo underrun on pipe %c\n",
				  pipe_name(pipe));
		}
	}
}