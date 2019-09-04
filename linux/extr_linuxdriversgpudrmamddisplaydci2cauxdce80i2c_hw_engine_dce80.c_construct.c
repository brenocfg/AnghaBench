#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_hw_engine_dce80_create_arg {size_t engine_id; int /*<<< orphan*/  reference_frequency; int /*<<< orphan*/  default_speed; int /*<<< orphan*/  ctx; } ;
struct TYPE_7__ {scalar_t__ DC_I2C_DDCX_SPEED; scalar_t__ DC_I2C_DDCX_SETUP; } ;
struct TYPE_5__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/ * funcs; TYPE_1__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  default_speed; int /*<<< orphan*/ * funcs; TYPE_2__ base; } ;
struct i2c_hw_engine_dce80 {size_t engine_id; int engine_keep_power_up_count; scalar_t__ transaction_count; scalar_t__ buffer_used_bytes; int /*<<< orphan*/  reference_frequency; TYPE_3__ addr; TYPE_4__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_i2c_hw_engine_construct (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__* ddc_setup_offset ; 
 scalar_t__* ddc_speed_offset ; 
 int /*<<< orphan*/  engine_funcs ; 
 int /*<<< orphan*/  i2c_engine_funcs ; 
 int /*<<< orphan*/  i2c_hw_engine_funcs ; 
 scalar_t__ mmDC_I2C_DDC1_SETUP ; 
 scalar_t__ mmDC_I2C_DDC1_SPEED ; 

__attribute__((used)) static void construct(
	struct i2c_hw_engine_dce80 *engine,
	const struct i2c_hw_engine_dce80_create_arg *arg)
{
	dal_i2c_hw_engine_construct(&engine->base, arg->ctx);

	engine->base.base.base.funcs = &engine_funcs;
	engine->base.base.funcs = &i2c_engine_funcs;
	engine->base.funcs = &i2c_hw_engine_funcs;
	engine->base.default_speed = arg->default_speed;
	engine->addr.DC_I2C_DDCX_SETUP =
		mmDC_I2C_DDC1_SETUP + ddc_setup_offset[arg->engine_id];
	engine->addr.DC_I2C_DDCX_SPEED =
		mmDC_I2C_DDC1_SPEED + ddc_speed_offset[arg->engine_id];

	engine->engine_id = arg->engine_id;
	engine->reference_frequency = arg->reference_frequency;
	engine->buffer_used_bytes = 0;
	engine->transaction_count = 0;
	engine->engine_keep_power_up_count = 1;
}