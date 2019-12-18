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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 scalar_t__ I2C_OK ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ smu_v11_0_i2c_transmit (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t smu_v11_0_i2c_eeprom_write_data(struct i2c_adapter *control,
						uint8_t address,
						uint8_t *data,
						uint32_t numbytes)
{
	uint32_t  ret;

	ret = smu_v11_0_i2c_transmit(control, address, data, numbytes, 0);

	if (ret != I2C_OK)
		DRM_ERROR("WriteI2CData() - I2C error occurred :%x", ret);
	else
		/*
		 * According to EEPROM spec there is a MAX of 10 ms required for
		 * EEPROM to flush internal RX buffer after STOP was issued at the
		 * end of write transaction. During this time the EEPROM will not be
		 * responsive to any more commands - so wait a bit more.
		 *
		 * TODO Improve to wait for first ACK for slave address after
		 * internal write cycle done.
		 */
		msleep(10);

	return ret;

}