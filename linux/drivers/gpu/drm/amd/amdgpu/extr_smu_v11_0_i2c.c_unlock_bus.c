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
struct i2c_adapter {int dummy; } ;
struct amdgpu_ras_eeprom_control {int bus_locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_bus_unlock (struct i2c_adapter*) ; 
 struct amdgpu_ras_eeprom_control* to_eeprom_control (struct i2c_adapter*) ; 

__attribute__((used)) static void unlock_bus(struct i2c_adapter *i2c, unsigned int flags)
{
	struct amdgpu_ras_eeprom_control *control = to_eeprom_control(i2c);

	if (!smu_v11_0_i2c_bus_unlock(i2c)) {
		DRM_ERROR("Failed to unlock the bus from SMU");
		return;
	}

	control->bus_locked = false;
}