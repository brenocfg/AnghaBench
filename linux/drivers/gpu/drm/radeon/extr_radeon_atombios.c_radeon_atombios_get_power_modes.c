#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct radeon_power_state {int dummy; } ;
struct radeon_pm_clock_info {int dummy; } ;
struct radeon_mode_info {int /*<<< orphan*/  atom_context; } ;
struct TYPE_8__ {int default_power_state_index; int num_power_states; int current_power_state_index; scalar_t__ current_vddc; TYPE_4__* power_state; scalar_t__ current_clock_mode_index; } ;
struct TYPE_6__ {int /*<<< orphan*/  default_sclk; int /*<<< orphan*/  default_mclk; } ;
struct radeon_device {TYPE_3__ pm; TYPE_1__ clock; struct radeon_mode_info mode_info; } ;
struct TYPE_7__ {scalar_t__ voltage; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_2__ voltage; int /*<<< orphan*/  sclk; int /*<<< orphan*/  mclk; } ;
struct TYPE_9__ {int num_clock_modes; int pcie_lanes; TYPE_5__* clock_info; scalar_t__ flags; TYPE_5__* default_clock_mode; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_DEFAULT ; 
 int /*<<< orphan*/  PowerPlayInfo ; 
 int /*<<< orphan*/  VOLTAGE_NONE ; 
 scalar_t__ atom_parse_data_header (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 
 TYPE_5__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int radeon_atombios_parse_power_table_1_3 (struct radeon_device*) ; 
 int radeon_atombios_parse_power_table_4_5 (struct radeon_device*) ; 
 int radeon_atombios_parse_power_table_6 (struct radeon_device*) ; 

void radeon_atombios_get_power_modes(struct radeon_device *rdev)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	int state_index = 0;

	rdev->pm.default_power_state_index = -1;

	if (atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		switch (frev) {
		case 1:
		case 2:
		case 3:
			state_index = radeon_atombios_parse_power_table_1_3(rdev);
			break;
		case 4:
		case 5:
			state_index = radeon_atombios_parse_power_table_4_5(rdev);
			break;
		case 6:
			state_index = radeon_atombios_parse_power_table_6(rdev);
			break;
		default:
			break;
		}
	}

	if (state_index == 0) {
		rdev->pm.power_state = kzalloc(sizeof(struct radeon_power_state), GFP_KERNEL);
		if (rdev->pm.power_state) {
			rdev->pm.power_state[0].clock_info =
				kcalloc(1,
				        sizeof(struct radeon_pm_clock_info),
				        GFP_KERNEL);
			if (rdev->pm.power_state[0].clock_info) {
				/* add the default mode */
				rdev->pm.power_state[state_index].type =
					POWER_STATE_TYPE_DEFAULT;
				rdev->pm.power_state[state_index].num_clock_modes = 1;
				rdev->pm.power_state[state_index].clock_info[0].mclk = rdev->clock.default_mclk;
				rdev->pm.power_state[state_index].clock_info[0].sclk = rdev->clock.default_sclk;
				rdev->pm.power_state[state_index].default_clock_mode =
					&rdev->pm.power_state[state_index].clock_info[0];
				rdev->pm.power_state[state_index].clock_info[0].voltage.type = VOLTAGE_NONE;
				rdev->pm.power_state[state_index].pcie_lanes = 16;
				rdev->pm.default_power_state_index = state_index;
				rdev->pm.power_state[state_index].flags = 0;
				state_index++;
			}
		}
	}

	rdev->pm.num_power_states = state_index;

	rdev->pm.current_power_state_index = rdev->pm.default_power_state_index;
	rdev->pm.current_clock_mode_index = 0;
	if (rdev->pm.default_power_state_index >= 0)
		rdev->pm.current_vddc =
			rdev->pm.power_state[rdev->pm.default_power_state_index].clock_info[0].voltage.voltage;
	else
		rdev->pm.current_vddc = 0;
}