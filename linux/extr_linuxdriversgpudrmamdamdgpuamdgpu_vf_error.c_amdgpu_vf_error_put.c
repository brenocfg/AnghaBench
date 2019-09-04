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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint16_t ;
struct TYPE_3__ {int write_count; int /*<<< orphan*/  lock; int /*<<< orphan*/ * data; void** flags; void** code; } ;
struct TYPE_4__ {TYPE_1__ vf_errors; } ;
struct amdgpu_device {TYPE_2__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGIM_ERROR_CATEGORY_VF ; 
 void* AMDGIM_ERROR_CODE (int /*<<< orphan*/ ,void*) ; 
 int AMDGPU_VF_ERROR_ENTRY_SIZE ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void amdgpu_vf_error_put(struct amdgpu_device *adev,
			 uint16_t sub_error_code,
			 uint16_t error_flags,
			 uint64_t error_data)
{
	int index;
	uint16_t error_code;

	if (!amdgpu_sriov_vf(adev))
		return;

	error_code = AMDGIM_ERROR_CODE(AMDGIM_ERROR_CATEGORY_VF, sub_error_code);

	mutex_lock(&adev->virt.vf_errors.lock);
	index = adev->virt.vf_errors.write_count % AMDGPU_VF_ERROR_ENTRY_SIZE;
	adev->virt.vf_errors.code [index] = error_code;
	adev->virt.vf_errors.flags [index] = error_flags;
	adev->virt.vf_errors.data [index] = error_data;
	adev->virt.vf_errors.write_count ++;
	mutex_unlock(&adev->virt.vf_errors.lock);
}