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
struct TYPE_5__ {int /*<<< orphan*/  valid; } ;
struct TYPE_8__ {TYPE_3__* version; TYPE_1__ status; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__* funcs; } ;
struct TYPE_6__ {int (* set_clockgating_state ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_STATE_GATE ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_UVD ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_VCE ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_VCN ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int amdgpu_emu_mode ; 
 int stub1 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_device_ip_late_set_cg_state(struct amdgpu_device *adev)
{
	int i = 0, r;

	if (amdgpu_emu_mode == 1)
		return 0;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		/* skip CG for VCE/UVD, it's handled specially */
		if (adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_UVD &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCE &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCN &&
		    adev->ip_blocks[i].version->funcs->set_clockgating_state) {
			/* enable clockgating to save power */
			r = adev->ip_blocks[i].version->funcs->set_clockgating_state((void *)adev,
										     AMD_CG_STATE_GATE);
			if (r) {
				DRM_ERROR("set_clockgating_state(gate) of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				return r;
			}
		}
	}

	return 0;
}