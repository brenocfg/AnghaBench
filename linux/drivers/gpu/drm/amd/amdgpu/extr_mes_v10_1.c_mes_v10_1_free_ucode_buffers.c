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
struct TYPE_2__ {int /*<<< orphan*/  ucode_fw_ptr; int /*<<< orphan*/  ucode_fw_gpu_addr; int /*<<< orphan*/  ucode_fw_obj; int /*<<< orphan*/  data_fw_ptr; int /*<<< orphan*/  data_fw_gpu_addr; int /*<<< orphan*/  data_fw_obj; } ;
struct amdgpu_device {TYPE_1__ mes; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void mes_v10_1_free_ucode_buffers(struct amdgpu_device *adev)
{
	amdgpu_bo_free_kernel(&adev->mes.data_fw_obj,
			      &adev->mes.data_fw_gpu_addr,
			      (void **)&adev->mes.data_fw_ptr);

	amdgpu_bo_free_kernel(&adev->mes.ucode_fw_obj,
			      &adev->mes.ucode_fw_gpu_addr,
			      (void **)&adev->mes.ucode_fw_ptr);
}