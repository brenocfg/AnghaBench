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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pp_hwmgr {int /*<<< orphan*/  adev; } ;
struct TYPE_2__ {int /*<<< orphan*/  usReferenceClock; } ;
typedef  TYPE_1__ ATOM_FIRMWARE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  FirmwareInfo ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

uint32_t atomctrl_get_reference_clock(struct pp_hwmgr *hwmgr)
{
	ATOM_FIRMWARE_INFO *fw_info;
	u8 frev, crev;
	u16 size;
	uint32_t clock;

	fw_info = (ATOM_FIRMWARE_INFO *)
		smu_atom_get_data_table(hwmgr->adev,
			GetIndexIntoMasterTable(DATA, FirmwareInfo),
			&size, &frev, &crev);

	if (fw_info == NULL)
		clock = 2700;
	else
		clock = (uint32_t)(le16_to_cpu(fw_info->usReferenceClock));

	return clock;
}