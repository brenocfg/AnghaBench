#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_14__ {int nonClockInfoIndex; int ucNumDPMLevels; int /*<<< orphan*/ * clockInfoIndex; } ;
union pplib_power_state {TYPE_2__ v2; } ;
struct TYPE_15__ {int ucEngineClockHigh; int /*<<< orphan*/  usEngineClockLow; } ;
union pplib_clock_info {TYPE_3__ sumo; } ;
struct TYPE_13__ {int /*<<< orphan*/  usNonClockInfoArrayOffset; int /*<<< orphan*/  usClockInfoArrayOffset; int /*<<< orphan*/  usStateArrayOffset; } ;
union power_info {TYPE_1__ pplib; } ;
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct kv_ps {int dummy; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_mode_info {TYPE_11__* atom_context; } ;
struct TYPE_17__ {int num_ps; int num_of_vce_states; TYPE_4__* vce_states; TYPE_7__* ps; } ;
struct TYPE_18__ {TYPE_5__ dpm; } ;
struct amdgpu_device {TYPE_6__ pm; struct amdgpu_mode_info mode_info; } ;
struct _StateArray {int ucNumEntries; scalar_t__ states; } ;
struct _NonClockInfoArray {int /*<<< orphan*/  ucEntrySize; int /*<<< orphan*/ * nonClockInfo; } ;
struct _ClockInfoArray {int ucNumEntries; int ucEntrySize; int /*<<< orphan*/ * clockInfo; } ;
struct _ATOM_PPLIB_NONCLOCK_INFO {int dummy; } ;
struct TYPE_19__ {struct kv_ps* ps_priv; } ;
struct TYPE_16__ {int clk_idx; int sclk; scalar_t__ mclk; } ;
struct TYPE_12__ {int bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PowerPlayInfo ; 
 int SUMO_MAX_HARDWARE_POWERLEVELS ; 
 int /*<<< orphan*/  amdgpu_add_thermal_controller (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_data_header (TYPE_11__*,int,int /*<<< orphan*/ *,int*,int*,int*) ; 
 TYPE_7__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_7__*) ; 
 int /*<<< orphan*/  kv_parse_pplib_clock_info (struct amdgpu_device*,TYPE_7__*,int,union pplib_clock_info*) ; 
 int /*<<< orphan*/  kv_parse_pplib_non_clock_info (struct amdgpu_device*,TYPE_7__*,struct _ATOM_PPLIB_NONCLOCK_INFO*,int /*<<< orphan*/ ) ; 
 struct kv_ps* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_parse_power_table(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
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
	struct kv_ps *ps;

	if (!amdgpu_atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset))
		return -EINVAL;
	power_info = (union power_info *)(mode_info->atom_context->bios + data_offset);

	amdgpu_add_thermal_controller(adev);

	state_array = (struct _StateArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usStateArrayOffset));
	clock_info_array = (struct _ClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usClockInfoArrayOffset));
	non_clock_info_array = (struct _NonClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(power_info->pplib.usNonClockInfoArrayOffset));

	adev->pm.dpm.ps = kcalloc(state_array->ucNumEntries,
				  sizeof(struct amdgpu_ps),
				  GFP_KERNEL);
	if (!adev->pm.dpm.ps)
		return -ENOMEM;
	power_state_offset = (u8 *)state_array->states;
	for (i = 0; i < state_array->ucNumEntries; i++) {
		u8 *idx;
		power_state = (union pplib_power_state *)power_state_offset;
		non_clock_array_index = power_state->v2.nonClockInfoIndex;
		non_clock_info = (struct _ATOM_PPLIB_NONCLOCK_INFO *)
			&non_clock_info_array->nonClockInfo[non_clock_array_index];
		ps = kzalloc(sizeof(struct kv_ps), GFP_KERNEL);
		if (ps == NULL) {
			kfree(adev->pm.dpm.ps);
			return -ENOMEM;
		}
		adev->pm.dpm.ps[i].ps_priv = ps;
		k = 0;
		idx = (u8 *)&power_state->v2.clockInfoIndex[0];
		for (j = 0; j < power_state->v2.ucNumDPMLevels; j++) {
			clock_array_index = idx[j];
			if (clock_array_index >= clock_info_array->ucNumEntries)
				continue;
			if (k >= SUMO_MAX_HARDWARE_POWERLEVELS)
				break;
			clock_info = (union pplib_clock_info *)
				((u8 *)&clock_info_array->clockInfo[0] +
				 (clock_array_index * clock_info_array->ucEntrySize));
			kv_parse_pplib_clock_info(adev,
						  &adev->pm.dpm.ps[i], k,
						  clock_info);
			k++;
		}
		kv_parse_pplib_non_clock_info(adev, &adev->pm.dpm.ps[i],
					      non_clock_info,
					      non_clock_info_array->ucEntrySize);
		power_state_offset += 2 + power_state->v2.ucNumDPMLevels;
	}
	adev->pm.dpm.num_ps = state_array->ucNumEntries;

	/* fill in the vce power states */
	for (i = 0; i < adev->pm.dpm.num_of_vce_states; i++) {
		u32 sclk;
		clock_array_index = adev->pm.dpm.vce_states[i].clk_idx;
		clock_info = (union pplib_clock_info *)
			&clock_info_array->clockInfo[clock_array_index * clock_info_array->ucEntrySize];
		sclk = le16_to_cpu(clock_info->sumo.usEngineClockLow);
		sclk |= clock_info->sumo.ucEngineClockHigh << 16;
		adev->pm.dpm.vce_states[i].sclk = sclk;
		adev->pm.dpm.vce_states[i].mclk = 0;
	}

	return 0;
}