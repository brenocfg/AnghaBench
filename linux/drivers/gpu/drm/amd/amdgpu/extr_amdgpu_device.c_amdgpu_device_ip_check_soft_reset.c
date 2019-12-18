#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_device {int num_ip_blocks; TYPE_4__* ip_blocks; } ;
struct TYPE_5__ {scalar_t__ hang; int /*<<< orphan*/  valid; } ;
struct TYPE_8__ {TYPE_3__* version; TYPE_1__ status; } ;
struct TYPE_7__ {TYPE_2__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; scalar_t__ (* check_soft_reset ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_asic_need_full_reset (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 scalar_t__ stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static bool amdgpu_device_ip_check_soft_reset(struct amdgpu_device *adev)
{
	int i;
	bool asic_hang = false;

	if (amdgpu_sriov_vf(adev))
		return true;

	if (amdgpu_asic_need_full_reset(adev))
		return true;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		if (adev->ip_blocks[i].version->funcs->check_soft_reset)
			adev->ip_blocks[i].status.hang =
				adev->ip_blocks[i].version->funcs->check_soft_reset(adev);
		if (adev->ip_blocks[i].status.hang) {
			DRM_INFO("IP block:%s is hung!\n", adev->ip_blocks[i].version->funcs->name);
			asic_hang = true;
		}
	}
	return asic_hang;
}