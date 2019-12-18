#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct dce_i2c_shift {int dummy; } ;
struct dce_i2c_registers {int dummy; } ;
struct dce_i2c_mask {int dummy; } ;
struct dce_i2c_hw {int reference_frequency; int engine_keep_power_up_count; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  setup_limit; scalar_t__ send_reset_length; void* default_speed; void* original_speed; scalar_t__ transaction_count; scalar_t__ buffer_used_bytes; struct dce_i2c_mask const* masks; struct dce_i2c_shift const* shifts; struct dce_i2c_registers const* regs; int /*<<< orphan*/  engine_id; struct dc_context* ctx; } ;
struct dc_context {TYPE_3__* dc_bios; } ;
struct TYPE_4__ {int crystal_frequency; } ;
struct TYPE_5__ {TYPE_1__ pll_info; } ;
struct TYPE_6__ {TYPE_2__ fw_info; } ;

/* Variables and functions */
 void* DEFAULT_I2C_HW_SPEED ; 
 int /*<<< orphan*/  I2C_HW_BUFFER_SIZE_DCE ; 
 int /*<<< orphan*/  I2C_SETUP_TIME_LIMIT_DCE ; 

void dce_i2c_hw_construct(
	struct dce_i2c_hw *dce_i2c_hw,
	struct dc_context *ctx,
	uint32_t engine_id,
	const struct dce_i2c_registers *regs,
	const struct dce_i2c_shift *shifts,
	const struct dce_i2c_mask *masks)
{
	dce_i2c_hw->ctx = ctx;
	dce_i2c_hw->engine_id = engine_id;
	dce_i2c_hw->reference_frequency = (ctx->dc_bios->fw_info.pll_info.crystal_frequency) >> 1;
	dce_i2c_hw->regs = regs;
	dce_i2c_hw->shifts = shifts;
	dce_i2c_hw->masks = masks;
	dce_i2c_hw->buffer_used_bytes = 0;
	dce_i2c_hw->transaction_count = 0;
	dce_i2c_hw->engine_keep_power_up_count = 1;
	dce_i2c_hw->original_speed = DEFAULT_I2C_HW_SPEED;
	dce_i2c_hw->default_speed = DEFAULT_I2C_HW_SPEED;
	dce_i2c_hw->send_reset_length = 0;
	dce_i2c_hw->setup_limit = I2C_SETUP_TIME_LIMIT_DCE;
	dce_i2c_hw->buffer_size = I2C_HW_BUFFER_SIZE_DCE;
}