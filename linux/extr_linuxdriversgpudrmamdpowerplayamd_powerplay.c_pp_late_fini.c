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
struct TYPE_2__ {scalar_t__ smu_prv_buffer; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_powerplay_destroy (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pp_late_fini(void *handle)
{
	struct amdgpu_device *adev = handle;

	if (adev->pm.smu_prv_buffer)
		amdgpu_bo_free_kernel(&adev->pm.smu_prv_buffer, NULL, NULL);
	amd_powerplay_destroy(adev);
}