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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_state {scalar_t__ gamma_lut; scalar_t__ degamma_lut; TYPE_1__* ctm; struct drm_crtc* crtc; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_color_ctm {unsigned long long* matrix; } ;
struct TYPE_4__ {int pipe; } ;
struct TYPE_3__ {struct drm_color_ctm* data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CGM_PIPE_CSC_COEFF01 (int) ; 
 int /*<<< orphan*/  CGM_PIPE_CSC_COEFF23 (int) ; 
 int /*<<< orphan*/  CGM_PIPE_CSC_COEFF45 (int) ; 
 int /*<<< orphan*/  CGM_PIPE_CSC_COEFF67 (int) ; 
 int /*<<< orphan*/  CGM_PIPE_CSC_COEFF8 (int) ; 
 int /*<<< orphan*/  CGM_PIPE_MODE (int) ; 
 int CGM_PIPE_MODE_CSC ; 
 int CGM_PIPE_MODE_DEGAMMA ; 
 int CGM_PIPE_MODE_GAMMA ; 
 scalar_t__ CTM_COEFF_8_0 ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int clamp_val (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  crtc_state_is_legacy_gamma (struct drm_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 TYPE_2__* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void cherryview_load_csc_matrix(struct drm_crtc_state *state)
{
	struct drm_crtc *crtc = state->crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	int pipe = to_intel_crtc(crtc)->pipe;
	uint32_t mode;

	if (state->ctm) {
		struct drm_color_ctm *ctm = state->ctm->data;
		uint16_t coeffs[9] = { 0, };
		int i;

		for (i = 0; i < ARRAY_SIZE(coeffs); i++) {
			uint64_t abs_coeff =
				((1ULL << 63) - 1) & ctm->matrix[i];

			/* Round coefficient. */
			abs_coeff += 1 << (32 - 13);
			/* Clamp to hardware limits. */
			abs_coeff = clamp_val(abs_coeff, 0, CTM_COEFF_8_0 - 1);

			/* Write coefficients in S3.12 format. */
			if (ctm->matrix[i] & (1ULL << 63))
				coeffs[i] = 1 << 15;
			coeffs[i] |= ((abs_coeff >> 32) & 7) << 12;
			coeffs[i] |= (abs_coeff >> 20) & 0xfff;
		}

		I915_WRITE(CGM_PIPE_CSC_COEFF01(pipe),
			   coeffs[1] << 16 | coeffs[0]);
		I915_WRITE(CGM_PIPE_CSC_COEFF23(pipe),
			   coeffs[3] << 16 | coeffs[2]);
		I915_WRITE(CGM_PIPE_CSC_COEFF45(pipe),
			   coeffs[5] << 16 | coeffs[4]);
		I915_WRITE(CGM_PIPE_CSC_COEFF67(pipe),
			   coeffs[7] << 16 | coeffs[6]);
		I915_WRITE(CGM_PIPE_CSC_COEFF8(pipe), coeffs[8]);
	}

	mode = (state->ctm ? CGM_PIPE_MODE_CSC : 0);
	if (!crtc_state_is_legacy_gamma(state)) {
		mode |= (state->degamma_lut ? CGM_PIPE_MODE_DEGAMMA : 0) |
			(state->gamma_lut ? CGM_PIPE_MODE_GAMMA : 0);
	}
	I915_WRITE(CGM_PIPE_MODE(pipe), mode);
}