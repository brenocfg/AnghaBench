#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  unsigned long long u64 ;
struct intel_crtc_state {int limited_color_range; scalar_t__ ycbcr420; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc_state {TYPE_1__* ctm; struct drm_crtc* crtc; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct drm_color_ctm {unsigned long long* matrix; } ;
struct TYPE_2__ {struct drm_color_ctm* data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int CSC_BLACK_SCREEN_OFFSET ; 
 int CSC_MODE_YUV_TO_RGB ; 
 scalar_t__ CTM_COEFF_0_125 ; 
 scalar_t__ CTM_COEFF_0_25 ; 
 scalar_t__ CTM_COEFF_0_5 ; 
 scalar_t__ CTM_COEFF_1_0 ; 
 scalar_t__ CTM_COEFF_2_0 ; 
 scalar_t__ CTM_COEFF_4_0 ; 
 scalar_t__ CTM_COEFF_NEGATIVE (unsigned long long const) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int ILK_CSC_COEFF_1_0 ; 
 int ILK_CSC_COEFF_FP (scalar_t__,int) ; 
 int ILK_CSC_COEFF_LIMITED_RANGE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BU (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BV (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BY (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RU_GU (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RV_GV (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RY_GY (int) ; 
 int /*<<< orphan*/  PIPE_CSC_MODE (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_HI (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_LO (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_ME (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_HI (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_LO (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_ME (int) ; 
 scalar_t__ clamp_val (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long long* ctm_mult_by_limited (unsigned long long*,unsigned long long*) ; 
 int /*<<< orphan*/  ilk_load_ycbcr_conversion_matrix (struct intel_crtc*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_crtc_state* to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void ilk_load_csc_matrix(struct drm_crtc_state *crtc_state)
{
	struct drm_crtc *crtc = crtc_state->crtc;
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int i, pipe = intel_crtc->pipe;
	uint16_t coeffs[9] = { 0, };
	struct intel_crtc_state *intel_crtc_state = to_intel_crtc_state(crtc_state);
	bool limited_color_range = false;

	/*
	 * FIXME if there's a gamma LUT after the CSC, we should
	 * do the range compression using the gamma LUT instead.
	 */
	if (INTEL_GEN(dev_priv) >= 8 || IS_HASWELL(dev_priv))
		limited_color_range = intel_crtc_state->limited_color_range;

	if (intel_crtc_state->ycbcr420) {
		ilk_load_ycbcr_conversion_matrix(intel_crtc);
		return;
	} else if (crtc_state->ctm) {
		struct drm_color_ctm *ctm = crtc_state->ctm->data;
		const u64 *input;
		u64 temp[9];

		if (limited_color_range)
			input = ctm_mult_by_limited(temp, ctm->matrix);
		else
			input = ctm->matrix;

		/*
		 * Convert fixed point S31.32 input to format supported by the
		 * hardware.
		 */
		for (i = 0; i < ARRAY_SIZE(coeffs); i++) {
			uint64_t abs_coeff = ((1ULL << 63) - 1) & input[i];

			/*
			 * Clamp input value to min/max supported by
			 * hardware.
			 */
			abs_coeff = clamp_val(abs_coeff, 0, CTM_COEFF_4_0 - 1);

			/* sign bit */
			if (CTM_COEFF_NEGATIVE(input[i]))
				coeffs[i] |= 1 << 15;

			if (abs_coeff < CTM_COEFF_0_125)
				coeffs[i] |= (3 << 12) |
					ILK_CSC_COEFF_FP(abs_coeff, 12);
			else if (abs_coeff < CTM_COEFF_0_25)
				coeffs[i] |= (2 << 12) |
					ILK_CSC_COEFF_FP(abs_coeff, 11);
			else if (abs_coeff < CTM_COEFF_0_5)
				coeffs[i] |= (1 << 12) |
					ILK_CSC_COEFF_FP(abs_coeff, 10);
			else if (abs_coeff < CTM_COEFF_1_0)
				coeffs[i] |= ILK_CSC_COEFF_FP(abs_coeff, 9);
			else if (abs_coeff < CTM_COEFF_2_0)
				coeffs[i] |= (7 << 12) |
					ILK_CSC_COEFF_FP(abs_coeff, 8);
			else
				coeffs[i] |= (6 << 12) |
					ILK_CSC_COEFF_FP(abs_coeff, 7);
		}
	} else {
		/*
		 * Load an identity matrix if no coefficients are provided.
		 *
		 * TODO: Check what kind of values actually come out of the
		 * pipe with these coeff/postoff values and adjust to get the
		 * best accuracy. Perhaps we even need to take the bpc value
		 * into consideration.
		 */
		for (i = 0; i < 3; i++) {
			if (limited_color_range)
				coeffs[i * 3 + i] =
					ILK_CSC_COEFF_LIMITED_RANGE;
			else
				coeffs[i * 3 + i] = ILK_CSC_COEFF_1_0;
		}
	}

	I915_WRITE(PIPE_CSC_COEFF_RY_GY(pipe), coeffs[0] << 16 | coeffs[1]);
	I915_WRITE(PIPE_CSC_COEFF_BY(pipe), coeffs[2] << 16);

	I915_WRITE(PIPE_CSC_COEFF_RU_GU(pipe), coeffs[3] << 16 | coeffs[4]);
	I915_WRITE(PIPE_CSC_COEFF_BU(pipe), coeffs[5] << 16);

	I915_WRITE(PIPE_CSC_COEFF_RV_GV(pipe), coeffs[6] << 16 | coeffs[7]);
	I915_WRITE(PIPE_CSC_COEFF_BV(pipe), coeffs[8] << 16);

	I915_WRITE(PIPE_CSC_PREOFF_HI(pipe), 0);
	I915_WRITE(PIPE_CSC_PREOFF_ME(pipe), 0);
	I915_WRITE(PIPE_CSC_PREOFF_LO(pipe), 0);

	if (INTEL_GEN(dev_priv) > 6) {
		uint16_t postoff = 0;

		if (limited_color_range)
			postoff = (16 * (1 << 12) / 255) & 0x1fff;

		I915_WRITE(PIPE_CSC_POSTOFF_HI(pipe), postoff);
		I915_WRITE(PIPE_CSC_POSTOFF_ME(pipe), postoff);
		I915_WRITE(PIPE_CSC_POSTOFF_LO(pipe), postoff);

		I915_WRITE(PIPE_CSC_MODE(pipe), 0);
	} else {
		uint32_t mode = CSC_MODE_YUV_TO_RGB;

		if (limited_color_range)
			mode |= CSC_BLACK_SCREEN_OFFSET;

		I915_WRITE(PIPE_CSC_MODE(pipe), mode);
	}
}