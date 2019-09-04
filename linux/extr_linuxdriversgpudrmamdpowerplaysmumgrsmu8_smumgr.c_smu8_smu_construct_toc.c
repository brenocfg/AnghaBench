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
struct smu8_smumgr {scalar_t__ toc_entry_used_count; } ;
struct pp_hwmgr {struct smu8_smumgr* smu_backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  smu8_smu_construct_toc_for_bootup (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_smu_construct_toc_for_clock_table (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_smu_construct_toc_for_power_profiling (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_smu_construct_toc_for_rlc_aram_save (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_smu_construct_toc_for_vddgfx_enter (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_smu_construct_toc_for_vddgfx_exit (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_smu_initialize_toc_empty_job_list (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu8_smu_construct_toc(struct pp_hwmgr *hwmgr)
{
	struct smu8_smumgr *smu8_smu = hwmgr->smu_backend;

	smu8_smu->toc_entry_used_count = 0;
	smu8_smu_initialize_toc_empty_job_list(hwmgr);
	smu8_smu_construct_toc_for_rlc_aram_save(hwmgr);
	smu8_smu_construct_toc_for_vddgfx_enter(hwmgr);
	smu8_smu_construct_toc_for_vddgfx_exit(hwmgr);
	smu8_smu_construct_toc_for_power_profiling(hwmgr);
	smu8_smu_construct_toc_for_bootup(hwmgr);
	smu8_smu_construct_toc_for_clock_table(hwmgr);

	return 0;
}