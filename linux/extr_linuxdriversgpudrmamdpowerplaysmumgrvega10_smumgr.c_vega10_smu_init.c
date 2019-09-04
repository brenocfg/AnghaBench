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
struct vega10_smumgr {TYPE_2__ smu_tables; } ;
struct pp_hwmgr {struct vega10_smumgr* smu_backend; scalar_t__ adev; int /*<<< orphan*/  device; } ;
struct cgs_firmware_info {int /*<<< orphan*/  kptr; int /*<<< orphan*/  member_0; } ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  Watermarks_t ;
struct TYPE_3__ {int version; int size; scalar_t__ table; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; int /*<<< orphan*/  table_id; } ;
typedef  int /*<<< orphan*/  PPTable_t ;
typedef  int /*<<< orphan*/  AvfsTable_t ;
typedef  int /*<<< orphan*/  AvfsFuseOverride_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 size_t AVFSFUSETABLE ; 
 size_t AVFSTABLE ; 
 int /*<<< orphan*/  CGS_UCODE_ID_SMU ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t PPTABLE ; 
 int /*<<< orphan*/  TABLE_AVFS ; 
 int /*<<< orphan*/  TABLE_AVFS_FUSE_OVERRIDE ; 
 int /*<<< orphan*/  TABLE_PMSTATUSLOG ; 
 int /*<<< orphan*/  TABLE_PPTABLE ; 
 int /*<<< orphan*/  TABLE_WATERMARKS ; 
 size_t TOOLSTABLE ; 
 size_t WMTABLE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int cgs_get_firmware_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cgs_firmware_info*) ; 
 int /*<<< orphan*/  kfree (struct vega10_smumgr*) ; 
 struct vega10_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_smu_init(struct pp_hwmgr *hwmgr)
{
	struct vega10_smumgr *priv;
	unsigned long tools_size;
	int ret;
	struct cgs_firmware_info info = {0};

	ret = cgs_get_firmware_info(hwmgr->device,
				    CGS_UCODE_ID_SMU,
				    &info);
	if (ret || !info.kptr)
		return -EINVAL;

	priv = kzalloc(sizeof(struct vega10_smumgr), GFP_KERNEL);

	if (!priv)
		return -ENOMEM;

	hwmgr->smu_backend = priv;

	/* allocate space for pptable */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
			sizeof(PPTable_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[PPTABLE].handle,
			&priv->smu_tables.entry[PPTABLE].mc_addr,
			&priv->smu_tables.entry[PPTABLE].table);
	if (ret)
		goto free_backend;

	priv->smu_tables.entry[PPTABLE].version = 0x01;
	priv->smu_tables.entry[PPTABLE].size = sizeof(PPTable_t);
	priv->smu_tables.entry[PPTABLE].table_id = TABLE_PPTABLE;

	/* allocate space for watermarks table */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
			sizeof(Watermarks_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[WMTABLE].handle,
			&priv->smu_tables.entry[WMTABLE].mc_addr,
			&priv->smu_tables.entry[WMTABLE].table);

	if (ret)
		goto err0;

	priv->smu_tables.entry[WMTABLE].version = 0x01;
	priv->smu_tables.entry[WMTABLE].size = sizeof(Watermarks_t);
	priv->smu_tables.entry[WMTABLE].table_id = TABLE_WATERMARKS;

	/* allocate space for AVFS table */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
			sizeof(AvfsTable_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[AVFSTABLE].handle,
			&priv->smu_tables.entry[AVFSTABLE].mc_addr,
			&priv->smu_tables.entry[AVFSTABLE].table);

	if (ret)
		goto err1;

	priv->smu_tables.entry[AVFSTABLE].version = 0x01;
	priv->smu_tables.entry[AVFSTABLE].size = sizeof(AvfsTable_t);
	priv->smu_tables.entry[AVFSTABLE].table_id = TABLE_AVFS;

	tools_size = 0x19000;
	if (tools_size) {
		ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
				tools_size,
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VRAM,
				&priv->smu_tables.entry[TOOLSTABLE].handle,
				&priv->smu_tables.entry[TOOLSTABLE].mc_addr,
				&priv->smu_tables.entry[TOOLSTABLE].table);
		if (ret)
			goto err2;
		priv->smu_tables.entry[TOOLSTABLE].version = 0x01;
		priv->smu_tables.entry[TOOLSTABLE].size = tools_size;
		priv->smu_tables.entry[TOOLSTABLE].table_id = TABLE_PMSTATUSLOG;
	}

	/* allocate space for AVFS Fuse table */
	ret = amdgpu_bo_create_kernel((struct amdgpu_device *)hwmgr->adev,
			sizeof(AvfsFuseOverride_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[AVFSFUSETABLE].handle,
			&priv->smu_tables.entry[AVFSFUSETABLE].mc_addr,
			&priv->smu_tables.entry[AVFSFUSETABLE].table);
	if (ret)
		goto err3;

	priv->smu_tables.entry[AVFSFUSETABLE].version = 0x01;
	priv->smu_tables.entry[AVFSFUSETABLE].size = sizeof(AvfsFuseOverride_t);
	priv->smu_tables.entry[AVFSFUSETABLE].table_id = TABLE_AVFS_FUSE_OVERRIDE;


	return 0;

err3:
	if (priv->smu_tables.entry[TOOLSTABLE].table)
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[TOOLSTABLE].handle,
				&priv->smu_tables.entry[TOOLSTABLE].mc_addr,
				&priv->smu_tables.entry[TOOLSTABLE].table);
err2:
	amdgpu_bo_free_kernel(&priv->smu_tables.entry[AVFSTABLE].handle,
				&priv->smu_tables.entry[AVFSTABLE].mc_addr,
				&priv->smu_tables.entry[AVFSTABLE].table);
err1:
	amdgpu_bo_free_kernel(&priv->smu_tables.entry[WMTABLE].handle,
				&priv->smu_tables.entry[WMTABLE].mc_addr,
				&priv->smu_tables.entry[WMTABLE].table);
err0:
	amdgpu_bo_free_kernel(&priv->smu_tables.entry[PPTABLE].handle,
			&priv->smu_tables.entry[PPTABLE].mc_addr,
			&priv->smu_tables.entry[PPTABLE].table);
free_backend:
	kfree(hwmgr->smu_backend);

	return -EINVAL;
}