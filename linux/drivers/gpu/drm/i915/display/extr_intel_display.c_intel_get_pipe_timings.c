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
typedef  int u32 ;
struct TYPE_5__ {int crtc_hdisplay; int crtc_htotal; int crtc_hblank_start; int crtc_hblank_end; int crtc_hsync_start; int crtc_hsync_end; int crtc_vdisplay; int crtc_vtotal; int crtc_vblank_start; int crtc_vblank_end; int crtc_vsync_start; int crtc_vsync_end; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_2__ adjusted_mode; } ;
struct intel_crtc_state {int cpu_transcoder; TYPE_3__ base; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  HBLANK (int) ; 
 int /*<<< orphan*/  HSYNC (int) ; 
 int /*<<< orphan*/  HTOTAL (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_INTERLACE_MASK ; 
 int /*<<< orphan*/  VBLANK (int) ; 
 int /*<<< orphan*/  VSYNC (int) ; 
 int /*<<< orphan*/  VTOTAL (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  transcoder_is_dsi (int) ; 

__attribute__((used)) static void intel_get_pipe_timings(struct intel_crtc *crtc,
				   struct intel_crtc_state *pipe_config)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum transcoder cpu_transcoder = pipe_config->cpu_transcoder;
	u32 tmp;

	tmp = I915_READ(HTOTAL(cpu_transcoder));
	pipe_config->base.adjusted_mode.crtc_hdisplay = (tmp & 0xffff) + 1;
	pipe_config->base.adjusted_mode.crtc_htotal = ((tmp >> 16) & 0xffff) + 1;

	if (!transcoder_is_dsi(cpu_transcoder)) {
		tmp = I915_READ(HBLANK(cpu_transcoder));
		pipe_config->base.adjusted_mode.crtc_hblank_start =
							(tmp & 0xffff) + 1;
		pipe_config->base.adjusted_mode.crtc_hblank_end =
						((tmp >> 16) & 0xffff) + 1;
	}
	tmp = I915_READ(HSYNC(cpu_transcoder));
	pipe_config->base.adjusted_mode.crtc_hsync_start = (tmp & 0xffff) + 1;
	pipe_config->base.adjusted_mode.crtc_hsync_end = ((tmp >> 16) & 0xffff) + 1;

	tmp = I915_READ(VTOTAL(cpu_transcoder));
	pipe_config->base.adjusted_mode.crtc_vdisplay = (tmp & 0xffff) + 1;
	pipe_config->base.adjusted_mode.crtc_vtotal = ((tmp >> 16) & 0xffff) + 1;

	if (!transcoder_is_dsi(cpu_transcoder)) {
		tmp = I915_READ(VBLANK(cpu_transcoder));
		pipe_config->base.adjusted_mode.crtc_vblank_start =
							(tmp & 0xffff) + 1;
		pipe_config->base.adjusted_mode.crtc_vblank_end =
						((tmp >> 16) & 0xffff) + 1;
	}
	tmp = I915_READ(VSYNC(cpu_transcoder));
	pipe_config->base.adjusted_mode.crtc_vsync_start = (tmp & 0xffff) + 1;
	pipe_config->base.adjusted_mode.crtc_vsync_end = ((tmp >> 16) & 0xffff) + 1;

	if (I915_READ(PIPECONF(cpu_transcoder)) & PIPECONF_INTERLACE_MASK) {
		pipe_config->base.adjusted_mode.flags |= DRM_MODE_FLAG_INTERLACE;
		pipe_config->base.adjusted_mode.crtc_vtotal += 1;
		pipe_config->base.adjusted_mode.crtc_vblank_end += 1;
	}
}