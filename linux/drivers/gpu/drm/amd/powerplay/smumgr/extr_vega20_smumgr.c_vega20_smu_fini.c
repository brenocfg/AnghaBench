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
struct vega20_smumgr {TYPE_2__ smu_tables; } ;
struct pp_hwmgr {int /*<<< orphan*/ * smu_backend; } ;
struct TYPE_3__ {int /*<<< orphan*/  table; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 size_t TABLE_ACTIVITY_MONITOR_COEFF ; 
 size_t TABLE_OVERDRIVE ; 
 size_t TABLE_PMSTATUSLOG ; 
 size_t TABLE_PPTABLE ; 
 size_t TABLE_SMU_METRICS ; 
 size_t TABLE_WATERMARKS ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega20_smu_fini(struct pp_hwmgr *hwmgr)
{
	struct vega20_smumgr *priv =
			(struct vega20_smumgr *)(hwmgr->smu_backend);

	if (priv) {
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_PPTABLE].handle,
				&priv->smu_tables.entry[TABLE_PPTABLE].mc_addr,
				&priv->smu_tables.entry[TABLE_PPTABLE].table);
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_WATERMARKS].handle,
				&priv->smu_tables.entry[TABLE_WATERMARKS].mc_addr,
				&priv->smu_tables.entry[TABLE_WATERMARKS].table);
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_PMSTATUSLOG].handle,
				&priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr,
				&priv->smu_tables.entry[TABLE_PMSTATUSLOG].table);
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
				&priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
				&priv->smu_tables.entry[TABLE_OVERDRIVE].table);
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_SMU_METRICS].handle,
				&priv->smu_tables.entry[TABLE_SMU_METRICS].mc_addr,
				&priv->smu_tables.entry[TABLE_SMU_METRICS].table);
		amdgpu_bo_free_kernel(&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].handle,
				&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].mc_addr,
				&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].table);
		kfree(hwmgr->smu_backend);
		hwmgr->smu_backend = NULL;
	}
	return 0;
}