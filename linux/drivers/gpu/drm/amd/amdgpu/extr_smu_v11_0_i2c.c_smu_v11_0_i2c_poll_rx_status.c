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
struct i2c_adapter {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABRT_7B_ADDR_NOACK ; 
 int /*<<< orphan*/  CKSVII2C_IC_STATUS ; 
 int /*<<< orphan*/  CKSVII2C_IC_TX_ABRT_SOURCE ; 
 int /*<<< orphan*/  I2C_NAK_7B_ADDR_NOACK ; 
 int /*<<< orphan*/  I2C_OK ; 
 int /*<<< orphan*/  I2C_SW_TIMEOUT ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFNE ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMUIO ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mmCKSVII2C_IC_STATUS ; 
 int /*<<< orphan*/  mmCKSVII2C_IC_TX_ABRT_SOURCE ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_clear_status (struct i2c_adapter*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 struct amdgpu_device* to_amdgpu_device (struct i2c_adapter*) ; 

__attribute__((used)) static uint32_t smu_v11_0_i2c_poll_rx_status(struct i2c_adapter *control)
{
	struct amdgpu_device *adev = to_amdgpu_device(control);
	uint32_t ret = I2C_OK;
	uint32_t reg_ic_status, reg_c_tx_abrt_source;

	reg_c_tx_abrt_source = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_TX_ABRT_SOURCE);

	/* If slave is not present */
	if (REG_GET_FIELD(reg_c_tx_abrt_source,
			  CKSVII2C_IC_TX_ABRT_SOURCE,
			  ABRT_7B_ADDR_NOACK) == 1) {
		ret |= I2C_NAK_7B_ADDR_NOACK;

		smu_v11_0_i2c_clear_status(control);
	} else {  /* wait till some data is there in RXFIFO */
		/* Poll for some byte in RXFIFO */
		unsigned long  timeout_counter = jiffies + msecs_to_jiffies(20);

		do {
			if (time_after(jiffies, timeout_counter)) {
				ret |= I2C_SW_TIMEOUT;
				break;
			}

			reg_ic_status = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);

		} while (REG_GET_FIELD(reg_ic_status, CKSVII2C_IC_STATUS, RFNE) == 0);
	}

	return ret;
}