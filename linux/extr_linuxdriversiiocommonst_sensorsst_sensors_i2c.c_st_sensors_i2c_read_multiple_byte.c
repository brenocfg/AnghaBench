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
typedef  int /*<<< orphan*/  u8 ;
struct st_sensor_transfer_buffer {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_SENSORS_I2C_MULTIREAD ; 
 int i2c_smbus_read_i2c_block_data_or_emulated (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static int st_sensors_i2c_read_multiple_byte(
		struct st_sensor_transfer_buffer *tb, struct device *dev,
			u8 reg_addr, int len, u8 *data, bool multiread_bit)
{
	if (multiread_bit)
		reg_addr |= ST_SENSORS_I2C_MULTIREAD;

	return i2c_smbus_read_i2c_block_data_or_emulated(to_i2c_client(dev),
							 reg_addr, len, data);
}