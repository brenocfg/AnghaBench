#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct psp_context {void* tmr_buf; void* fw_pri_buf; void* fence_buf; void* asd_shared_buf; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  cmd_buf_mem; int /*<<< orphan*/  cmd_buf_mc_addr; int /*<<< orphan*/  cmd_buf_bo; int /*<<< orphan*/  asd_shared_mc_addr; int /*<<< orphan*/  asd_shared_bo; int /*<<< orphan*/  fence_buf_mc_addr; int /*<<< orphan*/  fence_buf_bo; int /*<<< orphan*/  fw_pri_mc_addr; int /*<<< orphan*/  fw_pri_bo; int /*<<< orphan*/  tmr_mc_addr; int /*<<< orphan*/  tmr_bo; } ;
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_1__ firmware; struct psp_context psp; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int /*<<< orphan*/  PSP_RING_TYPE__KM ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_ucode_fini_bo (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psp_ring_destroy (struct psp_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct psp_context *psp = &adev->psp;

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		return 0;

	amdgpu_ucode_fini_bo(adev);

	psp_ring_destroy(psp, PSP_RING_TYPE__KM);

	amdgpu_bo_free_kernel(&psp->tmr_bo, &psp->tmr_mc_addr, &psp->tmr_buf);
	amdgpu_bo_free_kernel(&psp->fw_pri_bo,
			      &psp->fw_pri_mc_addr, &psp->fw_pri_buf);
	amdgpu_bo_free_kernel(&psp->fence_buf_bo,
			      &psp->fence_buf_mc_addr, &psp->fence_buf);
	amdgpu_bo_free_kernel(&psp->asd_shared_bo, &psp->asd_shared_mc_addr,
			      &psp->asd_shared_buf);
	amdgpu_bo_free_kernel(&psp->cmd_buf_bo, &psp->cmd_buf_mc_addr,
			      (void **)&psp->cmd_buf_mem);

	kfree(psp->cmd);
	psp->cmd = NULL;

	return 0;
}