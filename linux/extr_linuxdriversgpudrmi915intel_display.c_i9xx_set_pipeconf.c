#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_4__* config; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_7__ {TYPE_2__ adjusted_mode; } ;
struct TYPE_8__ {int pipe_bpp; scalar_t__ limited_color_range; TYPE_3__ base; scalar_t__ dither; scalar_t__ double_wide; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_SDVO ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPECONF (int /*<<< orphan*/ ) ; 
 int PIPECONF_10BPC ; 
 int PIPECONF_6BPC ; 
 int PIPECONF_8BPC ; 
 int PIPECONF_COLOR_RANGE_SELECT ; 
 int PIPECONF_DITHER_EN ; 
 int PIPECONF_DITHER_TYPE_SP ; 
 int PIPECONF_DOUBLE_WIDE ; 
 int PIPECONF_ENABLE ; 
 int PIPECONF_INTERLACE_W_FIELD_INDICATION ; 
 int PIPECONF_INTERLACE_W_SYNC_SHIFT ; 
 int PIPECONF_PROGRESSIVE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crtc_has_type (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_set_pipeconf(struct intel_crtc *intel_crtc)
{
	struct drm_i915_private *dev_priv = to_i915(intel_crtc->base.dev);
	uint32_t pipeconf;

	pipeconf = 0;

	/* we keep both pipes enabled on 830 */
	if (IS_I830(dev_priv))
		pipeconf |= I915_READ(PIPECONF(intel_crtc->pipe)) & PIPECONF_ENABLE;

	if (intel_crtc->config->double_wide)
		pipeconf |= PIPECONF_DOUBLE_WIDE;

	/* only g4x and later have fancy bpc/dither controls */
	if (IS_G4X(dev_priv) || IS_VALLEYVIEW(dev_priv) ||
	    IS_CHERRYVIEW(dev_priv)) {
		/* Bspec claims that we can't use dithering for 30bpp pipes. */
		if (intel_crtc->config->dither && intel_crtc->config->pipe_bpp != 30)
			pipeconf |= PIPECONF_DITHER_EN |
				    PIPECONF_DITHER_TYPE_SP;

		switch (intel_crtc->config->pipe_bpp) {
		case 18:
			pipeconf |= PIPECONF_6BPC;
			break;
		case 24:
			pipeconf |= PIPECONF_8BPC;
			break;
		case 30:
			pipeconf |= PIPECONF_10BPC;
			break;
		default:
			/* Case prevented by intel_choose_pipe_bpp_dither. */
			BUG();
		}
	}

	if (intel_crtc->config->base.adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE) {
		if (INTEL_GEN(dev_priv) < 4 ||
		    intel_crtc_has_type(intel_crtc->config, INTEL_OUTPUT_SDVO))
			pipeconf |= PIPECONF_INTERLACE_W_FIELD_INDICATION;
		else
			pipeconf |= PIPECONF_INTERLACE_W_SYNC_SHIFT;
	} else
		pipeconf |= PIPECONF_PROGRESSIVE;

	if ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	     intel_crtc->config->limited_color_range)
		pipeconf |= PIPECONF_COLOR_RANGE_SELECT;

	I915_WRITE(PIPECONF(intel_crtc->pipe), pipeconf);
	POSTING_READ(PIPECONF(intel_crtc->pipe));
}