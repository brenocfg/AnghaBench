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
struct dpp {int dummy; } ;
struct dcn_dpp_state {void* gamut_remap_c33_c34; void* gamut_remap_c31_c32; void* gamut_remap_c23_c24; void* gamut_remap_c21_c22; void* gamut_remap_c13_c14; void* gamut_remap_c11_c12; scalar_t__ gamut_remap_mode; scalar_t__ rgam_lut_mode; scalar_t__ dgam_lut_mode; scalar_t__ igam_input_format; scalar_t__ igam_lut_mode; scalar_t__ is_enabled; } ;
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DGAM_CONTROL ; 
 int /*<<< orphan*/  CM_DGAM_LUT_MODE ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_C11_C12 ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_C13_C14 ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_C21_C22 ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_C23_C24 ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_C31_C32 ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_C33_C34 ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_CONTROL ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_MODE ; 
 int /*<<< orphan*/  CM_IGAM_CONTROL ; 
 int /*<<< orphan*/  CM_IGAM_INPUT_FORMAT ; 
 int /*<<< orphan*/  CM_IGAM_LUT_MODE ; 
 int /*<<< orphan*/  CM_RGAM_CONTROL ; 
 int /*<<< orphan*/  CM_RGAM_LUT_MODE ; 
 int /*<<< orphan*/  DPP_CLOCK_ENABLE ; 
 int /*<<< orphan*/  DPP_CONTROL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 void* REG_READ (int /*<<< orphan*/ ) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp_read_state(struct dpp *dpp_base,
		struct dcn_dpp_state *s)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_GET(DPP_CONTROL,
			DPP_CLOCK_ENABLE, &s->is_enabled);
	REG_GET(CM_IGAM_CONTROL,
			CM_IGAM_LUT_MODE, &s->igam_lut_mode);
	REG_GET(CM_IGAM_CONTROL,
			CM_IGAM_INPUT_FORMAT, &s->igam_input_format);
	REG_GET(CM_DGAM_CONTROL,
			CM_DGAM_LUT_MODE, &s->dgam_lut_mode);
	REG_GET(CM_RGAM_CONTROL,
			CM_RGAM_LUT_MODE, &s->rgam_lut_mode);
	REG_GET(CM_GAMUT_REMAP_CONTROL,
			CM_GAMUT_REMAP_MODE, &s->gamut_remap_mode);

	if (s->gamut_remap_mode) {
		s->gamut_remap_c11_c12 = REG_READ(CM_GAMUT_REMAP_C11_C12);
		s->gamut_remap_c13_c14 = REG_READ(CM_GAMUT_REMAP_C13_C14);
		s->gamut_remap_c21_c22 = REG_READ(CM_GAMUT_REMAP_C21_C22);
		s->gamut_remap_c23_c24 = REG_READ(CM_GAMUT_REMAP_C23_C24);
		s->gamut_remap_c31_c32 = REG_READ(CM_GAMUT_REMAP_C31_C32);
		s->gamut_remap_c33_c34 = REG_READ(CM_GAMUT_REMAP_C33_C34);
	}
}