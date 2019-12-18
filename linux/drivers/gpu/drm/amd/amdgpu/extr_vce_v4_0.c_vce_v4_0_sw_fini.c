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
struct TYPE_4__ {int /*<<< orphan*/ * saved_bo; } ;
struct TYPE_3__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_2__ vce; TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int amdgpu_vce_suspend (struct amdgpu_device*) ; 
 int amdgpu_vce_sw_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_virt_free_mm_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vce_v4_0_sw_fini(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* free MM table */
	amdgpu_virt_free_mm_table(adev);

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
		kvfree(adev->vce.saved_bo);
		adev->vce.saved_bo = NULL;
	}

	r = amdgpu_vce_suspend(adev);
	if (r)
		return r;

	return amdgpu_vce_sw_fini(adev);
}