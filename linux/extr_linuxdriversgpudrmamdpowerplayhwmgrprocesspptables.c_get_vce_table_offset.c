#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct pp_hwmgr {int dummy; } ;
struct TYPE_7__ {scalar_t__ usSize; scalar_t__ usVCETableOffset; } ;
struct TYPE_6__ {scalar_t__ usTableSize; } ;
struct TYPE_5__ {scalar_t__ usExtendendedHeaderOffset; } ;
typedef  TYPE_1__ ATOM_PPLIB_POWERPLAYTABLE3 ;
typedef  TYPE_2__ ATOM_PPLIB_POWERPLAYTABLE ;
typedef  TYPE_3__ ATOM_PPLIB_EXTENDEDHEADER ;

/* Variables and functions */
 scalar_t__ SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2 ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static uint16_t get_vce_table_offset(struct pp_hwmgr *hwmgr,
			const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table)
{
	uint16_t vce_table_offset = 0;

	if (le16_to_cpu(powerplay_table->usTableSize) >=
	   sizeof(ATOM_PPLIB_POWERPLAYTABLE3)) {
		const ATOM_PPLIB_POWERPLAYTABLE3 *powerplay_table3 =
			(const ATOM_PPLIB_POWERPLAYTABLE3 *)powerplay_table;

		if (powerplay_table3->usExtendendedHeaderOffset > 0) {
			const ATOM_PPLIB_EXTENDEDHEADER  *extended_header =
						(const ATOM_PPLIB_EXTENDEDHEADER *)
						(((unsigned long)powerplay_table3) +
						le16_to_cpu(powerplay_table3->usExtendendedHeaderOffset));
			if (le16_to_cpu(extended_header->usSize) >=
			   SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2)
				vce_table_offset = le16_to_cpu(extended_header->usVCETableOffset);
		}
	}

	return vce_table_offset;
}