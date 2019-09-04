#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {struct dc_context* ctx; } ;
struct TYPE_7__ {TYPE_2__ base; } ;
struct TYPE_8__ {TYPE_3__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  DC_I2C_DDCX_SETUP; } ;
struct i2c_hw_engine_dce80 {TYPE_4__ base; TYPE_1__ addr; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DDC1_ENABLE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SETUP ; 
 int /*<<< orphan*/  dm_read_reg (struct dc_context*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_i2c_hw_engine(
	struct i2c_hw_engine_dce80 *engine)
{
	const uint32_t addr = engine->addr.DC_I2C_DDCX_SETUP;
	uint32_t value = 0;

	struct dc_context *ctx = NULL;

	ctx = engine->base.base.base.ctx;

	value = dm_read_reg(ctx, addr);

	set_reg_field_value(
		value,
		0,
		DC_I2C_DDC1_SETUP,
		DC_I2C_DDC1_ENABLE);

	dm_write_reg(ctx, addr, value);
}