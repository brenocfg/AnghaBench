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
struct smu10_hwmgr {int dummy; } ;
struct TYPE_3__ {int engineClock; int memoryClock; } ;
struct TYPE_4__ {int minimumClocksReductionPercentage; TYPE_1__ clockStep; scalar_t__ vbiosInterruptId; void* hardwarePerformanceLevels; void* hardwareActivityPerformanceLevels; } ;
struct pp_hwmgr {int pstate_sclk; int pstate_mclk; TYPE_2__ platform_descriptor; struct smu10_hwmgr* backend; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* SMU10_MAX_HARDWARE_POWERLEVELS ; 
 int SMU10_UMD_PSTATE_FCLK ; 
 int SMU10_UMD_PSTATE_GFXCLK ; 
 struct smu10_hwmgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smu10_construct_boot_state (struct pp_hwmgr*) ; 
 int smu10_get_system_info_data (struct pp_hwmgr*) ; 
 int smu10_initialize_dpm_defaults (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu10_populate_clock_table (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu10_hwmgr_backend_init(struct pp_hwmgr *hwmgr)
{
	int result = 0;
	struct smu10_hwmgr *data;

	data = kzalloc(sizeof(struct smu10_hwmgr), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	hwmgr->backend = data;

	result = smu10_initialize_dpm_defaults(hwmgr);
	if (result != 0) {
		pr_err("smu10_initialize_dpm_defaults failed\n");
		return result;
	}

	smu10_populate_clock_table(hwmgr);

	result = smu10_get_system_info_data(hwmgr);
	if (result != 0) {
		pr_err("smu10_get_system_info_data failed\n");
		return result;
	}

	smu10_construct_boot_state(hwmgr);

	hwmgr->platform_descriptor.hardwareActivityPerformanceLevels =
						SMU10_MAX_HARDWARE_POWERLEVELS;

	hwmgr->platform_descriptor.hardwarePerformanceLevels =
						SMU10_MAX_HARDWARE_POWERLEVELS;

	hwmgr->platform_descriptor.vbiosInterruptId = 0;

	hwmgr->platform_descriptor.clockStep.engineClock = 500;

	hwmgr->platform_descriptor.clockStep.memoryClock = 500;

	hwmgr->platform_descriptor.minimumClocksReductionPercentage = 50;

	hwmgr->pstate_sclk = SMU10_UMD_PSTATE_GFXCLK * 100;
	hwmgr->pstate_mclk = SMU10_UMD_PSTATE_FCLK * 100;

	return result;
}