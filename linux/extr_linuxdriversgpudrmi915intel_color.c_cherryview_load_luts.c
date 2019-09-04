#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc_state {TYPE_4__* gamma_lut; TYPE_2__* degamma_lut; scalar_t__ ctm; struct drm_crtc* crtc; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct drm_color_lut {int /*<<< orphan*/  red; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_6__ {size_t degamma_lut_size; size_t gamma_lut_size; } ;
struct TYPE_10__ {TYPE_1__ color; } ;
struct TYPE_9__ {struct drm_color_lut* data; } ;
struct TYPE_8__ {int pipe; } ;
struct TYPE_7__ {struct drm_color_lut* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGM_PIPE_DEGAMMA (int,size_t,int) ; 
 int /*<<< orphan*/  CGM_PIPE_GAMMA (int,size_t,int) ; 
 int /*<<< orphan*/  CGM_PIPE_MODE (int) ; 
 size_t CGM_PIPE_MODE_CSC ; 
 size_t CGM_PIPE_MODE_DEGAMMA ; 
 size_t CGM_PIPE_MODE_GAMMA ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,size_t) ; 
 TYPE_5__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ crtc_state_is_legacy_gamma (struct drm_crtc_state*) ; 
 int drm_color_lut_extract (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i9xx_load_luts_internal (struct drm_crtc*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void cherryview_load_luts(struct drm_crtc_state *state)
{
	struct drm_crtc *crtc = state->crtc;
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	enum pipe pipe = to_intel_crtc(crtc)->pipe;
	struct drm_color_lut *lut;
	uint32_t i, lut_size;
	uint32_t word0, word1;

	if (crtc_state_is_legacy_gamma(state)) {
		/* Turn off degamma/gamma on CGM block. */
		I915_WRITE(CGM_PIPE_MODE(pipe),
			   (state->ctm ? CGM_PIPE_MODE_CSC : 0));
		i9xx_load_luts_internal(crtc, state->gamma_lut,
					to_intel_crtc_state(state));
		return;
	}

	if (state->degamma_lut) {
		lut = state->degamma_lut->data;
		lut_size = INTEL_INFO(dev_priv)->color.degamma_lut_size;
		for (i = 0; i < lut_size; i++) {
			/* Write LUT in U0.14 format. */
			word0 =
			(drm_color_lut_extract(lut[i].green, 14) << 16) |
			drm_color_lut_extract(lut[i].blue, 14);
			word1 = drm_color_lut_extract(lut[i].red, 14);

			I915_WRITE(CGM_PIPE_DEGAMMA(pipe, i, 0), word0);
			I915_WRITE(CGM_PIPE_DEGAMMA(pipe, i, 1), word1);
		}
	}

	if (state->gamma_lut) {
		lut = state->gamma_lut->data;
		lut_size = INTEL_INFO(dev_priv)->color.gamma_lut_size;
		for (i = 0; i < lut_size; i++) {
			/* Write LUT in U0.10 format. */
			word0 =
			(drm_color_lut_extract(lut[i].green, 10) << 16) |
			drm_color_lut_extract(lut[i].blue, 10);
			word1 = drm_color_lut_extract(lut[i].red, 10);

			I915_WRITE(CGM_PIPE_GAMMA(pipe, i, 0), word0);
			I915_WRITE(CGM_PIPE_GAMMA(pipe, i, 1), word1);
		}
	}

	I915_WRITE(CGM_PIPE_MODE(pipe),
		   (state->ctm ? CGM_PIPE_MODE_CSC : 0) |
		   (state->degamma_lut ? CGM_PIPE_MODE_DEGAMMA : 0) |
		   (state->gamma_lut ? CGM_PIPE_MODE_GAMMA : 0));

	/*
	 * Also program a linear LUT in the legacy block (behind the
	 * CGM block).
	 */
	i9xx_load_luts_internal(crtc, NULL, to_intel_crtc_state(state));
}