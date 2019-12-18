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
struct TYPE_5__ {void* memoryClock; void* engineClock; } ;
struct TYPE_6__ {scalar_t__ overdriveVDDCStep; scalar_t__ maxOverdriveVDDC; scalar_t__ minOverdriveVDDC; TYPE_1__ overdriveLimit; } ;
struct pp_hwmgr {TYPE_2__ platform_descriptor; } ;
struct TYPE_7__ {int /*<<< orphan*/  ulMaxODMemoryClock; int /*<<< orphan*/  ulMaxODEngineClock; } ;
typedef  TYPE_3__ ATOM_Tonga_POWERPLAYTABLE ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_over_drive_limits(
		struct pp_hwmgr *hwmgr,
		const ATOM_Tonga_POWERPLAYTABLE *powerplay_table)
{
	hwmgr->platform_descriptor.overdriveLimit.engineClock =
		le32_to_cpu(powerplay_table->ulMaxODEngineClock);
	hwmgr->platform_descriptor.overdriveLimit.memoryClock =
		le32_to_cpu(powerplay_table->ulMaxODMemoryClock);

	hwmgr->platform_descriptor.minOverdriveVDDC = 0;
	hwmgr->platform_descriptor.maxOverdriveVDDC = 0;
	hwmgr->platform_descriptor.overdriveVDDCStep = 0;

	return 0;
}