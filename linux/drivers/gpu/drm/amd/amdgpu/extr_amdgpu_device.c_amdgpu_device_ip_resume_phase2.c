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
struct TYPE_7__ {int hw; int /*<<< orphan*/  valid; } ;
struct TYPE_8__ {TYPE_3__ status; TYPE_2__* version; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__* funcs; } ;
struct TYPE_5__ {int (* resume ) (struct amdgpu_device*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AMD_IP_BLOCK_TYPE_COMMON ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_GMC ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_IH ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_PSP ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int amdgpu_device_ip_resume_phase2(struct amdgpu_device *adev)
{
	int i, r;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid || adev->ip_blocks[i].status.hw)
			continue;
		if (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_COMMON ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_IH ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_PSP)
			continue;
		r = adev->ip_blocks[i].version->funcs->resume(adev);
		if (r) {
			DRM_ERROR("resume of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
			return r;
		}
		adev->ip_blocks[i].status.hw = true;
	}

	return 0;
}