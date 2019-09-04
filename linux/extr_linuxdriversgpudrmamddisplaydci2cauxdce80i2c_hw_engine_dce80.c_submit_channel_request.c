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
struct i2c_request_transaction_data {int /*<<< orphan*/  status; } ;
struct i2c_engine {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int /*<<< orphan*/  I2C_CHANNEL_OPERATION_ENGINE_BUSY ; 
 int /*<<< orphan*/  I2C_CHANNEL_OPERATION_SUCCEEDED ; 
 int /*<<< orphan*/  execute_transaction (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hw_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_transaction (int /*<<< orphan*/ ,struct i2c_request_transaction_data*) ; 

__attribute__((used)) static void submit_channel_request(
	struct i2c_engine *engine,
	struct i2c_request_transaction_data *request)
{
	request->status = I2C_CHANNEL_OPERATION_SUCCEEDED;

	if (!process_transaction(FROM_I2C_ENGINE(engine), request))
		return;

	if (is_hw_busy(&engine->base)) {
		request->status = I2C_CHANNEL_OPERATION_ENGINE_BUSY;
		return;
	}

	execute_transaction(FROM_I2C_ENGINE(engine));
}