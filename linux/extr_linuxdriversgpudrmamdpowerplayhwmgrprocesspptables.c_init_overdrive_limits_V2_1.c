#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* memoryClock; void* engineClock; } ;
struct TYPE_8__ {scalar_t__ overdriveVDDCStep; scalar_t__ maxOverdriveVDDC; scalar_t__ minOverdriveVDDC; TYPE_1__ overdriveLimit; } ;
struct pp_hwmgr {TYPE_2__ platform_descriptor; } ;
struct TYPE_11__ {int /*<<< orphan*/  ulMaxMemoryClock; int /*<<< orphan*/  ulMaxEngineClock; } ;
struct TYPE_10__ {scalar_t__ usTableSize; } ;
struct TYPE_9__ {scalar_t__ usExtendendedHeaderOffset; } ;
typedef  TYPE_3__ ATOM_PPLIB_POWERPLAYTABLE3 ;
typedef  TYPE_4__ ATOM_PPLIB_POWERPLAYTABLE ;
typedef  TYPE_5__ ATOM_PPLIB_EXTENDEDHEADER ;
typedef  int /*<<< orphan*/  ATOM_FIRMWARE_INFO_V2_1 ;

/* Variables and functions */
 int le16_to_cpu (scalar_t__) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_overdrive_limits_V2_1(struct pp_hwmgr *hwmgr,
			const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table,
			const ATOM_FIRMWARE_INFO_V2_1 *fw_info)
{
	const ATOM_PPLIB_POWERPLAYTABLE3 *powerplay_table3;
	const ATOM_PPLIB_EXTENDEDHEADER *header;

	if (le16_to_cpu(powerplay_table->usTableSize) <
	    sizeof(ATOM_PPLIB_POWERPLAYTABLE3))
		return 0;

	powerplay_table3 = (const ATOM_PPLIB_POWERPLAYTABLE3 *)powerplay_table;

	if (0 == powerplay_table3->usExtendendedHeaderOffset)
		return 0;

	header = (ATOM_PPLIB_EXTENDEDHEADER *)(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table3->usExtendendedHeaderOffset));

	hwmgr->platform_descriptor.overdriveLimit.engineClock = le32_to_cpu(header->ulMaxEngineClock);
	hwmgr->platform_descriptor.overdriveLimit.memoryClock = le32_to_cpu(header->ulMaxMemoryClock);


	hwmgr->platform_descriptor.minOverdriveVDDC = 0;
	hwmgr->platform_descriptor.maxOverdriveVDDC = 0;
	hwmgr->platform_descriptor.overdriveVDDCStep = 0;

	return 0;
}