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
typedef  int u8 ;
struct st_sensor_transfer_buffer {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static int st_sensors_i2c_read_byte(struct st_sensor_transfer_buffer *tb,
				struct device *dev, u8 reg_addr, u8 *res_byte)
{
	int err;

	err = i2c_smbus_read_byte_data(to_i2c_client(dev), reg_addr);
	if (err < 0)
		goto st_accel_i2c_read_byte_error;

	*res_byte = err & 0xff;

st_accel_i2c_read_byte_error:
	return err < 0 ? err : 0;
}