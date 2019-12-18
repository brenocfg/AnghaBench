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
struct smu8_smumgr {int /*<<< orphan*/  toc_entry_used_count; int /*<<< orphan*/  toc_entry_initialize_index; } ;
struct pp_hwmgr {scalar_t__ chip_id; struct smu8_smumgr* smu_backend; } ;

/* Variables and functions */
 scalar_t__ CHIP_STONEY ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1 ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2 ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA0 ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA1 ; 
 int /*<<< orphan*/  smu8_smu_populate_single_ucode_load_task (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu8_smu_construct_toc_for_bootup(struct pp_hwmgr *hwmgr)
{
	struct smu8_smumgr *smu8_smu = hwmgr->smu_backend;

	smu8_smu->toc_entry_initialize_index = smu8_smu->toc_entry_used_count;

	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA0, false);
	if (hwmgr->chip_id != CHIP_STONEY)
		smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA1, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1, false);
	if (hwmgr->chip_id != CHIP_STONEY)
		smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G, true);

	return 0;
}