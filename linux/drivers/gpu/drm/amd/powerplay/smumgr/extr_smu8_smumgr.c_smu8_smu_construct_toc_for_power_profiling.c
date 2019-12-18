#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smu8_smumgr {int /*<<< orphan*/  toc_entry_used_count; int /*<<< orphan*/  toc_entry_power_profiling_index; } ;
struct pp_hwmgr {struct smu8_smumgr* smu_backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING ; 
 int /*<<< orphan*/  TASK_TYPE_INITIALIZE ; 
 int /*<<< orphan*/  smu8_smu_populate_single_scratch_task (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu8_smu_construct_toc_for_power_profiling(struct pp_hwmgr *hwmgr)
{
	struct smu8_smumgr *smu8_smu = hwmgr->smu_backend;

	smu8_smu->toc_entry_power_profiling_index = smu8_smu->toc_entry_used_count;

	smu8_smu_populate_single_scratch_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING,
				TASK_TYPE_INITIALIZE, true);
	return 0;
}