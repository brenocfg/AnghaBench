#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned long bios_index; int flags; } ;
struct pp_power_state {int /*<<< orphan*/  hardware; TYPE_2__ classification; } ;
struct pp_hwmgr {scalar_t__ chip_family; TYPE_3__* hwmgr_func; } ;
typedef  int (* pp_tables_hw_clock_info_callback ) (struct pp_hwmgr*,int /*<<< orphan*/ *,int,void const*) ;
struct TYPE_13__ {int ucTableFormatRevision; } ;
struct TYPE_21__ {unsigned long ucNumStates; unsigned long ucStateEntrySize; int ucNonClockSize; int ucClockInfoSize; int /*<<< orphan*/  usClockInfoArrayOffset; int /*<<< orphan*/  usNonClockInfoArrayOffset; int /*<<< orphan*/  usStateArrayOffset; TYPE_1__ sHeader; } ;
struct TYPE_20__ {int ucNonClockStateIndex; int* ucClockStateIndices; } ;
struct TYPE_19__ {unsigned long nonClockInfoIndex; int ucNumDPMLevels; unsigned long* clockInfoIndex; } ;
struct TYPE_18__ {unsigned long ucEntrySize; scalar_t__ clockInfo; } ;
struct TYPE_17__ {unsigned long ucEntrySize; scalar_t__ nonClockInfo; } ;
struct TYPE_16__ {unsigned long ucNumEntries; } ;
struct TYPE_15__ {int (* patch_boot_state ) (struct pp_hwmgr*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ StateArray ;
typedef  TYPE_5__ NonClockInfoArray ;
typedef  TYPE_6__ ClockInfoArray ;
typedef  TYPE_7__ ATOM_PPLIB_STATE_V2 ;
typedef  TYPE_8__ ATOM_PPLIB_STATE ;
typedef  TYPE_9__ ATOM_PPLIB_POWERPLAYTABLE ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_NONCLOCK_INFO ;

/* Variables and functions */
 scalar_t__ AMDGPU_FAMILY_RV ; 
 int PP_StateClassificationFlag_Boot ; 
 TYPE_9__* get_powerplay_table (struct pp_hwmgr*) ; 
 TYPE_7__* get_state_entry_v2 (TYPE_4__ const*,unsigned long) ; 
 int init_non_clock_fields (struct pp_hwmgr*,struct pp_power_state*,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (struct pp_hwmgr*,int /*<<< orphan*/ *) ; 

int pp_tables_get_entry(struct pp_hwmgr *hwmgr,
				unsigned long entry_index,
				struct pp_power_state *ps,
			 pp_tables_hw_clock_info_callback func)
{
	int i;
	const StateArray *pstate_arrays;
	const ATOM_PPLIB_STATE_V2 *pstate_entry_v2;
	const ATOM_PPLIB_NONCLOCK_INFO *pnon_clock_info;
	const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table = get_powerplay_table(hwmgr);
	int result = 0;
	int res = 0;

	const ClockInfoArray *pclock_arrays;

	const NonClockInfoArray *pnon_clock_arrays;

	const ATOM_PPLIB_STATE *pstate_entry;

	if (powerplay_table == NULL)
		return -1;

	ps->classification.bios_index = entry_index;

	if (powerplay_table->sHeader.ucTableFormatRevision >= 6) {
		pstate_arrays = (StateArray *)(((unsigned long)powerplay_table) +
					le16_to_cpu(powerplay_table->usStateArrayOffset));

		if (entry_index > pstate_arrays->ucNumEntries)
			return -1;

		pstate_entry_v2 = get_state_entry_v2(pstate_arrays, entry_index);
		pclock_arrays = (ClockInfoArray *)(((unsigned long)powerplay_table) +
					le16_to_cpu(powerplay_table->usClockInfoArrayOffset));

		pnon_clock_arrays = (NonClockInfoArray *)(((unsigned long)powerplay_table) +
						le16_to_cpu(powerplay_table->usNonClockInfoArrayOffset));

		pnon_clock_info = (ATOM_PPLIB_NONCLOCK_INFO *)((unsigned long)(pnon_clock_arrays->nonClockInfo) +
					(pstate_entry_v2->nonClockInfoIndex * pnon_clock_arrays->ucEntrySize));

		result = init_non_clock_fields(hwmgr, ps, pnon_clock_arrays->ucEntrySize, pnon_clock_info);

		for (i = 0; i < pstate_entry_v2->ucNumDPMLevels; i++) {
			const void *pclock_info = (const void *)(
							(unsigned long)(pclock_arrays->clockInfo) +
							(pstate_entry_v2->clockInfoIndex[i] * pclock_arrays->ucEntrySize));
			res = func(hwmgr, &ps->hardware, i, pclock_info);
			if ((0 == result) && (0 != res))
				result = res;
		}
	} else {
		if (entry_index > powerplay_table->ucNumStates)
			return -1;

		pstate_entry = (ATOM_PPLIB_STATE *)((unsigned long)powerplay_table +
						    le16_to_cpu(powerplay_table->usStateArrayOffset) +
						    entry_index * powerplay_table->ucStateEntrySize);

		pnon_clock_info = (ATOM_PPLIB_NONCLOCK_INFO *)((unsigned long)powerplay_table +
						le16_to_cpu(powerplay_table->usNonClockInfoArrayOffset) +
						pstate_entry->ucNonClockStateIndex *
						powerplay_table->ucNonClockSize);

		result = init_non_clock_fields(hwmgr, ps,
							powerplay_table->ucNonClockSize,
							pnon_clock_info);

		for (i = 0; i < powerplay_table->ucStateEntrySize-1; i++) {
			const void *pclock_info = (const void *)((unsigned long)powerplay_table +
						le16_to_cpu(powerplay_table->usClockInfoArrayOffset) +
						pstate_entry->ucClockStateIndices[i] *
						powerplay_table->ucClockInfoSize);

			int res = func(hwmgr, &ps->hardware, i, pclock_info);

			if ((0 == result) && (0 != res))
					result = res;
		}
	}

	if ((0 == result) && (0 != (ps->classification.flags & PP_StateClassificationFlag_Boot))) {
		if (hwmgr->chip_family < AMDGPU_FAMILY_RV)
			result = hwmgr->hwmgr_func->patch_boot_state(hwmgr, &(ps->hardware));
	}

	return result;
}