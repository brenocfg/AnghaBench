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
struct i2c_hw_engine_dce110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DDC1_ENABLE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SETUP ; 
 int /*<<< orphan*/  FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP ; 

__attribute__((used)) static void disable_i2c_hw_engine(
	struct i2c_hw_engine_dce110 *hw_engine)
{
	REG_UPDATE_N(SETUP, 1, FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABLE), 0);
}