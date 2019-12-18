#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pp_hwmgr {int dummy; } ;
struct amd_vce_state {int evclk; int ecclk; } ;
struct TYPE_11__ {TYPE_2__* entries; } ;
typedef  TYPE_1__ VCEClockInfoArray ;
struct TYPE_12__ {int /*<<< orphan*/  usECClkLow; scalar_t__ ucECClkHigh; int /*<<< orphan*/  usEVClkLow; scalar_t__ ucEVClkHigh; } ;
typedef  TYPE_2__ VCEClockInfo ;
struct TYPE_16__ {int /*<<< orphan*/  usClockInfoArrayOffset; } ;
struct TYPE_15__ {size_t ucVCEClockInfoIndex; int ucClockInfoIndex; } ;
struct TYPE_14__ {TYPE_5__* entries; } ;
struct TYPE_13__ {unsigned long ucEntrySize; scalar_t__ clockInfo; } ;
typedef  TYPE_3__ ClockInfoArray ;
typedef  TYPE_4__ ATOM_PPLIB_VCE_State_Table ;
typedef  TYPE_5__ ATOM_PPLIB_VCE_State_Record ;
typedef  TYPE_6__ ATOM_PPLIB_POWERPLAYTABLE ;

/* Variables and functions */
 unsigned long NUM_BITS_CLOCK_INFO_ARRAY_INDEX ; 
 TYPE_6__* get_powerplay_table (struct pp_hwmgr*) ; 
 unsigned short get_vce_clock_info_array_offset (struct pp_hwmgr*,TYPE_6__ const*) ; 
 TYPE_4__* get_vce_state_table (struct pp_hwmgr*,TYPE_6__ const*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_vce_state_table_entry(struct pp_hwmgr *hwmgr,
							unsigned long i,
							struct amd_vce_state *vce_state,
							void **clock_info,
							unsigned long *flag)
{
	const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table = get_powerplay_table(hwmgr);

	const ATOM_PPLIB_VCE_State_Table *vce_state_table = get_vce_state_table(hwmgr, powerplay_table);

	unsigned short vce_clock_info_array_offset = get_vce_clock_info_array_offset(hwmgr, powerplay_table);

	const VCEClockInfoArray *vce_clock_info_array = (const VCEClockInfoArray *)(((unsigned long) powerplay_table) + vce_clock_info_array_offset);

	const ClockInfoArray *clock_arrays = (ClockInfoArray *)(((unsigned long)powerplay_table) +
								le16_to_cpu(powerplay_table->usClockInfoArrayOffset));

	const ATOM_PPLIB_VCE_State_Record *record = &vce_state_table->entries[i];

	const VCEClockInfo *vce_clock_info = &vce_clock_info_array->entries[record->ucVCEClockInfoIndex];

	unsigned long clockInfoIndex = record->ucClockInfoIndex & 0x3F;

	*flag = (record->ucClockInfoIndex >> NUM_BITS_CLOCK_INFO_ARRAY_INDEX);

	vce_state->evclk = ((uint32_t)vce_clock_info->ucEVClkHigh << 16) | le16_to_cpu(vce_clock_info->usEVClkLow);
	vce_state->ecclk = ((uint32_t)vce_clock_info->ucECClkHigh << 16) | le16_to_cpu(vce_clock_info->usECClkLow);

	*clock_info = (void *)((unsigned long)(clock_arrays->clockInfo) + (clockInfoIndex * clock_arrays->ucEntrySize));

	return 0;
}