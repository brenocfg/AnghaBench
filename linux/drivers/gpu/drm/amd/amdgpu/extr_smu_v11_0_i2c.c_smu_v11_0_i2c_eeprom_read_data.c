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
 int /*<<< orphan*/  I2C_NO_STOP ; 
 scalar_t__ I2C_OK ; 
 int /*<<< orphan*/  I2C_RESTART ; 
 scalar_t__ smu_v11_0_i2c_receive (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ smu_v11_0_i2c_transmit (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t smu_v11_0_i2c_eeprom_read_data(struct i2c_adapter *control,
					       uint8_t address,
					       uint8_t *data,
					       uint32_t numbytes)
{
	uint32_t  ret = 0;

	/* First 2 bytes are dummy write to set EEPROM address */
	ret = smu_v11_0_i2c_transmit(control, address, data, 2, I2C_NO_STOP);
	if (ret != I2C_OK)
		goto Fail;

	/* Now read data starting with that address */
	ret = smu_v11_0_i2c_receive(control, address, data + 2, numbytes - 2,
				    I2C_RESTART);

Fail:
	if (ret != I2C_OK)
		DRM_ERROR("ReadData() - I2C error occurred :%x", ret);

	return ret;
}