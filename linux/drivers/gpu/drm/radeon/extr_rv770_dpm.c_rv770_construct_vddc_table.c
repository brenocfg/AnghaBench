#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct rv7xx_power_info {size_t vddc_mask_low; void* valid_vddc_entries; TYPE_1__* vddc_table; } ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {int vddc; size_t low_smio; scalar_t__ high_smio; void* vddc_index; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MAX_NO_VREG_STEPS ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  radeon_atom_get_max_voltage (struct radeon_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  radeon_atom_get_min_voltage (struct radeon_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  radeon_atom_get_voltage_gpio_settings (struct radeon_device*,int,int /*<<< orphan*/ ,size_t*,size_t*) ; 
 int /*<<< orphan*/  radeon_atom_get_voltage_step (struct radeon_device*,int /*<<< orphan*/ ,int*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int rv770_construct_vddc_table(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u16 min, max, step;
	u32 steps = 0;
	u8 vddc_index = 0;
	u32 i;

	radeon_atom_get_min_voltage(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, &min);
	radeon_atom_get_max_voltage(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, &max);
	radeon_atom_get_voltage_step(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, &step);

	steps = (max - min) / step + 1;

	if (steps > MAX_NO_VREG_STEPS)
		return -EINVAL;

	for (i = 0; i < steps; i++) {
		u32 gpio_pins, gpio_mask;

		pi->vddc_table[i].vddc = (u16)(min + i * step);
		radeon_atom_get_voltage_gpio_settings(rdev,
						      pi->vddc_table[i].vddc,
						      SET_VOLTAGE_TYPE_ASIC_VDDC,
						      &gpio_pins, &gpio_mask);
		pi->vddc_table[i].low_smio = gpio_pins & gpio_mask;
		pi->vddc_table[i].high_smio = 0;
		pi->vddc_mask_low = gpio_mask;
		if (i > 0) {
			if ((pi->vddc_table[i].low_smio !=
			     pi->vddc_table[i - 1].low_smio ) ||
			     (pi->vddc_table[i].high_smio !=
			      pi->vddc_table[i - 1].high_smio))
				vddc_index++;
		}
		pi->vddc_table[i].vddc_index = vddc_index;
	}

	pi->valid_vddc_entries = (u8)steps;

	return 0;
}