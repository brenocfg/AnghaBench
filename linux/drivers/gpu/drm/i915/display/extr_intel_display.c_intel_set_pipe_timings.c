#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_display_mode {int crtc_vtotal; int crtc_vblank_end; int flags; int crtc_htotal; int crtc_hsync_start; int crtc_hdisplay; int crtc_hblank_start; int crtc_hblank_end; int crtc_hsync_end; int crtc_vdisplay; int crtc_vblank_start; int crtc_vsync_start; int crtc_vsync_end; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int cpu_transcoder; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  HBLANK (int) ; 
 int /*<<< orphan*/  HSYNC (int) ; 
 int /*<<< orphan*/  HTOTAL (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_SDVO ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int PIPE_B ; 
 int PIPE_C ; 
 int TRANSCODER_EDP ; 
 int /*<<< orphan*/  VBLANK (int) ; 
 int /*<<< orphan*/  VSYNC (int) ; 
 int /*<<< orphan*/  VSYNCSHIFT (int) ; 
 int /*<<< orphan*/  VTOTAL (int) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_set_pipe_timings(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;
	enum transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	const struct drm_display_mode *adjusted_mode = &crtc_state->base.adjusted_mode;
	u32 crtc_vtotal, crtc_vblank_end;
	int vsyncshift = 0;

	/* We need to be careful not to changed the adjusted mode, for otherwise
	 * the hw state checker will get angry at the mismatch. */
	crtc_vtotal = adjusted_mode->crtc_vtotal;
	crtc_vblank_end = adjusted_mode->crtc_vblank_end;

	if (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) {
		/* the chip adds 2 halflines automatically */
		crtc_vtotal -= 1;
		crtc_vblank_end -= 1;

		if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO))
			vsyncshift = (adjusted_mode->crtc_htotal - 1) / 2;
		else
			vsyncshift = adjusted_mode->crtc_hsync_start -
				adjusted_mode->crtc_htotal / 2;
		if (vsyncshift < 0)
			vsyncshift += adjusted_mode->crtc_htotal;
	}

	if (INTEL_GEN(dev_priv) > 3)
		I915_WRITE(VSYNCSHIFT(cpu_transcoder), vsyncshift);

	I915_WRITE(HTOTAL(cpu_transcoder),
		   (adjusted_mode->crtc_hdisplay - 1) |
		   ((adjusted_mode->crtc_htotal - 1) << 16));
	I915_WRITE(HBLANK(cpu_transcoder),
		   (adjusted_mode->crtc_hblank_start - 1) |
		   ((adjusted_mode->crtc_hblank_end - 1) << 16));
	I915_WRITE(HSYNC(cpu_transcoder),
		   (adjusted_mode->crtc_hsync_start - 1) |
		   ((adjusted_mode->crtc_hsync_end - 1) << 16));

	I915_WRITE(VTOTAL(cpu_transcoder),
		   (adjusted_mode->crtc_vdisplay - 1) |
		   ((crtc_vtotal - 1) << 16));
	I915_WRITE(VBLANK(cpu_transcoder),
		   (adjusted_mode->crtc_vblank_start - 1) |
		   ((crtc_vblank_end - 1) << 16));
	I915_WRITE(VSYNC(cpu_transcoder),
		   (adjusted_mode->crtc_vsync_start - 1) |
		   ((adjusted_mode->crtc_vsync_end - 1) << 16));

	/* Workaround: when the EDP input selection is B, the VTOTAL_B must be
	 * programmed with the VTOTAL_EDP value. Same for VTOTAL_C. This is
	 * documented on the DDI_FUNC_CTL register description, EDP Input Select
	 * bits. */
	if (IS_HASWELL(dev_priv) && cpu_transcoder == TRANSCODER_EDP &&
	    (pipe == PIPE_B || pipe == PIPE_C))
		I915_WRITE(VTOTAL(pipe), I915_READ(VTOTAL(cpu_transcoder)));

}