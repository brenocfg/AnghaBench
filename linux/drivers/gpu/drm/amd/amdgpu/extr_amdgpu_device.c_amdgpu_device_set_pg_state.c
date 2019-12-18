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
typedef  enum amd_powergating_state { ____Placeholder_amd_powergating_state } amd_powergating_state ;
struct TYPE_5__ {int /*<<< orphan*/  late_initialized; } ;
struct TYPE_8__ {TYPE_3__* version; TYPE_1__ status; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__* funcs; } ;
struct TYPE_6__ {int (* set_powergating_state ) (void*,int) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AMD_IP_BLOCK_TYPE_UVD ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_VCE ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_VCN ; 
 int AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int amdgpu_emu_mode ; 
 int stub1 (void*,int) ; 

__attribute__((used)) static int amdgpu_device_set_pg_state(struct amdgpu_device *adev, enum amd_powergating_state state)
{
	int i, j, r;

	if (amdgpu_emu_mode == 1)
		return 0;

	for (j = 0; j < adev->num_ip_blocks; j++) {
		i = state == AMD_PG_STATE_GATE ? j : adev->num_ip_blocks - j - 1;
		if (!adev->ip_blocks[i].status.late_initialized)
			continue;
		/* skip CG for VCE/UVD, it's handled specially */
		if (adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_UVD &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCE &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCN &&
		    adev->ip_blocks[i].version->funcs->set_powergating_state) {
			/* enable powergating to save power */
			r = adev->ip_blocks[i].version->funcs->set_powergating_state((void *)adev,
											state);
			if (r) {
				DRM_ERROR("set_powergating_state(gate) of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				return r;
			}
		}
	}
	return 0;
}