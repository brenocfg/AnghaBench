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
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_2__ adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int pipe_bpp; int /*<<< orphan*/  gamma_mode; scalar_t__ limited_color_range; TYPE_3__ base; scalar_t__ dither; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_10BPC ; 
 int PIPECONF_12BPC ; 
 int PIPECONF_6BPC ; 
 int PIPECONF_8BPC ; 
 int PIPECONF_COLOR_RANGE_SELECT ; 
 int PIPECONF_DITHER_EN ; 
 int PIPECONF_DITHER_TYPE_SP ; 
 int PIPECONF_GAMMA_MODE (int /*<<< orphan*/ ) ; 
 int PIPECONF_INTERLACED_ILK ; 
 int PIPECONF_PROGRESSIVE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ironlake_set_pipeconf(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;
	u32 val;

	val = 0;

	switch (crtc_state->pipe_bpp) {
	case 18:
		val |= PIPECONF_6BPC;
		break;
	case 24:
		val |= PIPECONF_8BPC;
		break;
	case 30:
		val |= PIPECONF_10BPC;
		break;
	case 36:
		val |= PIPECONF_12BPC;
		break;
	default:
		/* Case prevented by intel_choose_pipe_bpp_dither. */
		BUG();
	}

	if (crtc_state->dither)
		val |= (PIPECONF_DITHER_EN | PIPECONF_DITHER_TYPE_SP);

	if (crtc_state->base.adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE)
		val |= PIPECONF_INTERLACED_ILK;
	else
		val |= PIPECONF_PROGRESSIVE;

	if (crtc_state->limited_color_range)
		val |= PIPECONF_COLOR_RANGE_SELECT;

	val |= PIPECONF_GAMMA_MODE(crtc_state->gamma_mode);

	I915_WRITE(PIPECONF(pipe), val);
	POSTING_READ(PIPECONF(pipe));
}