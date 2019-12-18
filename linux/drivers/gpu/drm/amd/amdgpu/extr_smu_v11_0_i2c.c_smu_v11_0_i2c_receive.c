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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct i2c_adapter {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CKSVII2C_IC_DATA_CMD ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  DAT ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_UT_DRIVER ; 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int I2C_NAK_7B_ADDR_NOACK ; 
 int I2C_NAK_TXDATA_NOACK ; 
 int I2C_NO_STOP ; 
 int I2C_OK ; 
 int I2C_RESTART ; 
 int I2C_SW_TIMEOUT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESTART ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMUIO ; 
 int /*<<< orphan*/  STOP ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int drm_debug ; 
 int /*<<< orphan*/  mmCKSVII2C_IC_DATA_CMD ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int*,int,int) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_clear_status (struct i2c_adapter*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_enable (struct i2c_adapter*,int) ; 
 int smu_v11_0_i2c_poll_rx_status (struct i2c_adapter*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_set_address (struct i2c_adapter*,int) ; 
 struct amdgpu_device* to_amdgpu_device (struct i2c_adapter*) ; 

__attribute__((used)) static uint32_t smu_v11_0_i2c_receive(struct i2c_adapter *control,
				 uint8_t address, uint8_t *data,
				 uint32_t numbytes, uint8_t i2c_flag)
{
	struct amdgpu_device *adev = to_amdgpu_device(control);
	uint32_t bytes_received, ret = I2C_OK;

	bytes_received = 0;

	/* Set the I2C slave address */
	smu_v11_0_i2c_set_address(control, address);

	/* Enable I2C */
	smu_v11_0_i2c_enable(control, true);

	while (numbytes > 0) {
		uint32_t reg = 0;

		smu_v11_0_i2c_clear_status(control);


		/* Prepare transaction */

		/* Each time we disable I2C, so this is not a restart */
		if (bytes_received == 0)
			reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, RESTART,
					    (i2c_flag & I2C_RESTART) ? 1 : 0);

		reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, DAT, 0);
		/* Read */
		reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, CMD, 1);

		/* Transmitting last byte */
		if (numbytes == 1)
			/* Final transaction, so send stop if requested */
			reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, STOP,
					    (i2c_flag & I2C_NO_STOP) ? 0 : 1);

		WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_DATA_CMD, reg);

		ret = smu_v11_0_i2c_poll_rx_status(control);

		/* Any error, no point in proceeding */
		if (ret != I2C_OK) {
			if (ret & I2C_SW_TIMEOUT)
				DRM_ERROR("TIMEOUT ERROR !!!");

			if (ret & I2C_NAK_7B_ADDR_NOACK)
				DRM_ERROR("Received I2C_NAK_7B_ADDR_NOACK !!!");

			if (ret & I2C_NAK_TXDATA_NOACK)
				DRM_ERROR("Received I2C_NAK_TXDATA_NOACK !!!");

			break;
		}

		reg = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_DATA_CMD);
		data[bytes_received] = REG_GET_FIELD(reg, CKSVII2C_IC_DATA_CMD, DAT);

		/* Record that the bytes were received */
		bytes_received++;
		numbytes--;
	}

	DRM_DEBUG_DRIVER("I2C_Receive(), address = %x, bytes = %d, data :",
		  (uint16_t)address, bytes_received);

	if (drm_debug & DRM_UT_DRIVER) {
		print_hex_dump(KERN_INFO, "data: ", DUMP_PREFIX_NONE,
			       16, 1, data, bytes_received, false);
	}

	return ret;
}