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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ dev; } ;
struct amdgpu_device {TYPE_1__ kfd; } ;

/* Variables and functions */
 int compute_vmid_bitmap ; 

bool amdgpu_amdkfd_is_kfd_vmid(struct amdgpu_device *adev, u32 vmid)
{
	if (adev->kfd.dev) {
		if ((1 << vmid) & compute_vmid_bitmap)
			return true;
	}

	return false;
}