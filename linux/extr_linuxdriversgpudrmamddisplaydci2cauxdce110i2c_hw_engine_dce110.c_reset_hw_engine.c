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
struct engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_CONTROL ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS_RESET ; 
 struct i2c_hw_engine_dce110* FROM_ENGINE (struct engine*) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void reset_hw_engine(struct engine *engine)
{
	struct i2c_hw_engine_dce110 *hw_engine = FROM_ENGINE(engine);

	REG_UPDATE_2(
			DC_I2C_CONTROL,
			DC_I2C_SW_STATUS_RESET, 1,
			DC_I2C_SW_STATUS_RESET, 1);
}