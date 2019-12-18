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
typedef  int uint32_t ;
struct dce_i2c_hw {int /*<<< orphan*/  engine_keep_power_up_count; int /*<<< orphan*/  original_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_ARBITRATION ; 
 int /*<<< orphan*/  DC_I2C_CONTROL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_ENABLE ; 
 int /*<<< orphan*/  DC_I2C_SOFT_RESET ; 
 int /*<<< orphan*/  DC_I2C_SW_DONE_USING_I2C_REG ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS_RESET ; 
 int /*<<< orphan*/  DC_I2C_SW_USE_I2C_REG_REQ ; 
 int /*<<< orphan*/  FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  set_speed (struct dce_i2c_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_engine(
	struct dce_i2c_hw *dce_i2c_hw)
{
	bool safe_to_reset;

	/* Restore original HW engine speed */

	set_speed(dce_i2c_hw, dce_i2c_hw->original_speed);


	/* Reset HW engine */
	{
		uint32_t i2c_sw_status = 0;

		REG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
		/* if used by SW, safe to reset */
		safe_to_reset = (i2c_sw_status == 1);
	}

	if (safe_to_reset)
		REG_UPDATE_2(DC_I2C_CONTROL,
			     DC_I2C_SOFT_RESET, 1,
			     DC_I2C_SW_STATUS_RESET, 1);
	else
		REG_UPDATE(DC_I2C_CONTROL, DC_I2C_SW_STATUS_RESET, 1);
	/* HW I2c engine - clock gating feature */
	if (!dce_i2c_hw->engine_keep_power_up_count)
		REG_UPDATE_N(SETUP, 1, FN(SETUP, DC_I2C_DDC1_ENABLE), 0);
	/* Release I2C after reset, so HW or DMCU could use it */
	REG_UPDATE_2(DC_I2C_ARBITRATION, DC_I2C_SW_DONE_USING_I2C_REG, 1,
		DC_I2C_SW_USE_I2C_REG_REQ, 0);

}