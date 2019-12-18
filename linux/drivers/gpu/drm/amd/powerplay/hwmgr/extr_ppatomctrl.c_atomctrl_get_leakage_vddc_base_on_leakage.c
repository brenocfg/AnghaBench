#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u16 ;
struct pp_hwmgr {int /*<<< orphan*/  adev; } ;
struct TYPE_3__ {int ucTableFormatRevision; int ucTableContentRevision; int usStructureSize; } ;
struct TYPE_4__ {int usLeakageBinArrayOffset; int usElbVDDC_IdArrayOffset; int usElbVDDC_LevelArrayOffset; int ucElbVDDC_Num; int ucLeakageBinNum; int usElbVDDCI_IdArrayOffset; int usElbVDDCI_LevelArrayOffset; int ucElbVDDCI_Num; TYPE_1__ asHeader; } ;
typedef  TYPE_2__ ATOM_ASIC_PROFILING_INFO_V2_1 ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_ProfilingInfo ; 
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int atomctrl_get_leakage_vddc_base_on_leakage(struct pp_hwmgr *hwmgr,
					uint16_t *vddc, uint16_t *vddci,
					uint16_t virtual_voltage_id,
					uint16_t efuse_voltage_id)
{
	int i, j;
	int ix;
	u16 *leakage_bin, *vddc_id_buf, *vddc_buf, *vddci_id_buf, *vddci_buf;
	ATOM_ASIC_PROFILING_INFO_V2_1 *profile;

	*vddc = 0;
	*vddci = 0;

	ix = GetIndexIntoMasterTable(DATA, ASIC_ProfilingInfo);

	profile = (ATOM_ASIC_PROFILING_INFO_V2_1 *)
			smu_atom_get_data_table(hwmgr->adev,
					ix,
					NULL, NULL, NULL);
	if (!profile)
		return -EINVAL;

	if ((profile->asHeader.ucTableFormatRevision >= 2) &&
		(profile->asHeader.ucTableContentRevision >= 1) &&
		(profile->asHeader.usStructureSize >= sizeof(ATOM_ASIC_PROFILING_INFO_V2_1))) {
		leakage_bin = (u16 *)((char *)profile + profile->usLeakageBinArrayOffset);
		vddc_id_buf = (u16 *)((char *)profile + profile->usElbVDDC_IdArrayOffset);
		vddc_buf = (u16 *)((char *)profile + profile->usElbVDDC_LevelArrayOffset);
		if (profile->ucElbVDDC_Num > 0) {
			for (i = 0; i < profile->ucElbVDDC_Num; i++) {
				if (vddc_id_buf[i] == virtual_voltage_id) {
					for (j = 0; j < profile->ucLeakageBinNum; j++) {
						if (efuse_voltage_id <= leakage_bin[j]) {
							*vddc = vddc_buf[j * profile->ucElbVDDC_Num + i];
							break;
						}
					}
					break;
				}
			}
		}

		vddci_id_buf = (u16 *)((char *)profile + profile->usElbVDDCI_IdArrayOffset);
		vddci_buf   = (u16 *)((char *)profile + profile->usElbVDDCI_LevelArrayOffset);
		if (profile->ucElbVDDCI_Num > 0) {
			for (i = 0; i < profile->ucElbVDDCI_Num; i++) {
				if (vddci_id_buf[i] == virtual_voltage_id) {
					for (j = 0; j < profile->ucLeakageBinNum; j++) {
						if (efuse_voltage_id <= leakage_bin[j]) {
							*vddci = vddci_buf[j * profile->ucElbVDDCI_Num + i];
							break;
						}
					}
					break;
				}
			}
		}
	}

	return 0;
}