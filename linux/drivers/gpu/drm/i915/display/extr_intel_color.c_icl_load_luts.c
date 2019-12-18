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
struct TYPE_2__ {scalar_t__ degamma_lut; int /*<<< orphan*/  crtc; struct drm_property_blob* gamma_lut; } ;
struct intel_crtc_state {int gamma_mode; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct drm_property_blob {int dummy; } ;

/* Variables and functions */
#define  GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED 129 
#define  GAMMA_MODE_MODE_8BIT 128 
 int GAMMA_MODE_MODE_MASK ; 
 int /*<<< orphan*/  PAL_PREC_INDEX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdw_load_lut_10 (struct intel_crtc*,struct drm_property_blob const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glk_load_degamma_lut (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  i9xx_load_luts (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  icl_program_gamma_multi_segment (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  icl_program_gamma_superfine_segment (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  ivb_load_lut_ext_max (struct intel_crtc*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_load_luts(const struct intel_crtc_state *crtc_state)
{
	const struct drm_property_blob *gamma_lut = crtc_state->base.gamma_lut;
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);

	if (crtc_state->base.degamma_lut)
		glk_load_degamma_lut(crtc_state);

	switch (crtc_state->gamma_mode & GAMMA_MODE_MODE_MASK) {
	case GAMMA_MODE_MODE_8BIT:
		i9xx_load_luts(crtc_state);
		break;

	case GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED:
		icl_program_gamma_superfine_segment(crtc_state);
		icl_program_gamma_multi_segment(crtc_state);
		break;

	default:
		bdw_load_lut_10(crtc, gamma_lut, PAL_PREC_INDEX_VALUE(0));
		ivb_load_lut_ext_max(crtc);
	}
}