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
struct amdgpu_ras_eeprom_control {int /*<<< orphan*/  eeprom_accessor; } ;
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  smu_v11_0_i2c_eeprom_control_fini (int /*<<< orphan*/ *) ; 
 struct amdgpu_device* to_amdgpu_device (struct amdgpu_ras_eeprom_control*) ; 

void amdgpu_ras_eeprom_fini(struct amdgpu_ras_eeprom_control *control)
{
	struct amdgpu_device *adev = to_amdgpu_device(control);

	switch (adev->asic_type) {
	case CHIP_VEGA20:
		smu_v11_0_i2c_eeprom_control_fini(&control->eeprom_accessor);
		break;

	default:
		return;
	}
}