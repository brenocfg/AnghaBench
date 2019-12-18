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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_4__ {TYPE_3__* atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_6__ {int bios; } ;
struct TYPE_5__ {int ucElbVDDC_Num; int ucLeakageBinNum; int ucElbVDDCI_Num; int /*<<< orphan*/  usElbVDDCI_LevelArrayOffset; int /*<<< orphan*/  usElbVDDCI_IdArrayOffset; int /*<<< orphan*/  usElbVDDC_LevelArrayOffset; int /*<<< orphan*/  usElbVDDC_IdArrayOffset; int /*<<< orphan*/  usLeakageBinArrayOffset; } ;
typedef  TYPE_2__ ATOM_ASIC_PROFILING_INFO_V2_1 ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_ProfilingInfo ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_data_header (TYPE_3__*,int,int*,int*,int*,int*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

int amdgpu_atombios_get_leakage_vddc_based_on_leakage_params(struct amdgpu_device *adev,
							     u16 *vddc, u16 *vddci,
							     u16 virtual_voltage_id,
							     u16 vbios_voltage_id)
{
	int index = GetIndexIntoMasterTable(DATA, ASIC_ProfilingInfo);
	u8 frev, crev;
	u16 data_offset, size;
	int i, j;
	ATOM_ASIC_PROFILING_INFO_V2_1 *profile;
	u16 *leakage_bin, *vddc_id_buf, *vddc_buf, *vddci_id_buf, *vddci_buf;

	*vddc = 0;
	*vddci = 0;

	if (!amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, &size,
				    &frev, &crev, &data_offset))
		return -EINVAL;

	profile = (ATOM_ASIC_PROFILING_INFO_V2_1 *)
		(adev->mode_info.atom_context->bios + data_offset);

	switch (frev) {
	case 1:
		return -EINVAL;
	case 2:
		switch (crev) {
		case 1:
			if (size < sizeof(ATOM_ASIC_PROFILING_INFO_V2_1))
				return -EINVAL;
			leakage_bin = (u16 *)
				(adev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usLeakageBinArrayOffset));
			vddc_id_buf = (u16 *)
				(adev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usElbVDDC_IdArrayOffset));
			vddc_buf = (u16 *)
				(adev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usElbVDDC_LevelArrayOffset));
			vddci_id_buf = (u16 *)
				(adev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usElbVDDCI_IdArrayOffset));
			vddci_buf = (u16 *)
				(adev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usElbVDDCI_LevelArrayOffset));

			if (profile->ucElbVDDC_Num > 0) {
				for (i = 0; i < profile->ucElbVDDC_Num; i++) {
					if (vddc_id_buf[i] == virtual_voltage_id) {
						for (j = 0; j < profile->ucLeakageBinNum; j++) {
							if (vbios_voltage_id <= leakage_bin[j]) {
								*vddc = vddc_buf[j * profile->ucElbVDDC_Num + i];
								break;
							}
						}
						break;
					}
				}
			}
			if (profile->ucElbVDDCI_Num > 0) {
				for (i = 0; i < profile->ucElbVDDCI_Num; i++) {
					if (vddci_id_buf[i] == virtual_voltage_id) {
						for (j = 0; j < profile->ucLeakageBinNum; j++) {
							if (vbios_voltage_id <= leakage_bin[j]) {
								*vddci = vddci_buf[j * profile->ucElbVDDCI_Num + i];
								break;
							}
						}
						break;
					}
				}
			}
			break;
		default:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			return -EINVAL;
		}
		break;
	default:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		return -EINVAL;
	}

	return 0;
}