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
struct TYPE_4__ {int data_size; int /*<<< orphan*/  kaddr; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {int data_size; int /*<<< orphan*/  kaddr; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;
struct smu8_smumgr {TYPE_2__ toc_buffer; TYPE_1__ smu_buffer; int /*<<< orphan*/  scratch_buffer_length; int /*<<< orphan*/ * scratch_buffer; } ;
struct pp_hwmgr {scalar_t__ adev; struct smu8_smumgr* smu_backend; } ;
struct amdgpu_device {int dummy; } ;
struct SMU8_MultimediaPowerLogData {int dummy; } ;
struct SMU8_Fusion_ClkTable {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM ; 
 int /*<<< orphan*/  SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM ; 
 int UCODE_ID_RLC_SCRATCH_SIZE_BYTE ; 
 int UCODE_ID_RLC_SRM_ARAM_SIZE_BYTE ; 
 int UCODE_ID_RLC_SRM_DRAM_SIZE_BYTE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct smu8_smumgr*) ; 
 struct smu8_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ smu8_smu_populate_single_scratch_entry (struct pp_hwmgr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smu8_smu_init(struct pp_hwmgr *hwmgr)
{
	int ret = 0;
	struct smu8_smumgr *smu8_smu;

	smu8_smu = kzalloc(sizeof(struct smu8_smumgr), GFP_KERNEL);
	if (smu8_smu == NULL)
		return -ENOMEM;

	hwmgr->smu_backend = smu8_smu;

	smu8_smu->toc_buffer.data_size = 4096;
	smu8_smu->smu_buffer.data_size =
		ALIGN(UCODE_ID_RLC_SCRATCH_SIZE_BYTE, 32) +
		ALIGN(UCODE_ID_RLC_SRM_ARAM_SIZE_BYTE, 32) +
		ALIGN(UCODE_ID_RLC_SRM_DRAM_SIZE_BYTE, 32) +
		ALIGN(sizeof(struct SMU8_MultimediaPowerLogData), 32) +
		ALIGN(sizeof(struct SMU8_Fusion_ClkTable), 32);

	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
				smu8_smu->toc_buffer.data_size,
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VRAM,
				&smu8_smu->toc_buffer.handle,
				&smu8_smu->toc_buffer.mc_addr,
				&smu8_smu->toc_buffer.kaddr);
	if (ret)
		goto err2;

	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
				smu8_smu->smu_buffer.data_size,
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VRAM,
				&smu8_smu->smu_buffer.handle,
				&smu8_smu->smu_buffer.mc_addr,
				&smu8_smu->smu_buffer.kaddr);
	if (ret)
		goto err1;

	if (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH,
		UCODE_ID_RLC_SCRATCH_SIZE_BYTE,
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) {
		pr_err("Error when Populate Firmware Entry.\n");
		goto err0;
	}

	if (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM,
		UCODE_ID_RLC_SRM_ARAM_SIZE_BYTE,
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) {
		pr_err("Error when Populate Firmware Entry.\n");
		goto err0;
	}
	if (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM,
		UCODE_ID_RLC_SRM_DRAM_SIZE_BYTE,
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) {
		pr_err("Error when Populate Firmware Entry.\n");
		goto err0;
	}

	if (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING,
		sizeof(struct SMU8_MultimediaPowerLogData),
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) {
		pr_err("Error when Populate Firmware Entry.\n");
		goto err0;
	}

	if (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE,
		sizeof(struct SMU8_Fusion_ClkTable),
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) {
		pr_err("Error when Populate Firmware Entry.\n");
		goto err0;
	}

	return 0;

err0:
	amdgpu_bo_free_kernel(&smu8_smu->smu_buffer.handle,
				&smu8_smu->smu_buffer.mc_addr,
				&smu8_smu->smu_buffer.kaddr);
err1:
	amdgpu_bo_free_kernel(&smu8_smu->toc_buffer.handle,
				&smu8_smu->toc_buffer.mc_addr,
				&smu8_smu->toc_buffer.kaddr);
err2:
	kfree(smu8_smu);
	return -EINVAL;
}