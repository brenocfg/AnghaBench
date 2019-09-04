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
struct engine {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_CONTROL ; 
 int /*<<< orphan*/  DC_I2C_SOFT_RESET ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS_RESET ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDC_I2C_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reset_hw_engine(struct engine *engine)
{
	uint32_t value = dm_read_reg(engine->ctx, mmDC_I2C_CONTROL);

	set_reg_field_value(
		value,
		1,
		DC_I2C_CONTROL,
		DC_I2C_SOFT_RESET);

	set_reg_field_value(
		value,
		1,
		DC_I2C_CONTROL,
		DC_I2C_SW_STATUS_RESET);

	dm_write_reg(engine->ctx, mmDC_I2C_CONTROL, value);
}