#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int nonClockInfoIndex; int ucNumDPMLevels; int /*<<< orphan*/ * clockInfoIndex; } ;
union pplib_power_state {TYPE_3__ v2; } ;
typedef  union pplib_clock_info {int dummy; } pplib_clock_info ;
struct TYPE_12__ {int /*<<< orphan*/  usNonClockInfoArrayOffset; int /*<<< orphan*/  usClockInfoArrayOffset; int /*<<< orphan*/  usStateArrayOffset; } ;
union power_info {TYPE_1__ pplib; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct sumo_ps {int dummy; } ;
struct radeon_ps {int dummy; } ;
struct radeon_mode_info {TYPE_10__* atom_context; } ;
struct TYPE_15__ {int num_ps; TYPE_6__* ps; } ;
struct TYPE_16__ {TYPE_4__ dpm; TYPE_2__* power_state; } ;
struct radeon_device {TYPE_5__ pm; struct radeon_mode_info mode_info; } ;
struct _StateArray {int ucNumEntries; scalar_t__ states; } ;
struct _NonClockInfoArray {int /*<<< orphan*/  ucEntrySize; int /*<<< orphan*/ * nonClockInfo; } ;
struct _ClockInfoArray {int ucEntrySize; int /*<<< orphan*/ * clockInfo; } ;
struct _ATOM_PPLIB_NONCLOCK_INFO {int dummy; } ;
struct TYPE_17__ {struct sumo_ps* ps_priv; } ;
struct TYPE_13__ {int /*<<< orphan*/  clock_info; } ;
struct TYPE_11__ {scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PowerPlayInfo ; 
 int SUMO_MAX_HARDWARE_POWERLEVELS ; 
 int /*<<< orphan*/  atom_parse_data_header (TYPE_10__*,int,int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 TYPE_6__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_6__*) ; 
 struct sumo_ps* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sumo_parse_pplib_clock_info (struct radeon_device*,TYPE_6__*,int,union pplib_clock_info*) ; 
 int /*<<< orphan*/  sumo_parse_pplib_non_clock_info (struct radeon_device*,TYPE_6__*,struct _ATOM_PPLIB_NONCLOCK_INFO*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sumo_parse_power_table(struct radeon_device *rdev)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	struct _ATOM_PPLIB_NONCLOCK_INFO *non_clock_info;
	union pplib_power_state *power_state;
	int i, j, k, non_clock_array_index, clock_array_index;
	union pplib_clock_info *clock_info;
	struct _StateArray *state_array;
	struct _ClockInfoArray *clock_info_array;
	struct _NonClockInfoArray *non_clock_info_array;
	union power_info *power_info;
	int index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	u8 *power_state_offset;
	struct sumo_ps *ps;

	if (!atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset))
		return -EINVAL;
	power_info = (union power_info *)(mode_info->atom_context->bios + data_offset);

	state_array = (struct _StateArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usStateArrayOffset));
	clock_info_array = (struct _ClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usClockInfoArrayOffset));
	non_clock_info_array = (struct _NonClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usNonClockInfoArrayOffset));

	rdev->pm.dpm.ps = kcalloc(state_array->ucNumEntries,
				  sizeof(struct radeon_ps),
				  GFP_KERNEL);
	if (!rdev->pm.dpm.ps)
		return -ENOMEM;
	power_state_offset = (u8 *)state_array->states;
	for (i = 0; i < state_array->ucNumEntries; i++) {
		u8 *idx;
		power_state = (union pplib_power_state *)power_state_offset;
		non_clock_array_index = power_state->v2.nonClockInfoIndex;
		non_clock_info = (struct _ATOM_PPLIB_NONCLOCK_INFO *)
			&non_clock_info_array->nonClockInfo[non_clock_array_index];
		if (!rdev->pm.power_state[i].clock_info)
			return -EINVAL;
		ps = kzalloc(sizeof(struct sumo_ps), GFP_KERNEL);
		if (ps == NULL) {
			kfree(rdev->pm.dpm.ps);
			return -ENOMEM;
		}
		rdev->pm.dpm.ps[i].ps_priv = ps;
		k = 0;
		idx = (u8 *)&power_state->v2.clockInfoIndex[0];
		for (j = 0; j < power_state->v2.ucNumDPMLevels; j++) {
			clock_array_index = idx[j];
			if (k >= SUMO_MAX_HARDWARE_POWERLEVELS)
				break;

			clock_info = (union pplib_clock_info *)
				((u8 *)&clock_info_array->clockInfo[0] +
				 (clock_array_index * clock_info_array->ucEntrySize));
			sumo_parse_pplib_clock_info(rdev,
						    &rdev->pm.dpm.ps[i], k,
						    clock_info);
			k++;
		}
		sumo_parse_pplib_non_clock_info(rdev, &rdev->pm.dpm.ps[i],
						non_clock_info,
						non_clock_info_array->ucEntrySize);
		power_state_offset += 2 + power_state->v2.ucNumDPMLevels;
	}
	rdev->pm.dpm.num_ps = state_array->ucNumEntries;
	return 0;
}