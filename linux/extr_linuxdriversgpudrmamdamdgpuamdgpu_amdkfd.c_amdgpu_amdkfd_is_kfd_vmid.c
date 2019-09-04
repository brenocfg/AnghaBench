#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct amdgpu_device {scalar_t__ kfd; } ;

/* Variables and functions */
 int compute_vmid_bitmap ; 

bool amdgpu_amdkfd_is_kfd_vmid(struct amdgpu_device *adev, u32 vmid)
{
	if (adev->kfd) {
		if ((1 << vmid) & compute_vmid_bitmap)
			return true;
	}

	return false;
}