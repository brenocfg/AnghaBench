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
struct TYPE_4__ {TYPE_1__* entry; } ;
struct vega12_smumgr {TYPE_2__ smu_tables; } ;
struct pp_hwmgr {struct vega12_smumgr* smu_backend; scalar_t__ adev; int /*<<< orphan*/  device; } ;
struct cgs_firmware_info {int /*<<< orphan*/  kptr; int /*<<< orphan*/  member_0; } ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  Watermarks_t ;
struct TYPE_3__ {int version; int size; scalar_t__ table; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  SmuMetrics_t ;
typedef  int /*<<< orphan*/  PPTable_t ;
typedef  int /*<<< orphan*/  OverDriveTable_t ;
typedef  int /*<<< orphan*/  AvfsFuseOverride_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  CGS_UCODE_ID_SMU ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t TABLE_AVFS_FUSE_OVERRIDE ; 
 size_t TABLE_OVERDRIVE ; 
 size_t TABLE_PMSTATUSLOG ; 
 size_t TABLE_PPTABLE ; 
 size_t TABLE_SMU_METRICS ; 
 size_t TABLE_WATERMARKS ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int cgs_get_firmware_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cgs_firmware_info*) ; 
 int /*<<< orphan*/  kfree (struct vega12_smumgr*) ; 
 struct vega12_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega12_smu_init(struct pp_hwmgr *hwmgr)
{
	struct vega12_smumgr *priv;
	unsigned long tools_size;
	struct cgs_firmware_info info = {0};
	int ret;

	ret = cgs_get_firmware_info(hwmgr->device, CGS_UCODE_ID_SMU,
				&info);
	if (ret || !info.kptr)
		return -EINVAL;

	priv = kzalloc(sizeof(struct vega12_smumgr), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	hwmgr->smu_backend = priv;

	/* allocate space for pptable */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
			sizeof(PPTable_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[TABLE_PPTABLE].handle,
			&priv->smu_tables.entry[TABLE_PPTABLE].mc_addr,
			&priv->smu_tables.entry[TABLE_PPTABLE].table);
	if (ret)
		goto free_backend;

	priv->smu_tables.entry[TABLE_PPTABLE].version = 0x01;
	priv->smu_tables.entry[TABLE_PPTABLE].size = sizeof(PPTable_t);

	/* allocate space for watermarks table */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
				      sizeof(Watermarks_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &priv->smu_tables.entry[TABLE_WATERMARKS].handle,
				      &priv->smu_tables.entry[TABLE_WATERMARKS].mc_addr,
				      &priv->smu_tables.entry[TABLE_WATERMARKS].table);

	if (ret)
		goto err0;

	priv->smu_tables.entry[TABLE_WATERMARKS].version = 0x01;
	priv->smu_tables.entry[TABLE_WATERMARKS].size = sizeof(Watermarks_t);

	tools_size = 0x19000;
	if (tools_size) {
		ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
					      tools_size,
					      PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VRAM,
					      &priv->smu_tables.entry[TABLE_PMSTATUSLOG].handle,
					      &priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr,
					      &priv->smu_tables.entry[TABLE_PMSTATUSLOG].table);
		if (ret)
			goto err1;

		priv->smu_tables.entry[TABLE_PMSTATUSLOG].version = 0x01;
		priv->smu_tables.entry[TABLE_PMSTATUSLOG].size = tools_size;
	}

	/* allocate space for AVFS Fuse table */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
				      sizeof(AvfsFuseOverride_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].handle,
				      &priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].mc_addr,
				      &priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].table);

	if (ret)
		goto err2;

	priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].version = 0x01;
	priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].size = sizeof(AvfsFuseOverride_t);

	/* allocate space for OverDrive table */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
				      sizeof(OverDriveTable_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
				      &priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
				      &priv->smu_tables.entry[TABLE_OVERDRIVE].table);
	if (ret)
		goto err3;

	priv->smu_tables.entry[TABLE_OVERDRIVE].version = 0x01;
	priv->smu_tables.entry[TABLE_OVERDRIVE].size = sizeof(OverDriveTable_t);

	/* allocate space for SMU_METRICS table */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
				      sizeof(SmuMetrics_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &priv->smu_tables.entry[TABLE_SMU_METRICS].handle,
				      &priv->smu_tables.entry[TABLE_SMU_METRICS].mc_addr,
				      &priv->smu_tables.entry[TABLE_SMU_METRICS].table);
	if (ret)
		goto err4;

	priv->smu_tables.entry[TABLE_SMU_METRICS].version = 0x01;
	priv->smu_tables.entry[TABLE_SMU_METRICS].size = sizeof(SmuMetrics_t);

	return 0;

err4:
	amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
				&priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
				&priv->smu_tables.entry[TABLE_OVERDRIVE].table);
err3:
	amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].handle,
				&priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].mc_addr,
				&priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].table);
err2:
	if (priv->smu_tables.entry[TABLE_PMSTATUSLOG].table)
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_PMSTATUSLOG].handle,
				&priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr,
				&priv->smu_tables.entry[TABLE_PMSTATUSLOG].table);
err1:
	amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_WATERMARKS].handle,
				&priv->smu_tables.entry[TABLE_WATERMARKS].mc_addr,
				&priv->smu_tables.entry[TABLE_WATERMARKS].table);
err0:
	amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_PPTABLE].handle,
			&priv->smu_tables.entry[TABLE_PPTABLE].mc_addr,
			&priv->smu_tables.entry[TABLE_PPTABLE].table);
free_backend:
	kfree(hwmgr->smu_backend);

	return -EINVAL;
}