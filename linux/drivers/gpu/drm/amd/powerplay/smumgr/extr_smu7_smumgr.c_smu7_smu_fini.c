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
struct TYPE_4__ {int /*<<< orphan*/  kaddr; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  kaddr; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;
struct smu7_smumgr {int /*<<< orphan*/ * toc; TYPE_2__ smu_buffer; TYPE_1__ header_buffer; } ;
struct pp_hwmgr {int /*<<< orphan*/ * smu_backend; scalar_t__ not_vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

int smu7_smu_fini(struct pp_hwmgr *hwmgr)
{
	struct smu7_smumgr *smu_data = (struct smu7_smumgr *)(hwmgr->smu_backend);

	amdgpu_bo_free_kernel(&smu_data->header_buffer.handle,
					&smu_data->header_buffer.mc_addr,
					&smu_data->header_buffer.kaddr);

	if (hwmgr->not_vf)
		amdgpu_bo_free_kernel(&smu_data->smu_buffer.handle,
					&smu_data->smu_buffer.mc_addr,
					&smu_data->smu_buffer.kaddr);


	kfree(smu_data->toc);
	smu_data->toc = NULL;
	kfree(hwmgr->smu_backend);
	hwmgr->smu_backend = NULL;
	return 0;
}