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
struct dce_i2c_hw {int reference_frequency; TYPE_1__* masks; } ;
struct TYPE_2__ {scalar_t__ DC_I2C_DDC1_START_STOP_TIMING_CNTL; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DDC1_PRESCALE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SPEED ; 
 int /*<<< orphan*/  DC_I2C_DDC1_START_STOP_TIMING_CNTL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_THRESHOLD ; 
 int /*<<< orphan*/  FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  SPEED ; 

__attribute__((used)) static void set_speed(
	struct dce_i2c_hw *dce_i2c_hw,
	uint32_t speed)
{

	if (speed) {
		if (dce_i2c_hw->masks->DC_I2C_DDC1_START_STOP_TIMING_CNTL)
			REG_UPDATE_N(SPEED, 3,
				     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PRESCALE), dce_i2c_hw->reference_frequency / speed,
				     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THRESHOLD), 2,
				     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_START_STOP_TIMING_CNTL), speed > 50 ? 2:1);
		else
			REG_UPDATE_N(SPEED, 2,
				     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PRESCALE), dce_i2c_hw->reference_frequency / speed,
				     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THRESHOLD), 2);
	}
}