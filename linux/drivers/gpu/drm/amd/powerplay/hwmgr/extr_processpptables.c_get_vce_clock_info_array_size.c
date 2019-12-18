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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct pp_hwmgr {int dummy; } ;
struct TYPE_2__ {int ucNumEntries; } ;
typedef  TYPE_1__ VCEClockInfoArray ;
typedef  int /*<<< orphan*/  VCEClockInfo ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_POWERPLAYTABLE ;

/* Variables and functions */
 scalar_t__ get_vce_clock_info_array_offset (struct pp_hwmgr*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static uint16_t get_vce_clock_info_array_size(struct pp_hwmgr *hwmgr,
			const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table)
{
	uint16_t table_offset = get_vce_clock_info_array_offset(hwmgr,
							powerplay_table);
	uint16_t table_size = 0;

	if (table_offset > 0) {
		const VCEClockInfoArray *p = (const VCEClockInfoArray *)
			(((unsigned long) powerplay_table) + table_offset);
		table_size = sizeof(uint8_t) + p->ucNumEntries * sizeof(VCEClockInfo);
	}

	return table_size;
}