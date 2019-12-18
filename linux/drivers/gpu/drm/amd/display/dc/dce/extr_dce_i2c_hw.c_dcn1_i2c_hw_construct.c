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
typedef  int /*<<< orphan*/  uint32_t ;
struct dce_i2c_shift {int dummy; } ;
struct dce_i2c_registers {int dummy; } ;
struct dce_i2c_mask {int dummy; } ;
struct dce_i2c_hw {int /*<<< orphan*/  setup_limit; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_SETUP_TIME_LIMIT_DCN ; 
 int /*<<< orphan*/  dce112_i2c_hw_construct (struct dce_i2c_hw*,struct dc_context*,int /*<<< orphan*/ ,struct dce_i2c_registers const*,struct dce_i2c_shift const*,struct dce_i2c_mask const*) ; 

void dcn1_i2c_hw_construct(
	struct dce_i2c_hw *dce_i2c_hw,
	struct dc_context *ctx,
	uint32_t engine_id,
	const struct dce_i2c_registers *regs,
	const struct dce_i2c_shift *shifts,
	const struct dce_i2c_mask *masks)
{
	dce112_i2c_hw_construct(dce_i2c_hw,
			ctx,
			engine_id,
			regs,
			shifts,
			masks);
	dce_i2c_hw->setup_limit = I2C_SETUP_TIME_LIMIT_DCN;
}