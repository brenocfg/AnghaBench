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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int h_taps; int h_taps_c; int v_taps; int v_taps_c; } ;
struct TYPE_7__ {int /*<<< orphan*/  vert_c; int /*<<< orphan*/  horz_c; int /*<<< orphan*/  vert; int /*<<< orphan*/  horz; } ;
struct TYPE_6__ {scalar_t__ horz; scalar_t__ vert; } ;
struct scaler_data {TYPE_3__ taps; TYPE_2__ ratios; TYPE_1__ sharpness; } ;
struct dcn10_dpp {TYPE_5__* tf_shift; TYPE_4__* tf_mask; int /*<<< orphan*/  const* filter_v_c; int /*<<< orphan*/  const* filter_h_c; int /*<<< orphan*/  const* filter_v; int /*<<< orphan*/  const* filter_h; } ;
struct TYPE_10__ {int /*<<< orphan*/  SCL_COEF_RAM_SELECT_CURRENT; } ;
struct TYPE_9__ {int /*<<< orphan*/  SCL_COEF_RAM_SELECT_CURRENT; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSCL_2TAP_CONTROL ; 
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SCL_CHROMA_COEF_MODE ; 
 int /*<<< orphan*/  SCL_COEF_CHROMA_HORZ_FILTER ; 
 int /*<<< orphan*/  SCL_COEF_CHROMA_VERT_FILTER ; 
 int /*<<< orphan*/  SCL_COEF_LUMA_HORZ_FILTER ; 
 int /*<<< orphan*/  SCL_COEF_LUMA_VERT_FILTER ; 
 int /*<<< orphan*/  SCL_COEF_RAM_SELECT ; 
 int /*<<< orphan*/  SCL_H_2TAP_HARDCODE_COEF_EN ; 
 int /*<<< orphan*/  SCL_H_2TAP_SHARP_EN ; 
 int /*<<< orphan*/  SCL_H_2TAP_SHARP_FACTOR ; 
 int /*<<< orphan*/  SCL_MODE ; 
 int /*<<< orphan*/  SCL_V_2TAP_HARDCODE_COEF_EN ; 
 int /*<<< orphan*/  SCL_V_2TAP_SHARP_EN ; 
 int /*<<< orphan*/  SCL_V_2TAP_SHARP_FACTOR ; 
 int /*<<< orphan*/ * dpp1_dscl_get_filter_coeffs_64p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp1_dscl_set_scaler_filter (struct dcn10_dpp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int get_reg_field_value_ex (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpp1_dscl_set_scl_filter(
		struct dcn10_dpp *dpp,
		const struct scaler_data *scl_data,
		bool chroma_coef_mode)
{
	bool h_2tap_hardcode_coef_en = false;
	bool v_2tap_hardcode_coef_en = false;
	bool h_2tap_sharp_en = false;
	bool v_2tap_sharp_en = false;
	uint32_t h_2tap_sharp_factor = scl_data->sharpness.horz;
	uint32_t v_2tap_sharp_factor = scl_data->sharpness.vert;
	bool coef_ram_current;
	const uint16_t *filter_h = NULL;
	const uint16_t *filter_v = NULL;
	const uint16_t *filter_h_c = NULL;
	const uint16_t *filter_v_c = NULL;

	h_2tap_hardcode_coef_en = scl_data->taps.h_taps < 3
					&& scl_data->taps.h_taps_c < 3
		&& (scl_data->taps.h_taps > 1 && scl_data->taps.h_taps_c > 1);
	v_2tap_hardcode_coef_en = scl_data->taps.v_taps < 3
					&& scl_data->taps.v_taps_c < 3
		&& (scl_data->taps.v_taps > 1 && scl_data->taps.v_taps_c > 1);

	h_2tap_sharp_en = h_2tap_hardcode_coef_en && h_2tap_sharp_factor != 0;
	v_2tap_sharp_en = v_2tap_hardcode_coef_en && v_2tap_sharp_factor != 0;

	REG_UPDATE_6(DSCL_2TAP_CONTROL,
		SCL_H_2TAP_HARDCODE_COEF_EN, h_2tap_hardcode_coef_en,
		SCL_H_2TAP_SHARP_EN, h_2tap_sharp_en,
		SCL_H_2TAP_SHARP_FACTOR, h_2tap_sharp_factor,
		SCL_V_2TAP_HARDCODE_COEF_EN, v_2tap_hardcode_coef_en,
		SCL_V_2TAP_SHARP_EN, v_2tap_sharp_en,
		SCL_V_2TAP_SHARP_FACTOR, v_2tap_sharp_factor);

	if (!v_2tap_hardcode_coef_en || !h_2tap_hardcode_coef_en) {
		bool filter_updated = false;

		filter_h = dpp1_dscl_get_filter_coeffs_64p(
				scl_data->taps.h_taps, scl_data->ratios.horz);
		filter_v = dpp1_dscl_get_filter_coeffs_64p(
				scl_data->taps.v_taps, scl_data->ratios.vert);

		filter_updated = (filter_h && (filter_h != dpp->filter_h))
				|| (filter_v && (filter_v != dpp->filter_v));

		if (chroma_coef_mode) {
			filter_h_c = dpp1_dscl_get_filter_coeffs_64p(
					scl_data->taps.h_taps_c, scl_data->ratios.horz_c);
			filter_v_c = dpp1_dscl_get_filter_coeffs_64p(
					scl_data->taps.v_taps_c, scl_data->ratios.vert_c);
			filter_updated = filter_updated || (filter_h_c && (filter_h_c != dpp->filter_h_c))
							|| (filter_v_c && (filter_v_c != dpp->filter_v_c));
		}

		if (filter_updated) {
			uint32_t scl_mode = REG_READ(SCL_MODE);

			if (!h_2tap_hardcode_coef_en && filter_h) {
				dpp1_dscl_set_scaler_filter(
					dpp, scl_data->taps.h_taps,
					SCL_COEF_LUMA_HORZ_FILTER, filter_h);
			}
			dpp->filter_h = filter_h;
			if (!v_2tap_hardcode_coef_en && filter_v) {
				dpp1_dscl_set_scaler_filter(
					dpp, scl_data->taps.v_taps,
					SCL_COEF_LUMA_VERT_FILTER, filter_v);
			}
			dpp->filter_v = filter_v;
			if (chroma_coef_mode) {
				if (!h_2tap_hardcode_coef_en && filter_h_c) {
					dpp1_dscl_set_scaler_filter(
						dpp, scl_data->taps.h_taps_c,
						SCL_COEF_CHROMA_HORZ_FILTER, filter_h_c);
				}
				if (!v_2tap_hardcode_coef_en && filter_v_c) {
					dpp1_dscl_set_scaler_filter(
						dpp, scl_data->taps.v_taps_c,
						SCL_COEF_CHROMA_VERT_FILTER, filter_v_c);
				}
			}
			dpp->filter_h_c = filter_h_c;
			dpp->filter_v_c = filter_v_c;

			coef_ram_current = get_reg_field_value_ex(
				scl_mode, dpp->tf_mask->SCL_COEF_RAM_SELECT_CURRENT,
				dpp->tf_shift->SCL_COEF_RAM_SELECT_CURRENT);

			/* Swap coefficient RAM and set chroma coefficient mode */
			REG_SET_2(SCL_MODE, scl_mode,
					SCL_COEF_RAM_SELECT, !coef_ram_current,
					SCL_CHROMA_COEF_MODE, chroma_coef_mode);
		}
	}
}