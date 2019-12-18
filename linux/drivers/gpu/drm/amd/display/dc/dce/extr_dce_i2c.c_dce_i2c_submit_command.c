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
struct resource_pool {int dummy; } ;
struct i2c_command {int dummy; } ;
struct ddc {int dummy; } ;
struct dce_i2c_sw {int dummy; } ;
struct dce_i2c_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 struct dce_i2c_hw* acquire_i2c_hw_engine (struct resource_pool*,struct ddc*) ; 
 struct dce_i2c_sw* dce_i2c_acquire_i2c_sw_engine (struct resource_pool*,struct ddc*) ; 
 int dce_i2c_submit_command_hw (struct resource_pool*,struct ddc*,struct i2c_command*,struct dce_i2c_hw*) ; 
 int dce_i2c_submit_command_sw (struct resource_pool*,struct ddc*,struct i2c_command*,struct dce_i2c_sw*) ; 

bool dce_i2c_submit_command(
	struct resource_pool *pool,
	struct ddc *ddc,
	struct i2c_command *cmd)
{
	struct dce_i2c_hw *dce_i2c_hw;
	struct dce_i2c_sw *dce_i2c_sw;

	if (!ddc) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!cmd) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	/* The software engine is only available on dce8 */
	dce_i2c_sw = dce_i2c_acquire_i2c_sw_engine(pool, ddc);

	if (!dce_i2c_sw) {
		dce_i2c_hw = acquire_i2c_hw_engine(pool, ddc);

		if (!dce_i2c_hw)
			return false;

		return dce_i2c_submit_command_hw(pool, ddc, cmd, dce_i2c_hw);
	}

	return dce_i2c_submit_command_sw(pool, ddc, cmd, dce_i2c_sw);

}