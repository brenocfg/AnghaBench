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
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; scalar_t__ addr; } ;
struct i2c_adapter {int dummy; } ;
struct amdgpu_ras_eeprom_control {int /*<<< orphan*/  bus_locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EIO ; 
 int I2C_M_RD ; 
 int I2C_OK ; 
 int smu_v11_0_i2c_eeprom_read_data (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smu_v11_0_i2c_eeprom_write_data (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_fini (struct i2c_adapter*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_init (struct i2c_adapter*) ; 
 struct amdgpu_ras_eeprom_control* to_eeprom_control (struct i2c_adapter*) ; 

__attribute__((used)) static int smu_v11_0_i2c_eeprom_i2c_xfer(struct i2c_adapter *i2c_adap,
			      struct i2c_msg *msgs, int num)
{
	int i, ret;
	struct amdgpu_ras_eeprom_control *control = to_eeprom_control(i2c_adap);

	if (!control->bus_locked) {
		DRM_ERROR("I2C bus unlocked, stopping transaction!");
		return -EIO;
	}

	smu_v11_0_i2c_init(i2c_adap);

	for (i = 0; i < num; i++) {
		if (msgs[i].flags & I2C_M_RD)
			ret = smu_v11_0_i2c_eeprom_read_data(i2c_adap,
							(uint8_t)msgs[i].addr,
							msgs[i].buf, msgs[i].len);
		else
			ret = smu_v11_0_i2c_eeprom_write_data(i2c_adap,
							 (uint8_t)msgs[i].addr,
							 msgs[i].buf, msgs[i].len);

		if (ret != I2C_OK) {
			num = -EIO;
			break;
		}
	}

	smu_v11_0_i2c_fini(i2c_adap);
	return num;
}