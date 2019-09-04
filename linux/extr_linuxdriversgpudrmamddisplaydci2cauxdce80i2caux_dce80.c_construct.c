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
typedef  size_t uint32_t ;
struct i2caux {int /*<<< orphan*/ * aux_engines; int /*<<< orphan*/  aux_timeout_period; int /*<<< orphan*/ * i2c_hw_engines; int /*<<< orphan*/  default_i2c_hw_speed; int /*<<< orphan*/ * i2c_sw_engines; int /*<<< orphan*/  default_i2c_sw_speed; int /*<<< orphan*/ * funcs; } ;
struct i2caux_dce80 {int i2c_hw_buffer_in_use; struct i2caux base; } ;
struct i2c_sw_engine_dce80_create_arg {size_t engine_id; struct dc_context* ctx; int /*<<< orphan*/  default_speed; } ;
struct i2c_hw_engine_dce80_create_arg {size_t engine_id; size_t reference_frequency; struct dc_context* ctx; int /*<<< orphan*/  default_speed; } ;
struct dc_context {int /*<<< orphan*/  dc_bios; } ;
struct aux_engine_dce110_init_data {size_t engine_id; int /*<<< orphan*/ * regs; struct dc_context* ctx; int /*<<< orphan*/  timeout_period; } ;
typedef  enum gpio_ddc_line { ____Placeholder_gpio_ddc_line } gpio_ddc_line ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  dal_aux_engine_dce110_create (struct aux_engine_dce110_init_data*) ; 
 int /*<<< orphan*/  dal_i2c_hw_engine_dce80_create (struct i2c_hw_engine_dce80_create_arg*) ; 
 int /*<<< orphan*/  dal_i2c_sw_engine_dce80_create (struct i2c_sw_engine_dce80_create_arg*) ; 
 int /*<<< orphan*/  dal_i2caux_construct (struct i2caux*,struct dc_context*) ; 
 int dal_i2caux_get_reference_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dce80_aux_regs ; 
 int* hw_aux_lines ; 
 int* hw_ddc_lines ; 
 int /*<<< orphan*/  i2caux_funcs ; 

__attribute__((used)) static void construct(
	struct i2caux_dce80 *i2caux_dce80,
	struct dc_context *ctx)
{
	/* Entire family have I2C engine reference clock frequency
	 * changed from XTALIN (27) to XTALIN/2 (13.5) */

	struct i2caux *base = &i2caux_dce80->base;

	uint32_t reference_frequency =
		dal_i2caux_get_reference_clock(ctx->dc_bios) >> 1;

	/*bool use_i2c_sw_engine = dal_adapter_service_is_feature_supported(as,
		FEATURE_RESTORE_USAGE_I2C_SW_ENGINE);*/

	/* Use SWI2C for dce8 currently, sicne we have bug with hwi2c */
	bool use_i2c_sw_engine = true;

	uint32_t i;

	dal_i2caux_construct(base, ctx);

	i2caux_dce80->base.funcs = &i2caux_funcs;
	i2caux_dce80->i2c_hw_buffer_in_use = false;

	/* Create I2C HW engines (HW + SW pairs)
	 * for all lines which has assisted HW DDC
	 * 'i' (loop counter) used as DDC/AUX engine_id */

	i = 0;

	do {
		enum gpio_ddc_line line_id = hw_ddc_lines[i];

		struct i2c_hw_engine_dce80_create_arg hw_arg;

		if (use_i2c_sw_engine) {
			struct i2c_sw_engine_dce80_create_arg sw_arg;

			sw_arg.engine_id = i;
			sw_arg.default_speed = base->default_i2c_sw_speed;
			sw_arg.ctx = ctx;
			base->i2c_sw_engines[line_id] =
				dal_i2c_sw_engine_dce80_create(&sw_arg);
		}

		hw_arg.engine_id = i;
		hw_arg.reference_frequency = reference_frequency;
		hw_arg.default_speed = base->default_i2c_hw_speed;
		hw_arg.ctx = ctx;

		base->i2c_hw_engines[line_id] =
			dal_i2c_hw_engine_dce80_create(&hw_arg);

		++i;
	} while (i < ARRAY_SIZE(hw_ddc_lines));

	/* Create AUX engines for all lines which has assisted HW AUX
	 * 'i' (loop counter) used as DDC/AUX engine_id */

	i = 0;

	do {
		enum gpio_ddc_line line_id = hw_aux_lines[i];

		struct aux_engine_dce110_init_data arg;

		arg.engine_id = i;
		arg.timeout_period = base->aux_timeout_period;
		arg.ctx = ctx;
		arg.regs = &dce80_aux_regs[i];

		base->aux_engines[line_id] =
			dal_aux_engine_dce110_create(&arg);

		++i;
	} while (i < ARRAY_SIZE(hw_aux_lines));

	/* TODO Generic I2C SW and HW */
}