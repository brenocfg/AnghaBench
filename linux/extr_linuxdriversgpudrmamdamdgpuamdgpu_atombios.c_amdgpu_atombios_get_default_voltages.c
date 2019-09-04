#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  usBootUpMVDDCVoltage; int /*<<< orphan*/  usBootUpVDDCIVoltage; } ;
struct TYPE_4__ {int /*<<< orphan*/  usBootUpVDDCVoltage; } ;
union firmware_info {TYPE_2__ info_22; TYPE_1__ info_14; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct amdgpu_mode_info {TYPE_3__* atom_context; } ;
struct amdgpu_device {struct amdgpu_mode_info mode_info; } ;
struct TYPE_6__ {scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  FirmwareInfo ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_3__*,int,int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

void amdgpu_atombios_get_default_voltages(struct amdgpu_device *adev,
					  u16 *vddc, u16 *vddci, u16 *mvdd)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, FirmwareInfo);
	u8 frev, crev;
	u16 data_offset;
	union firmware_info *firmware_info;

	*vddc = 0;
	*vddci = 0;
	*mvdd = 0;

	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		firmware_info =
			(union firmware_info *)(mode_info->atom_context->bios +
						data_offset);
		*vddc = le16_to_cpu(firmware_info->info_14.usBootUpVDDCVoltage);
		if ((frev == 2) && (crev >= 2)) {
			*vddci = le16_to_cpu(firmware_info->info_22.usBootUpVDDCIVoltage);
			*mvdd = le16_to_cpu(firmware_info->info_22.usBootUpMVDDCVoltage);
		}
	}
}