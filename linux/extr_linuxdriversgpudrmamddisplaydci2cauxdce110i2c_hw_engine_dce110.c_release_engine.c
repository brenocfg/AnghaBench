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
struct i2c_engine {TYPE_2__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  original_speed; struct i2c_engine base; } ;
struct i2c_hw_engine_dce110 {int /*<<< orphan*/  engine_keep_power_up_count; TYPE_1__ base; } ;
struct engine {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_speed ) (struct i2c_engine*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_ARBITRATION ; 
 int /*<<< orphan*/  DC_I2C_CONTROL ; 
 int /*<<< orphan*/  DC_I2C_SOFT_RESET ; 
 int /*<<< orphan*/  DC_I2C_SW_DONE_USING_I2C_REG ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS_RESET ; 
 struct i2c_hw_engine_dce110* FROM_ENGINE (struct engine*) ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_i2c_hw_engine (struct i2c_hw_engine_dce110*) ; 
 int /*<<< orphan*/  stub1 (struct i2c_engine*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_engine(
	struct engine *engine)
{
	struct i2c_hw_engine_dce110 *hw_engine = FROM_ENGINE(engine);

	struct i2c_engine *base = NULL;
	bool safe_to_reset;

	base = &hw_engine->base.base;

	/* Restore original HW engine speed */

	base->funcs->set_speed(base, hw_engine->base.original_speed);

	/* Release I2C */
	REG_UPDATE(DC_I2C_ARBITRATION, DC_I2C_SW_DONE_USING_I2C_REG, 1);

	/* Reset HW engine */
	{
		uint32_t i2c_sw_status = 0;
		REG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
		/* if used by SW, safe to reset */
		safe_to_reset = (i2c_sw_status == 1);
	}

	if (safe_to_reset)
		REG_UPDATE_2(
			DC_I2C_CONTROL,
			DC_I2C_SOFT_RESET, 1,
			DC_I2C_SW_STATUS_RESET, 1);
	else
		REG_UPDATE(DC_I2C_CONTROL, DC_I2C_SW_STATUS_RESET, 1);

	/* HW I2c engine - clock gating feature */
	if (!hw_engine->engine_keep_power_up_count)
		disable_i2c_hw_engine(hw_engine);
}