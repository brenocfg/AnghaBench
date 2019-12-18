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
struct TYPE_3__ {int /*<<< orphan*/  kaddr; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  kaddr; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  handle; } ;
struct smu8_smumgr {TYPE_1__ smu_buffer; TYPE_2__ toc_buffer; } ;
struct pp_hwmgr {struct smu8_smumgr* smu_backend; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct smu8_smumgr*) ; 

__attribute__((used)) static int smu8_smu_fini(struct pp_hwmgr *hwmgr)
{
	struct smu8_smumgr *smu8_smu;

	if (hwmgr == NULL || hwmgr->device == NULL)
		return -EINVAL;

	smu8_smu = hwmgr->smu_backend;
	if (smu8_smu) {
		amdgpu_bo_free_kernel(&smu8_smu->toc_buffer.handle,
					&smu8_smu->toc_buffer.mc_addr,
					&smu8_smu->toc_buffer.kaddr);
		amdgpu_bo_free_kernel(&smu8_smu->smu_buffer.handle,
					&smu8_smu->smu_buffer.mc_addr,
					&smu8_smu->smu_buffer.kaddr);
		kfree(smu8_smu);
	}

	return 0;
}