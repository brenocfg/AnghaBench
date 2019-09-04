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
typedef  unsigned int uint32_t ;
struct i2caux {int /*<<< orphan*/ * aux_engines; int /*<<< orphan*/  aux_timeout_period; TYPE_1__** i2c_hw_engines; int /*<<< orphan*/  default_i2c_hw_speed; int /*<<< orphan*/ * i2c_sw_engines; int /*<<< orphan*/  default_i2c_sw_speed; int /*<<< orphan*/ * funcs; } ;
struct i2caux_dce110 {int i2c_hw_buffer_in_use; struct i2caux base; } ;
struct i2c_sw_engine_dce110_create_arg {unsigned int engine_id; struct dc_context* ctx; int /*<<< orphan*/  default_speed; } ;
struct i2c_hw_engine_dce110_create_arg {unsigned int engine_id; unsigned int reference_frequency; struct dce110_i2c_hw_engine_mask const* i2c_mask; struct dce110_i2c_hw_engine_shift const* i2c_shift; struct dce110_i2c_hw_engine_registers const* regs; struct dc_context* ctx; int /*<<< orphan*/  default_speed; } ;
struct dce110_i2c_hw_engine_shift {int dummy; } ;
struct dce110_i2c_hw_engine_registers {int dummy; } ;
struct dce110_i2c_hw_engine_mask {int dummy; } ;
struct dce110_aux_registers {int dummy; } ;
struct dc_context {int dce_version; int /*<<< orphan*/  dc_bios; } ;
struct aux_engine_dce110_init_data {unsigned int engine_id; struct dce110_aux_registers const* regs; struct dc_context* ctx; int /*<<< orphan*/  timeout_period; } ;
typedef  enum gpio_ddc_line { ____Placeholder_gpio_ddc_line } gpio_ddc_line ;
struct TYPE_2__ {int /*<<< orphan*/  send_reset_length; int /*<<< orphan*/  setup_limit; } ;

/* Variables and functions */
#define  DCN_VERSION_1_0 128 
 int /*<<< orphan*/  I2C_SETUP_TIME_LIMIT_DCE ; 
 int /*<<< orphan*/  I2C_SETUP_TIME_LIMIT_DCN ; 
 int /*<<< orphan*/  dal_aux_engine_dce110_create (struct aux_engine_dce110_init_data*) ; 
 TYPE_1__* dal_i2c_hw_engine_dce110_create (struct i2c_hw_engine_dce110_create_arg*) ; 
 int /*<<< orphan*/  dal_i2c_sw_engine_dce110_create (struct i2c_sw_engine_dce110_create_arg*) ; 
 int /*<<< orphan*/  dal_i2caux_construct (struct i2caux*,struct dc_context*) ; 
 int dal_i2caux_get_reference_clock (int /*<<< orphan*/ ) ; 
 int* hw_aux_lines ; 
 int* hw_ddc_lines ; 
 int /*<<< orphan*/  i2caux_funcs ; 

void dal_i2caux_dce110_construct(
	struct i2caux_dce110 *i2caux_dce110,
	struct dc_context *ctx,
	unsigned int num_i2caux_inst,
	const struct dce110_aux_registers aux_regs[],
	const struct dce110_i2c_hw_engine_registers i2c_hw_engine_regs[],
	const struct dce110_i2c_hw_engine_shift *i2c_shift,
	const struct dce110_i2c_hw_engine_mask *i2c_mask)
{
	uint32_t i = 0;
	uint32_t reference_frequency = 0;
	bool use_i2c_sw_engine = false;
	struct i2caux *base = NULL;
	/*TODO: For CZ bring up, if dal_i2caux_get_reference_clock
	 * does not return 48KHz, we need hard coded for 48Khz.
	 * Some BIOS setting incorrect cause this
	 * For production, we always get value from BIOS*/
	reference_frequency =
		dal_i2caux_get_reference_clock(ctx->dc_bios) >> 1;

	base = &i2caux_dce110->base;

	dal_i2caux_construct(base, ctx);

	i2caux_dce110->base.funcs = &i2caux_funcs;
	i2caux_dce110->i2c_hw_buffer_in_use = false;
	/* Create I2C engines (DDC lines per connector)
	 * different I2C/AUX usage cases, DDC, Generic GPIO, AUX.
	 */
	do {
		enum gpio_ddc_line line_id = hw_ddc_lines[i];

		struct i2c_hw_engine_dce110_create_arg hw_arg_dce110;

		if (use_i2c_sw_engine) {
			struct i2c_sw_engine_dce110_create_arg sw_arg;

			sw_arg.engine_id = i;
			sw_arg.default_speed = base->default_i2c_sw_speed;
			sw_arg.ctx = ctx;
			base->i2c_sw_engines[line_id] =
				dal_i2c_sw_engine_dce110_create(&sw_arg);
		}

		hw_arg_dce110.engine_id = i;
		hw_arg_dce110.reference_frequency = reference_frequency;
		hw_arg_dce110.default_speed = base->default_i2c_hw_speed;
		hw_arg_dce110.ctx = ctx;
		hw_arg_dce110.regs = &i2c_hw_engine_regs[i];
		hw_arg_dce110.i2c_shift = i2c_shift;
		hw_arg_dce110.i2c_mask = i2c_mask;

		base->i2c_hw_engines[line_id] =
			dal_i2c_hw_engine_dce110_create(&hw_arg_dce110);
		if (base->i2c_hw_engines[line_id] != NULL) {
			switch (ctx->dce_version) {
			case DCN_VERSION_1_0:
				base->i2c_hw_engines[line_id]->setup_limit =
					I2C_SETUP_TIME_LIMIT_DCN;
				base->i2c_hw_engines[line_id]->send_reset_length  = 0;
			break;
			default:
				base->i2c_hw_engines[line_id]->setup_limit =
					I2C_SETUP_TIME_LIMIT_DCE;
				base->i2c_hw_engines[line_id]->send_reset_length  = 0;
				break;
			}
		}
		++i;
	} while (i < num_i2caux_inst);

	/* Create AUX engines for all lines which has assisted HW AUX
	 * 'i' (loop counter) used as DDC/AUX engine_id */

	i = 0;

	do {
		enum gpio_ddc_line line_id = hw_aux_lines[i];

		struct aux_engine_dce110_init_data aux_init_data;

		aux_init_data.engine_id = i;
		aux_init_data.timeout_period = base->aux_timeout_period;
		aux_init_data.ctx = ctx;
		aux_init_data.regs = &aux_regs[i];

		base->aux_engines[line_id] =
			dal_aux_engine_dce110_create(&aux_init_data);

		++i;
	} while (i < num_i2caux_inst);

	/*TODO Generic I2C SW and HW*/
}