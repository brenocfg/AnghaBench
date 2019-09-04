#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int default_speed; } ;
struct TYPE_4__ {int DC_I2C_DDCX_SPEED; } ;
struct i2c_hw_engine_dce80 {int reference_frequency; TYPE_3__ base; TYPE_1__ addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
struct i2c_engine {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DDC1_PRESCALE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SPEED ; 
 struct i2c_hw_engine_dce80* FROM_I2C_ENGINE (struct i2c_engine const*) ; 
 int dm_read_reg (int /*<<< orphan*/ ,int const) ; 
 int get_reg_field_value (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t get_speed(
	const struct i2c_engine *i2c_engine)
{
	const struct i2c_hw_engine_dce80 *engine = FROM_I2C_ENGINE(i2c_engine);

	const uint32_t addr = engine->addr.DC_I2C_DDCX_SPEED;

	uint32_t pre_scale = 0;

	uint32_t value = dm_read_reg(i2c_engine->base.ctx, addr);

	pre_scale = get_reg_field_value(
			value,
			DC_I2C_DDC1_SPEED,
			DC_I2C_DDC1_PRESCALE);

	/* [anaumov] it seems following is unnecessary */
	/*ASSERT(value.bits.DC_I2C_DDC1_PRESCALE);*/

	return pre_scale ?
		engine->reference_frequency / pre_scale :
		engine->base.default_speed;
}