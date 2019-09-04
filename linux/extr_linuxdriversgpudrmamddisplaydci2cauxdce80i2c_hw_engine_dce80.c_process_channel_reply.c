#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct i2c_reply_transaction_data {int length; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct i2c_engine {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DATA ; 
 int /*<<< orphan*/  DC_I2C_DATA_RW ; 
 int /*<<< orphan*/  DC_I2C_INDEX ; 
 int /*<<< orphan*/  DC_I2C_INDEX_WRITE ; 
 int dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_reg_field_value (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDC_I2C_DATA ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_channel_reply(
	struct i2c_engine *engine,
	struct i2c_reply_transaction_data *reply)
{
	uint32_t length = reply->length;
	uint8_t *buffer = reply->data;

	uint32_t value = 0;

	/*set index*/
	set_reg_field_value(
		value,
		length - 1,
		DC_I2C_DATA,
		DC_I2C_INDEX);

	set_reg_field_value(
		value,
		1,
		DC_I2C_DATA,
		DC_I2C_DATA_RW);

	set_reg_field_value(
		value,
		1,
		DC_I2C_DATA,
		DC_I2C_INDEX_WRITE);

	dm_write_reg(engine->base.ctx, mmDC_I2C_DATA, value);

	while (length) {
		/* after reading the status,
		 * if the I2C operation executed successfully
		 * (i.e. DC_I2C_STATUS_DONE = 1) then the I2C controller
		 * should read data bytes from I2C circular data buffer */

		value = dm_read_reg(engine->base.ctx, mmDC_I2C_DATA);

		*buffer++ = get_reg_field_value(
				value,
				DC_I2C_DATA,
				DC_I2C_DATA);

		--length;
	}
}