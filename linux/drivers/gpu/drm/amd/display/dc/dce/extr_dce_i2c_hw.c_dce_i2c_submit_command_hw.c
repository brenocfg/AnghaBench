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
typedef  int uint8_t ;
struct resource_pool {int i2c_hw_buffer_in_use; } ;
struct i2c_payload {int dummy; } ;
struct i2c_command {int number_of_payloads; struct i2c_payload* payloads; int /*<<< orphan*/  speed; } ;
struct ddc {int dummy; } ;
struct dce_i2c_hw {int /*<<< orphan*/ * ddc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_ddc_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dce_i2c_hw_engine_submit_payload (struct dce_i2c_hw*,struct i2c_payload*,int) ; 
 int /*<<< orphan*/  release_engine (struct dce_i2c_hw*) ; 
 int /*<<< orphan*/  set_speed (struct dce_i2c_hw*,int /*<<< orphan*/ ) ; 

bool dce_i2c_submit_command_hw(
	struct resource_pool *pool,
	struct ddc *ddc,
	struct i2c_command *cmd,
	struct dce_i2c_hw *dce_i2c_hw)
{
	uint8_t index_of_payload = 0;
	bool result;

	set_speed(dce_i2c_hw, cmd->speed);

	result = true;

	while (index_of_payload < cmd->number_of_payloads) {
		bool mot = (index_of_payload != cmd->number_of_payloads - 1);

		struct i2c_payload *payload = cmd->payloads + index_of_payload;

		if (!dce_i2c_hw_engine_submit_payload(
				dce_i2c_hw, payload, mot)) {
			result = false;
			break;
		}



		++index_of_payload;
	}

	pool->i2c_hw_buffer_in_use = false;

	release_engine(dce_i2c_hw);
	dal_ddc_close(dce_i2c_hw->ddc);

	dce_i2c_hw->ddc = NULL;

	return result;
}