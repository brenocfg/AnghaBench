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

/* Variables and functions */
 int ISP1301_I2C_OTG_CONTROL_1 ; 
 int ISP1301_I2C_REG_CLEAR_ADDR ; 
 int /*<<< orphan*/  OTG1_VBUS_DRV ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1301_i2c_client ; 

__attribute__((used)) static inline void isp1301_vbus_off(void)
{
	i2c_smbus_write_byte_data(isp1301_i2c_client,
		ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR,
		OTG1_VBUS_DRV);
}