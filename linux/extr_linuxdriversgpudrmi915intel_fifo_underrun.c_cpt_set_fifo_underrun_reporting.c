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
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDE_ERROR_CPT ; 
 int /*<<< orphan*/  SERR_INT ; 
 int SERR_INT_TRANS_FIFO_UNDERRUN (int) ; 
 int /*<<< orphan*/  cpt_can_enable_serr_int (struct drm_device*) ; 
 int /*<<< orphan*/  ibx_disable_display_interrupt (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibx_enable_display_interrupt (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void cpt_set_fifo_underrun_reporting(struct drm_device *dev,
					    enum pipe pch_transcoder,
					    bool enable, bool old)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (enable) {
		I915_WRITE(SERR_INT,
			   SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder));

		if (!cpt_can_enable_serr_int(dev))
			return;

		ibx_enable_display_interrupt(dev_priv, SDE_ERROR_CPT);
	} else {
		ibx_disable_display_interrupt(dev_priv, SDE_ERROR_CPT);

		if (old && I915_READ(SERR_INT) &
		    SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder)) {
			DRM_ERROR("uncleared pch fifo underrun on pch transcoder %c\n",
				  pipe_name(pch_transcoder));
		}
	}
}