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
struct intel_crtc {scalar_t__ cpu_fifo_underrun_disabled; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbc_handle_fifo_underrun_irq (struct drm_i915_private*) ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int) ; 
 scalar_t__ intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  trace_intel_cpu_fifo_underrun (struct drm_i915_private*,int) ; 

void intel_cpu_fifo_underrun_irq_handler(struct drm_i915_private *dev_priv,
					 enum pipe pipe)
{
	struct intel_crtc *crtc = intel_get_crtc_for_pipe(dev_priv, pipe);

	/* We may be called too early in init, thanks BIOS! */
	if (crtc == NULL)
		return;

	/* GMCH can't disable fifo underruns, filter them. */
	if (HAS_GMCH(dev_priv) &&
	    crtc->cpu_fifo_underrun_disabled)
		return;

	if (intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, false)) {
		trace_intel_cpu_fifo_underrun(dev_priv, pipe);
		DRM_ERROR("CPU pipe %c FIFO underrun\n",
			  pipe_name(pipe));
	}

	intel_fbc_handle_fifo_underrun_irq(dev_priv);
}