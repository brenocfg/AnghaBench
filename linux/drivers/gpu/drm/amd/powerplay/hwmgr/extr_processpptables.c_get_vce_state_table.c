#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct pp_hwmgr {int dummy; } ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_VCE_State_Table ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_POWERPLAYTABLE ;

/* Variables and functions */
 scalar_t__ get_vce_state_table_offset (struct pp_hwmgr*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const ATOM_PPLIB_VCE_State_Table *get_vce_state_table(
						struct pp_hwmgr *hwmgr,
						const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table)
{
	uint16_t table_offset = get_vce_state_table_offset(hwmgr, powerplay_table);

	if (table_offset > 0)
		return (const ATOM_PPLIB_VCE_State_Table *)(((unsigned long) powerplay_table) + table_offset);

	return NULL;
}