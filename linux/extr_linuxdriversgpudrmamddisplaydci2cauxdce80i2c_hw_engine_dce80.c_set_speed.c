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
typedef  int uint32_t ;
struct TYPE_3__ {int DC_I2C_DDCX_SPEED; } ;
struct i2c_hw_engine_dce80 {int reference_frequency; TYPE_1__ addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
struct i2c_engine {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DDC1_PRESCALE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SPEED ; 
 int /*<<< orphan*/  DC_I2C_DDC1_THRESHOLD ; 
 struct i2c_hw_engine_dce80* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int dm_read_reg (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_speed(
	struct i2c_engine *i2c_engine,
	uint32_t speed)
{
	struct i2c_hw_engine_dce80 *engine = FROM_I2C_ENGINE(i2c_engine);

	if (speed) {
		const uint32_t addr = engine->addr.DC_I2C_DDCX_SPEED;

		uint32_t value = dm_read_reg(i2c_engine->base.ctx, addr);

		set_reg_field_value(
			value,
			engine->reference_frequency / speed,
			DC_I2C_DDC1_SPEED,
			DC_I2C_DDC1_PRESCALE);

		set_reg_field_value(
			value,
			2,
			DC_I2C_DDC1_SPEED,
			DC_I2C_DDC1_THRESHOLD);

		dm_write_reg(i2c_engine->base.ctx, addr, value);
	}
}