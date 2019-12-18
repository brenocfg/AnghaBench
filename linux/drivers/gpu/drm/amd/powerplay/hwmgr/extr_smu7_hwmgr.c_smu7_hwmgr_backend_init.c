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
struct smu7_hwmgr {int is_tlu_enabled; int pcie_gen_cap; int pcie_spc_cap; int /*<<< orphan*/  pcie_lane_cap; } ;
struct TYPE_5__ {int engineClock; int memoryClock; } ;
struct TYPE_6__ {int hardwarePerformanceLevels; int minimumClocksReductionPercentage; int vbiosInterruptId; TYPE_2__ clockStep; int /*<<< orphan*/  hardwareActivityPerformanceLevels; int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {scalar_t__ pp_table_version; TYPE_3__ platform_descriptor; struct amdgpu_device* adev; struct smu7_hwmgr* backend; } ;
struct TYPE_4__ {int pcie_gen_mask; int /*<<< orphan*/  pcie_mlw_mask; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PHM_PlatformCaps_EVV ; 
 scalar_t__ PP_TABLE_V0 ; 
 scalar_t__ PP_TABLE_V1 ; 
 int /*<<< orphan*/  SMU7_MAX_HARDWARE_POWERLEVELS ; 
 struct smu7_hwmgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phm_initializa_dynamic_state_adjustment_rule_settings (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smu7_complete_dependency_tables (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_get_elb_voltages (struct pp_hwmgr*) ; 
 int smu7_get_evv_voltages (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_hwmgr_backend_fini (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_init_dpm_defaults (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_patch_dependency_tables_with_leakage (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_patch_voltage_workaround (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_set_private_data_based_on_pptable_v0 (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_set_private_data_based_on_pptable_v1 (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_thermal_parameter_init (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu7_hwmgr_backend_init(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data;
	int result = 0;

	data = kzalloc(sizeof(struct smu7_hwmgr), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	hwmgr->backend = data;
	smu7_patch_voltage_workaround(hwmgr);
	smu7_init_dpm_defaults(hwmgr);

	/* Get leakage voltage based on leakage ID. */
	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_EVV)) {
		result = smu7_get_evv_voltages(hwmgr);
		if (result) {
			pr_info("Get EVV Voltage Failed.  Abort Driver loading!\n");
			return -EINVAL;
		}
	} else {
		smu7_get_elb_voltages(hwmgr);
	}

	if (hwmgr->pp_table_version == PP_TABLE_V1) {
		smu7_complete_dependency_tables(hwmgr);
		smu7_set_private_data_based_on_pptable_v1(hwmgr);
	} else if (hwmgr->pp_table_version == PP_TABLE_V0) {
		smu7_patch_dependency_tables_with_leakage(hwmgr);
		smu7_set_private_data_based_on_pptable_v0(hwmgr);
	}

	/* Initalize Dynamic State Adjustment Rule Settings */
	result = phm_initializa_dynamic_state_adjustment_rule_settings(hwmgr);

	if (0 == result) {
		struct amdgpu_device *adev = hwmgr->adev;

		data->is_tlu_enabled = false;

		hwmgr->platform_descriptor.hardwareActivityPerformanceLevels =
							SMU7_MAX_HARDWARE_POWERLEVELS;
		hwmgr->platform_descriptor.hardwarePerformanceLevels = 2;
		hwmgr->platform_descriptor.minimumClocksReductionPercentage = 50;

		data->pcie_gen_cap = adev->pm.pcie_gen_mask;
		if (data->pcie_gen_cap & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)
			data->pcie_spc_cap = 20;
		data->pcie_lane_cap = adev->pm.pcie_mlw_mask;

		hwmgr->platform_descriptor.vbiosInterruptId = 0x20000400; /* IRQ_SOURCE1_SW_INT */
/* The true clock step depends on the frequency, typically 4.5 or 9 MHz. Here we use 5. */
		hwmgr->platform_descriptor.clockStep.engineClock = 500;
		hwmgr->platform_descriptor.clockStep.memoryClock = 500;
		smu7_thermal_parameter_init(hwmgr);
	} else {
		/* Ignore return value in here, we are cleaning up a mess. */
		smu7_hwmgr_backend_fini(hwmgr);
	}

	return 0;
}