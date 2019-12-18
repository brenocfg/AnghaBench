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
struct sti_hqvdp_hvsrc {int hori_shift; int vert_shift; int /*<<< orphan*/  cv_coef; int /*<<< orphan*/  yv_coef; int /*<<< orphan*/  ch_coef; int /*<<< orphan*/  yh_coef; } ;
typedef  enum sti_hvsrc_orient { ____Placeholder_sti_hvsrc_orient } sti_hvsrc_orient ;

/* Variables and functions */
 int HVSRC_HORI ; 
 int SCALE_MAX_FOR_LEG_LUT_C ; 
 int SCALE_MAX_FOR_LEG_LUT_D ; 
 int SCALE_MAX_FOR_LEG_LUT_E ; 
 int SCALE_MAX_FOR_LEG_LUT_F ; 
 int SHIFT_LUT_A_LEGACY ; 
 int SHIFT_LUT_B ; 
 int SHIFT_LUT_C_C_LEGACY ; 
 int SHIFT_LUT_C_Y_LEGACY ; 
 int SHIFT_LUT_D_C_LEGACY ; 
 int SHIFT_LUT_D_Y_LEGACY ; 
 int SHIFT_LUT_E_C_LEGACY ; 
 int SHIFT_LUT_E_Y_LEGACY ; 
 int SHIFT_LUT_F_C_LEGACY ; 
 int SHIFT_LUT_F_Y_LEGACY ; 
 int* coef_lut_a_legacy ; 
 int* coef_lut_b ; 
 int* coef_lut_c_c_legacy ; 
 int* coef_lut_c_y_legacy ; 
 int* coef_lut_d_c_legacy ; 
 int* coef_lut_d_y_legacy ; 
 int* coef_lut_e_c_legacy ; 
 int* coef_lut_e_y_legacy ; 
 int* coef_lut_f_c_legacy ; 
 int* coef_lut_f_y_legacy ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static void sti_hqvdp_update_hvsrc(enum sti_hvsrc_orient orient, int scale,
		struct sti_hqvdp_hvsrc *hvsrc)
{
	const int *coef_c, *coef_y;
	int shift_c, shift_y;

	/* Get the appropriate coef tables */
	if (scale < SCALE_MAX_FOR_LEG_LUT_F) {
		coef_y = coef_lut_f_y_legacy;
		coef_c = coef_lut_f_c_legacy;
		shift_y = SHIFT_LUT_F_Y_LEGACY;
		shift_c = SHIFT_LUT_F_C_LEGACY;
	} else if (scale < SCALE_MAX_FOR_LEG_LUT_E) {
		coef_y = coef_lut_e_y_legacy;
		coef_c = coef_lut_e_c_legacy;
		shift_y = SHIFT_LUT_E_Y_LEGACY;
		shift_c = SHIFT_LUT_E_C_LEGACY;
	} else if (scale < SCALE_MAX_FOR_LEG_LUT_D) {
		coef_y = coef_lut_d_y_legacy;
		coef_c = coef_lut_d_c_legacy;
		shift_y = SHIFT_LUT_D_Y_LEGACY;
		shift_c = SHIFT_LUT_D_C_LEGACY;
	} else if (scale < SCALE_MAX_FOR_LEG_LUT_C) {
		coef_y = coef_lut_c_y_legacy;
		coef_c = coef_lut_c_c_legacy;
		shift_y = SHIFT_LUT_C_Y_LEGACY;
		shift_c = SHIFT_LUT_C_C_LEGACY;
	} else if (scale == SCALE_MAX_FOR_LEG_LUT_C) {
		coef_y = coef_c = coef_lut_b;
		shift_y = shift_c = SHIFT_LUT_B;
	} else {
		coef_y = coef_c = coef_lut_a_legacy;
		shift_y = shift_c = SHIFT_LUT_A_LEGACY;
	}

	if (orient == HVSRC_HORI) {
		hvsrc->hori_shift = (shift_c << 16) | shift_y;
		memcpy(hvsrc->yh_coef, coef_y, sizeof(hvsrc->yh_coef));
		memcpy(hvsrc->ch_coef, coef_c, sizeof(hvsrc->ch_coef));
	} else {
		hvsrc->vert_shift = (shift_c << 16) | shift_y;
		memcpy(hvsrc->yv_coef, coef_y, sizeof(hvsrc->yv_coef));
		memcpy(hvsrc->cv_coef, coef_c, sizeof(hvsrc->cv_coef));
	}
}