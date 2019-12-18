#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ucVoltageType; void* usVoltageLevel; int /*<<< orphan*/  ucVoltageMode; } ;
union set_voltage {TYPE_2__ v2; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_ASIC_VOLTAGE_MODE_GET_GPIOMASK ; 
 int /*<<< orphan*/  SET_ASIC_VOLTAGE_MODE_GET_GPIOVAL ; 
 int /*<<< orphan*/  SetVoltage ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int radeon_atom_get_voltage_gpio_settings(struct radeon_device *rdev,
					  u16 voltage_level, u8 voltage_type,
					  u32 *gpio_value, u32 *gpio_mask)
{
	union set_voltage args;
	int index = GetIndexIntoMasterTable(COMMAND, SetVoltage);
	u8 frev, crev;

	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		return -EINVAL;

	switch (crev) {
	case 1:
		return -EINVAL;
	case 2:
		args.v2.ucVoltageType = voltage_type;
		args.v2.ucVoltageMode = SET_ASIC_VOLTAGE_MODE_GET_GPIOMASK;
		args.v2.usVoltageLevel = cpu_to_le16(voltage_level);

		atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);

		*gpio_mask = le32_to_cpu(*(u32 *)&args.v2);

		args.v2.ucVoltageType = voltage_type;
		args.v2.ucVoltageMode = SET_ASIC_VOLTAGE_MODE_GET_GPIOVAL;
		args.v2.usVoltageLevel = cpu_to_le16(voltage_level);

		atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);

		*gpio_value = le32_to_cpu(*(u32 *)&args.v2);
		break;
	default:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		return -EINVAL;
	}

	return 0;
}