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
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_set_pch_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  trace_intel_pch_fifo_underrun (struct drm_i915_private*,int) ; 

void intel_pch_fifo_underrun_irq_handler(struct drm_i915_private *dev_priv,
					 enum pipe pch_transcoder)
{
	if (intel_set_pch_fifo_underrun_reporting(dev_priv, pch_transcoder,
						  false)) {
		trace_intel_pch_fifo_underrun(dev_priv, pch_transcoder);
		DRM_ERROR("PCH transcoder %c FIFO underrun\n",
			  pipe_name(pch_transcoder));
	}
}