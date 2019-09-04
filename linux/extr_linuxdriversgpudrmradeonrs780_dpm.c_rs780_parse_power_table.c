#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ucNonClockStateIndex; int* ucClockStateIndices; } ;
union pplib_power_state {TYPE_1__ v1; } ;
typedef  union pplib_clock_info {int dummy; } pplib_clock_info ;
struct TYPE_13__ {int ucNumStates; int ucStateEntrySize; int ucNonClockSize; int ucClockInfoSize; int /*<<< orphan*/  usClockInfoArrayOffset; int /*<<< orphan*/  usNonClockInfoArrayOffset; int /*<<< orphan*/  usStateArrayOffset; } ;
union power_info {TYPE_4__ pplib; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct radeon_ps {int dummy; } ;
struct radeon_mode_info {TYPE_9__* atom_context; } ;
struct TYPE_11__ {int num_ps; TYPE_5__* ps; } ;
struct TYPE_12__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; struct radeon_mode_info mode_info; } ;
struct igp_ps {int dummy; } ;
struct _ATOM_PPLIB_NONCLOCK_INFO {int dummy; } ;
struct TYPE_15__ {scalar_t__ bios; } ;
struct TYPE_14__ {struct igp_ps* ps_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PowerPlayInfo ; 
 int /*<<< orphan*/  atom_parse_data_header (TYPE_9__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_5__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 struct igp_ps* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs780_parse_pplib_clock_info (struct radeon_device*,TYPE_5__*,union pplib_clock_info*) ; 
 int /*<<< orphan*/  rs780_parse_pplib_non_clock_info (struct radeon_device*,TYPE_5__*,struct _ATOM_PPLIB_NONCLOCK_INFO*,int) ; 

__attribute__((used)) static int rs780_parse_power_table(struct radeon_device *rdev)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	struct _ATOM_PPLIB_NONCLOCK_INFO *non_clock_info;
	union pplib_power_state *power_state;
	int i;
	union pplib_clock_info *clock_info;
	union power_info *power_info;
	int index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	struct igp_ps *ps;

	if (!atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset))
		return -EINVAL;
	power_info = (union power_info *)(mode_info->atom_context->bios + data_offset);

	rdev->pm.dpm.ps = kcalloc(power_info->pplib.ucNumStates,
				  sizeof(struct radeon_ps),
				  GFP_KERNEL);
	if (!rdev->pm.dpm.ps)
		return -ENOMEM;

	for (i = 0; i < power_info->pplib.ucNumStates; i++) {
		power_state = (union pplib_power_state *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(power_info->pplib.usStateArrayOffset) +
			 i * power_info->pplib.ucStateEntrySize);
		non_clock_info = (struct _ATOM_PPLIB_NONCLOCK_INFO *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(power_info->pplib.usNonClockInfoArrayOffset) +
			 (power_state->v1.ucNonClockStateIndex *
			  power_info->pplib.ucNonClockSize));
		if (power_info->pplib.ucStateEntrySize - 1) {
			clock_info = (union pplib_clock_info *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(power_info->pplib.usClockInfoArrayOffset) +
				 (power_state->v1.ucClockStateIndices[0] *
				  power_info->pplib.ucClockInfoSize));
			ps = kzalloc(sizeof(struct igp_ps), GFP_KERNEL);
			if (ps == NULL) {
				kfree(rdev->pm.dpm.ps);
				return -ENOMEM;
			}
			rdev->pm.dpm.ps[i].ps_priv = ps;
			rs780_parse_pplib_non_clock_info(rdev, &rdev->pm.dpm.ps[i],
							 non_clock_info,
							 power_info->pplib.ucNonClockSize);
			rs780_parse_pplib_clock_info(rdev,
						     &rdev->pm.dpm.ps[i],
						     clock_info);
		}
	}
	rdev->pm.dpm.num_ps = power_info->pplib.ucNumStates;
	return 0;
}