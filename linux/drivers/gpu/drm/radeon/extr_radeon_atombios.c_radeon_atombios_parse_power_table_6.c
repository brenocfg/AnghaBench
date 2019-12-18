#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nonClockInfoIndex; int ucNumDPMLevels; int* clockInfoIndex; } ;
union pplib_power_state {TYPE_3__ v2; } ;
typedef  union pplib_clock_info {int dummy; } pplib_clock_info ;
struct TYPE_8__ {int /*<<< orphan*/  usNonClockInfoArrayOffset; int /*<<< orphan*/  usClockInfoArrayOffset; int /*<<< orphan*/  usStateArrayOffset; int /*<<< orphan*/  sThermalController; } ;
union power_info {TYPE_1__ pplib; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct radeon_power_state {int dummy; } ;
struct radeon_pm_clock_info {int dummy; } ;
struct radeon_mode_info {TYPE_7__* atom_context; } ;
struct TYPE_12__ {int default_power_state_index; TYPE_6__* power_state; } ;
struct TYPE_9__ {int /*<<< orphan*/  default_sclk; int /*<<< orphan*/  default_mclk; } ;
struct radeon_device {TYPE_5__ pm; TYPE_2__ clock; struct radeon_mode_info mode_info; } ;
struct _StateArray {int ucNumEntries; scalar_t__ states; } ;
struct _NonClockInfoArray {int /*<<< orphan*/ * nonClockInfo; } ;
struct _ClockInfoArray {int ucEntrySize; int /*<<< orphan*/ * clockInfo; } ;
struct _ATOM_PPLIB_NONCLOCK_INFO {int dummy; } ;
struct TYPE_14__ {scalar_t__ bios; } ;
struct TYPE_13__ {int num_clock_modes; TYPE_4__* clock_info; TYPE_4__* default_clock_mode; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  sclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_DEFAULT ; 
 int /*<<< orphan*/  PowerPlayInfo ; 
 int /*<<< orphan*/  RADEON_PM_MODE_NO_DISPLAY ; 
 int /*<<< orphan*/  atom_parse_data_header (TYPE_7__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_add_pplib_thermal_controller (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int radeon_atombios_parse_pplib_clock_info (struct radeon_device*,int,int,union pplib_clock_info*) ; 
 int /*<<< orphan*/  radeon_atombios_parse_pplib_non_clock_info (struct radeon_device*,int,int,struct _ATOM_PPLIB_NONCLOCK_INFO*) ; 

__attribute__((used)) static int radeon_atombios_parse_power_table_6(struct radeon_device *rdev)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	struct _ATOM_PPLIB_NONCLOCK_INFO *non_clock_info;
	union pplib_power_state *power_state;
	int i, j, non_clock_array_index, clock_array_index;
	int state_index = 0, mode_index = 0;
	union pplib_clock_info *clock_info;
	struct _StateArray *state_array;
	struct _ClockInfoArray *clock_info_array;
	struct _NonClockInfoArray *non_clock_info_array;
	bool valid;
	union power_info *power_info;
	int index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	u8 *power_state_offset;

	if (!atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset))
		return state_index;
	power_info = (union power_info *)(mode_info->atom_context->bios + data_offset);

	radeon_atombios_add_pplib_thermal_controller(rdev, &power_info->pplib.sThermalController);
	state_array = (struct _StateArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usStateArrayOffset));
	clock_info_array = (struct _ClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usClockInfoArrayOffset));
	non_clock_info_array = (struct _NonClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usNonClockInfoArrayOffset));
	if (state_array->ucNumEntries == 0)
		return state_index;
	rdev->pm.power_state = kcalloc(state_array->ucNumEntries,
				       sizeof(struct radeon_power_state),
				       GFP_KERNEL);
	if (!rdev->pm.power_state)
		return state_index;
	power_state_offset = (u8 *)state_array->states;
	for (i = 0; i < state_array->ucNumEntries; i++) {
		mode_index = 0;
		power_state = (union pplib_power_state *)power_state_offset;
		non_clock_array_index = power_state->v2.nonClockInfoIndex;
		non_clock_info = (struct _ATOM_PPLIB_NONCLOCK_INFO *)
			&non_clock_info_array->nonClockInfo[non_clock_array_index];
		rdev->pm.power_state[i].clock_info =
			kcalloc(power_state->v2.ucNumDPMLevels ?
				power_state->v2.ucNumDPMLevels : 1,
				sizeof(struct radeon_pm_clock_info),
				GFP_KERNEL);
		if (!rdev->pm.power_state[i].clock_info)
			return state_index;
		if (power_state->v2.ucNumDPMLevels) {
			for (j = 0; j < power_state->v2.ucNumDPMLevels; j++) {
				clock_array_index = power_state->v2.clockInfoIndex[j];
				clock_info = (union pplib_clock_info *)
					&clock_info_array->clockInfo[clock_array_index * clock_info_array->ucEntrySize];
				valid = radeon_atombios_parse_pplib_clock_info(rdev,
									       state_index, mode_index,
									       clock_info);
				if (valid)
					mode_index++;
			}
		} else {
			rdev->pm.power_state[state_index].clock_info[0].mclk =
				rdev->clock.default_mclk;
			rdev->pm.power_state[state_index].clock_info[0].sclk =
				rdev->clock.default_sclk;
			mode_index++;
		}
		rdev->pm.power_state[state_index].num_clock_modes = mode_index;
		if (mode_index) {
			radeon_atombios_parse_pplib_non_clock_info(rdev, state_index, mode_index,
								   non_clock_info);
			state_index++;
		}
		power_state_offset += 2 + power_state->v2.ucNumDPMLevels;
	}
	/* if multiple clock modes, mark the lowest as no display */
	for (i = 0; i < state_index; i++) {
		if (rdev->pm.power_state[i].num_clock_modes > 1)
			rdev->pm.power_state[i].clock_info[0].flags |=
				RADEON_PM_MODE_NO_DISPLAY;
	}
	/* first mode is usually default */
	if (rdev->pm.default_power_state_index == -1) {
		rdev->pm.power_state[0].type =
			POWER_STATE_TYPE_DEFAULT;
		rdev->pm.default_power_state_index = 0;
		rdev->pm.power_state[0].default_clock_mode =
			&rdev->pm.power_state[0].clock_info[0];
	}
	return state_index;
}