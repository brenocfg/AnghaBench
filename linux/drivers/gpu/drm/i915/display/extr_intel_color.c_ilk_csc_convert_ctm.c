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
typedef  unsigned long long u64 ;
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* ctm; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct drm_color_ctm {unsigned long long* matrix; } ;
struct TYPE_3__ {struct drm_color_ctm* data; } ;

/* Variables and functions */
 unsigned long long CTM_COEFF_0_125 ; 
 unsigned long long CTM_COEFF_0_25 ; 
 unsigned long long CTM_COEFF_0_5 ; 
 unsigned long long CTM_COEFF_1_0 ; 
 unsigned long long CTM_COEFF_2_0 ; 
 scalar_t__ CTM_COEFF_4_0 ; 
 scalar_t__ CTM_COEFF_NEGATIVE (unsigned long long const) ; 
 int ILK_CSC_COEFF_FP (unsigned long long,int) ; 
 unsigned long long clamp_val (unsigned long long,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long long* ctm_mult_by_limited (unsigned long long*,unsigned long long*) ; 
 scalar_t__ ilk_csc_limited_range (struct intel_crtc_state const*) ; 

__attribute__((used)) static void ilk_csc_convert_ctm(const struct intel_crtc_state *crtc_state,
				u16 coeffs[9])
{
	const struct drm_color_ctm *ctm = crtc_state->base.ctm->data;
	const u64 *input;
	u64 temp[9];
	int i;

	if (ilk_csc_limited_range(crtc_state))
		input = ctm_mult_by_limited(temp, ctm->matrix);
	else
		input = ctm->matrix;

	/*
	 * Convert fixed point S31.32 input to format supported by the
	 * hardware.
	 */
	for (i = 0; i < 9; i++) {
		u64 abs_coeff = ((1ULL << 63) - 1) & input[i];

		/*
		 * Clamp input value to min/max supported by
		 * hardware.
		 */
		abs_coeff = clamp_val(abs_coeff, 0, CTM_COEFF_4_0 - 1);

		coeffs[i] = 0;

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
}