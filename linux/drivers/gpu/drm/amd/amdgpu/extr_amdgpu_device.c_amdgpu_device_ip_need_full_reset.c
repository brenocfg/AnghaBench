#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_device {int num_ip_blocks; TYPE_3__* ip_blocks; } ;
struct TYPE_5__ {scalar_t__ hang; int /*<<< orphan*/  valid; } ;
struct TYPE_6__ {TYPE_2__ status; TYPE_1__* version; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMD_IP_BLOCK_TYPE_ACP ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_DCE ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_GMC ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_PSP ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_SMC ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 scalar_t__ amdgpu_asic_need_full_reset (struct amdgpu_device*) ; 

__attribute__((used)) static bool amdgpu_device_ip_need_full_reset(struct amdgpu_device *adev)
{
	int i;

	if (amdgpu_asic_need_full_reset(adev))
		return true;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		if ((adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC) ||
		    (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC) ||
		    (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_ACP) ||
		    (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_DCE) ||
		     adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_PSP) {
			if (adev->ip_blocks[i].status.hang) {
				DRM_INFO("Some block need full reset!\n");
				return true;
			}
		}
	}
	return false;
}