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
struct pp_hwmgr {struct vega10_smumgr* smu_backend; } ;
struct TYPE_3__ {scalar_t__ table; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 size_t AVFSFUSETABLE ; 
 size_t AVFSTABLE ; 
 size_t PPTABLE ; 
 size_t TOOLSTABLE ; 
 size_t WMTABLE ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (struct vega10_smumgr*) ; 

__attribute__((used)) static int vega10_smu_fini(struct pp_hwmgr *hwmgr)
{
	struct vega10_smumgr *priv = hwmgr->smu_backend;

	if (priv) {
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[PPTABLE].handle,
				&priv->smu_tables.entry[PPTABLE].mc_addr,
				&priv->smu_tables.entry[PPTABLE].table);
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[WMTABLE].handle,
					&priv->smu_tables.entry[WMTABLE].mc_addr,
					&priv->smu_tables.entry[WMTABLE].table);
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[AVFSTABLE].handle,
					&priv->smu_tables.entry[AVFSTABLE].mc_addr,
					&priv->smu_tables.entry[AVFSTABLE].table);
		if (priv->smu_tables.entry[TOOLSTABLE].table)
			amdgpu_bo_free_kernel(&priv->smu_tables.entry[TOOLSTABLE].handle,
					&priv->smu_tables.entry[TOOLSTABLE].mc_addr,
					&priv->smu_tables.entry[TOOLSTABLE].table);
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[AVFSFUSETABLE].handle,
					&priv->smu_tables.entry[AVFSFUSETABLE].mc_addr,
					&priv->smu_tables.entry[AVFSFUSETABLE].table);
		kfree(hwmgr->smu_backend);
		hwmgr->smu_backend = NULL;
	}
	return 0;
}