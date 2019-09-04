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
typedef  int uint32_t ;
struct i2c_hw_engine_dce110 {int reference_frequency; TYPE_1__* i2c_mask; } ;
struct i2c_engine {int dummy; } ;
struct TYPE_2__ {scalar_t__ DC_I2C_DDC1_START_STOP_TIMING_CNTL; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DDC1_PRESCALE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SPEED ; 
 int /*<<< orphan*/  DC_I2C_DDC1_START_STOP_TIMING_CNTL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_THRESHOLD ; 
 int /*<<< orphan*/  FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_hw_engine_dce110* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int /*<<< orphan*/  REG_UPDATE_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  SPEED ; 

__attribute__((used)) static void set_speed(
	struct i2c_engine *i2c_engine,
	uint32_t speed)
{
	struct i2c_hw_engine_dce110 *hw_engine = FROM_I2C_ENGINE(i2c_engine);

	if (speed) {
		if (hw_engine->i2c_mask->DC_I2C_DDC1_START_STOP_TIMING_CNTL)
			REG_UPDATE_N(
				SPEED, 3,
				FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PRESCALE), hw_engine->reference_frequency / speed,
				FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THRESHOLD), 2,
				FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_START_STOP_TIMING_CNTL), speed > 50 ? 2:1);
		else
			REG_UPDATE_N(
				SPEED, 2,
				FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PRESCALE), hw_engine->reference_frequency / speed,
				FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THRESHOLD), 2);
	}
}