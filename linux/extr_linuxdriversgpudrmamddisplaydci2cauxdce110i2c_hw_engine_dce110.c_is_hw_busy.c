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
typedef  scalar_t__ uint32_t ;
struct i2c_hw_engine_dce110 {int dummy; } ;
struct engine {int dummy; } ;

/* Variables and functions */
 scalar_t__ DC_I2C_STATUS__DC_I2C_STATUS_IDLE ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS ; 
 struct i2c_hw_engine_dce110* FROM_ENGINE (struct engine*) ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  reset_hw_engine (struct engine*) ; 

__attribute__((used)) static bool is_hw_busy(struct engine *engine)
{
	struct i2c_hw_engine_dce110 *hw_engine = FROM_ENGINE(engine);
	uint32_t i2c_sw_status = 0;

	REG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
	if (i2c_sw_status == DC_I2C_STATUS__DC_I2C_STATUS_IDLE)
		return false;

	reset_hw_engine(engine);

	REG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
	return i2c_sw_status != DC_I2C_STATUS__DC_I2C_STATUS_IDLE;
}