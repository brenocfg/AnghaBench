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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct i2c_payload {int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct dce_i2c_hw {int /*<<< orphan*/  buffer_used_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DATA ; 
 int /*<<< orphan*/  DC_I2C_DATA_RW ; 
 int /*<<< orphan*/  DC_I2C_INDEX ; 
 int /*<<< orphan*/  DC_I2C_INDEX_WRITE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void process_channel_reply(
	struct dce_i2c_hw *dce_i2c_hw,
	struct i2c_payload *reply)
{
	uint32_t length = reply->length;
	uint8_t *buffer = reply->data;

	REG_SET_3(DC_I2C_DATA, 0,
		 DC_I2C_INDEX, dce_i2c_hw->buffer_used_write,
		 DC_I2C_DATA_RW, 1,
		 DC_I2C_INDEX_WRITE, 1);

	while (length) {
		/* after reading the status,
		 * if the I2C operation executed successfully
		 * (i.e. DC_I2C_STATUS_DONE = 1) then the I2C controller
		 * should read data bytes from I2C circular data buffer
		 */

		uint32_t i2c_data;

		REG_GET(DC_I2C_DATA, DC_I2C_DATA, &i2c_data);
		*buffer++ = i2c_data;

		--length;
	}
}