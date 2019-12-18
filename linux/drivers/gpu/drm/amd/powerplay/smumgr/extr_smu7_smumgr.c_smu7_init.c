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
struct smu7_smumgr {TYPE_2__ header_buffer; TYPE_1__ smu_buffer; } ;
struct pp_hwmgr {int feature_mask; int avfs_supported; scalar_t__ adev; int /*<<< orphan*/  not_vf; scalar_t__ smu_backend; } ;
struct amdgpu_device {int dummy; } ;
struct SMU_DRAMData_TOC {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PP_AVFS_MASK ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ smum_is_hw_avfs_present (struct pp_hwmgr*) ; 

int smu7_init(struct pp_hwmgr *hwmgr)
{
	struct smu7_smumgr *smu_data;
	int r;
	/* Allocate memory for backend private data */
	smu_data = (struct smu7_smumgr *)(hwmgr->smu_backend);
	smu_data->header_buffer.data_size =
			((sizeof(struct SMU_DRAMData_TOC) / 4096) + 1) * 4096;

/* Allocate FW image data structure and header buffer and
 * send the header buffer address to SMU */
	r = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
		smu_data->header_buffer.data_size,
		PAGE_SIZE,
		AMDGPU_GEM_DOMAIN_VRAM,
		&smu_data->header_buffer.handle,
		&smu_data->header_buffer.mc_addr,
		&smu_data->header_buffer.kaddr);

	if (r)
		return -EINVAL;

	if (!hwmgr->not_vf)
		return 0;

	smu_data->smu_buffer.data_size = 200*4096;
	r = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
		smu_data->smu_buffer.data_size,
		PAGE_SIZE,
		AMDGPU_GEM_DOMAIN_VRAM,
		&smu_data->smu_buffer.handle,
		&smu_data->smu_buffer.mc_addr,
		&smu_data->smu_buffer.kaddr);

	if (r) {
		amdgpu_bo_free_kernel(&smu_data->header_buffer.handle,
					&smu_data->header_buffer.mc_addr,
					&smu_data->header_buffer.kaddr);
		return -EINVAL;
	}

	if (smum_is_hw_avfs_present(hwmgr) &&
	    (hwmgr->feature_mask & PP_AVFS_MASK))
		hwmgr->avfs_supported = true;

	return 0;
}