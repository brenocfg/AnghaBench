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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ setup_limit; scalar_t__ send_reset_length; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct i2c_hw_engine_dce110 {TYPE_2__ base; int /*<<< orphan*/  engine_id; } ;
struct i2c_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_ARBITRATION ; 
 int /*<<< orphan*/  DC_I2C_ARBITRATION__DC_I2C_SW_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  DC_I2C_CONTROL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_ENABLE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SETUP ; 
 int /*<<< orphan*/  DC_I2C_DDC1_TIME_LIMIT ; 
 int /*<<< orphan*/  DC_I2C_DDC_SELECT ; 
 int /*<<< orphan*/  DC_I2C_GO ; 
 int /*<<< orphan*/  DC_I2C_NO_QUEUED_SW_GO ; 
 int /*<<< orphan*/  DC_I2C_SEND_RESET ; 
 int /*<<< orphan*/  DC_I2C_SOFT_RESET ; 
 int /*<<< orphan*/  DC_I2C_SW_PRIORITY ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS_RESET ; 
 int /*<<< orphan*/  DC_I2C_TRANSACTION_COUNT ; 
 int /*<<< orphan*/  FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_hw_engine_dce110* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 scalar_t__ I2C_SETUP_TIME_LIMIT_DCE ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SETUP ; 

__attribute__((used)) static bool setup_engine(
	struct i2c_engine *i2c_engine)
{
	struct i2c_hw_engine_dce110 *hw_engine = FROM_I2C_ENGINE(i2c_engine);
	uint32_t i2c_setup_limit = I2C_SETUP_TIME_LIMIT_DCE;
	uint32_t  reset_length = 0;

	if (hw_engine->base.base.setup_limit != 0)
		i2c_setup_limit = hw_engine->base.base.setup_limit;

	/* Program pin select */
	REG_UPDATE_6(
			DC_I2C_CONTROL,
			DC_I2C_GO, 0,
			DC_I2C_SOFT_RESET, 0,
			DC_I2C_SEND_RESET, 0,
			DC_I2C_SW_STATUS_RESET, 1,
			DC_I2C_TRANSACTION_COUNT, 0,
			DC_I2C_DDC_SELECT, hw_engine->engine_id);

	/* Program time limit */
	if (hw_engine->base.base.send_reset_length == 0) {
		/*pre-dcn*/
		REG_UPDATE_N(
				SETUP, 2,
				FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_TIME_LIMIT), i2c_setup_limit,
				FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABLE), 1);
	} else {
		reset_length = hw_engine->base.base.send_reset_length;
	}
	/* Program HW priority
	 * set to High - interrupt software I2C at any time
	 * Enable restart of SW I2C that was interrupted by HW
	 * disable queuing of software while I2C is in use by HW */
	REG_UPDATE_2(
			DC_I2C_ARBITRATION,
			DC_I2C_NO_QUEUED_SW_GO, 0,
			DC_I2C_SW_PRIORITY, DC_I2C_ARBITRATION__DC_I2C_SW_PRIORITY_NORMAL);

	return true;
}