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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; scalar_t__ smu_backend; } ;
struct ci_smumgr {int /*<<< orphan*/  power_tune_table; } ;
struct SMU7_Discrete_PmFuses {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PowerContainment ; 
 int /*<<< orphan*/  PmFuseTable ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 scalar_t__ SMU7_FIRMWARE_HEADER_LOCATION ; 
 int /*<<< orphan*/  SMU7_Firmware_Header ; 
 int ci_copy_bytes_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ci_min_max_v_gnbl_pm_lid_from_bapm_vddc (struct pp_hwmgr*) ; 
 int ci_populate_bapm_vddc_base_leakage_sidd (struct pp_hwmgr*) ; 
 int ci_populate_bapm_vddc_vid_sidd (struct pp_hwmgr*) ; 
 int ci_populate_dw8 (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int ci_populate_fuzzy_fan (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int ci_populate_svi_load_line (struct pp_hwmgr*) ; 
 int ci_populate_tdc_limit (struct pp_hwmgr*) ; 
 int ci_populate_vddc_vid (struct pp_hwmgr*) ; 
 scalar_t__ ci_read_smc_sram_dword (struct pp_hwmgr*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ci_populate_pm_fuses(struct pp_hwmgr *hwmgr)
{
	struct ci_smumgr *smu_data = (struct ci_smumgr *)(hwmgr->smu_backend);
	uint32_t pm_fuse_table_offset;
	int ret = 0;

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_PowerContainment)) {
		if (ci_read_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU7_Firmware_Header, PmFuseTable),
				&pm_fuse_table_offset, SMC_RAM_END)) {
			pr_err("Attempt to get pm_fuse_table_offset Failed!\n");
			return -EINVAL;
		}

		/* DW0 - DW3 */
		ret = ci_populate_bapm_vddc_vid_sidd(hwmgr);
		/* DW4 - DW5 */
		ret |= ci_populate_vddc_vid(hwmgr);
		/* DW6 */
		ret |= ci_populate_svi_load_line(hwmgr);
		/* DW7 */
		ret |= ci_populate_tdc_limit(hwmgr);
		/* DW8 */
		ret |= ci_populate_dw8(hwmgr, pm_fuse_table_offset);

		ret |= ci_populate_fuzzy_fan(hwmgr, pm_fuse_table_offset);

		ret |= ci_min_max_v_gnbl_pm_lid_from_bapm_vddc(hwmgr);

		ret |= ci_populate_bapm_vddc_base_leakage_sidd(hwmgr);
		if (ret)
			return ret;

		ret = ci_copy_bytes_to_smc(hwmgr, pm_fuse_table_offset,
				(uint8_t *)&smu_data->power_tune_table,
				sizeof(struct SMU7_Discrete_PmFuses), SMC_RAM_END);
	}
	return ret;
}