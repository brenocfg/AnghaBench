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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int h_taps; int v_taps; int h_taps_c; int v_taps_c; } ;
struct scaler_data {scalar_t__ format; TYPE_2__ taps; } ;
struct TYPE_3__ {struct dc_context* ctx; } ;
struct dce_transform {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ PIXEL_FORMAT_420BPP8 ; 
 int /*<<< orphan*/  SCLV_CONTROL ; 
 int /*<<< orphan*/  SCLV_MODE ; 
 int /*<<< orphan*/  SCLV_TAP_CONTROL ; 
 int /*<<< orphan*/  SCL_BOUNDARY_MODE ; 
 int /*<<< orphan*/  SCL_H_NUM_OF_TAPS ; 
 int /*<<< orphan*/  SCL_H_NUM_OF_TAPS_C ; 
 int /*<<< orphan*/  SCL_MODE ; 
 int /*<<< orphan*/  SCL_MODE_C ; 
 int /*<<< orphan*/  SCL_PSCL_EN ; 
 int /*<<< orphan*/  SCL_PSCL_EN_C ; 
 int /*<<< orphan*/  SCL_V_NUM_OF_TAPS ; 
 int /*<<< orphan*/  SCL_V_NUM_OF_TAPS_C ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/ ,scalar_t__) ; 
 int get_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSCLV_CONTROL ; 
 int /*<<< orphan*/  mmSCLV_MODE ; 
 int /*<<< orphan*/  mmSCLV_TAP_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool setup_scaling_configuration(
	struct dce_transform *xfm_dce,
	const struct scaler_data *data)
{
	bool is_scaling_needed = false;
	struct dc_context *ctx = xfm_dce->base.ctx;
	uint32_t value = 0;

	set_reg_field_value(value, data->taps.h_taps - 1,
			SCLV_TAP_CONTROL, SCL_H_NUM_OF_TAPS);
	set_reg_field_value(value, data->taps.v_taps - 1,
			SCLV_TAP_CONTROL, SCL_V_NUM_OF_TAPS);
	set_reg_field_value(value, data->taps.h_taps_c - 1,
			SCLV_TAP_CONTROL, SCL_H_NUM_OF_TAPS_C);
	set_reg_field_value(value, data->taps.v_taps_c - 1,
			SCLV_TAP_CONTROL, SCL_V_NUM_OF_TAPS_C);
	dm_write_reg(ctx, mmSCLV_TAP_CONTROL, value);

	value = 0;
	if (data->taps.h_taps + data->taps.v_taps > 2) {
		set_reg_field_value(value, 1, SCLV_MODE, SCL_MODE);
		set_reg_field_value(value, 1, SCLV_MODE, SCL_PSCL_EN);
		is_scaling_needed = true;
	} else {
		set_reg_field_value(value, 0, SCLV_MODE, SCL_MODE);
		set_reg_field_value(value, 0, SCLV_MODE, SCL_PSCL_EN);
	}

	if (data->taps.h_taps_c + data->taps.v_taps_c > 2) {
		set_reg_field_value(value, 1, SCLV_MODE, SCL_MODE_C);
		set_reg_field_value(value, 1, SCLV_MODE, SCL_PSCL_EN_C);
		is_scaling_needed = true;
	} else if (data->format != PIXEL_FORMAT_420BPP8) {
		set_reg_field_value(
			value,
			get_reg_field_value(value, SCLV_MODE, SCL_MODE),
			SCLV_MODE,
			SCL_MODE_C);
		set_reg_field_value(
			value,
			get_reg_field_value(value, SCLV_MODE, SCL_PSCL_EN),
			SCLV_MODE,
			SCL_PSCL_EN_C);
	} else {
		set_reg_field_value(value, 0, SCLV_MODE, SCL_MODE_C);
		set_reg_field_value(value, 0, SCLV_MODE, SCL_PSCL_EN_C);
	}
	dm_write_reg(ctx, mmSCLV_MODE, value);

	value = 0;
	/*
	 * 0 - Replaced out of bound pixels with black pixel
	 * (or any other required color)
	 * 1 - Replaced out of bound pixels with the edge pixel
	 */
	set_reg_field_value(value, 1, SCLV_CONTROL, SCL_BOUNDARY_MODE);
	dm_write_reg(ctx, mmSCLV_CONTROL, value);

	return is_scaling_needed;
}