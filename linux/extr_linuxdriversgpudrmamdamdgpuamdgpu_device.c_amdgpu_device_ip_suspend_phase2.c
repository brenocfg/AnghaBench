#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int num_ip_blocks; TYPE_6__* ip_blocks; TYPE_2__ powerplay; } ;
struct TYPE_9__ {int /*<<< orphan*/  valid; } ;
struct TYPE_12__ {TYPE_5__* version; TYPE_3__ status; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_4__* funcs; } ;
struct TYPE_10__ {int (* set_clockgating_state ) (void*,int /*<<< orphan*/ ) ;int (* suspend ) (struct amdgpu_device*) ;int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ set_powergating_by_smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_STATE_UNGATE ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_DCE ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_GFX ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_SMC ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int amdgpu_device_ip_set_clockgating_state (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dpm_set_powergating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_virt_release_full_gpu (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_virt_request_full_gpu (struct amdgpu_device*,int) ; 
 int stub1 (void*,int /*<<< orphan*/ ) ; 
 int stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static int amdgpu_device_ip_suspend_phase2(struct amdgpu_device *adev)
{
	int i, r;

	if (amdgpu_sriov_vf(adev))
		amdgpu_virt_request_full_gpu(adev, false);

	/* ungate SMC block first */
	r = amdgpu_device_ip_set_clockgating_state(adev, AMD_IP_BLOCK_TYPE_SMC,
						   AMD_CG_STATE_UNGATE);
	if (r) {
		DRM_ERROR("set_clockgating_state(ungate) SMC failed %d\n", r);
	}

	/* call smu to disable gfx off feature first when suspend */
	if (adev->powerplay.pp_funcs->set_powergating_by_smu)
		amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_GFX, false);

	for (i = adev->num_ip_blocks - 1; i >= 0; i--) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		/* displays are handled in phase1 */
		if (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_DCE)
			continue;
		/* ungate blocks so that suspend can properly shut them down */
		if (adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_SMC &&
			adev->ip_blocks[i].version->funcs->set_clockgating_state) {
			r = adev->ip_blocks[i].version->funcs->set_clockgating_state((void *)adev,
										     AMD_CG_STATE_UNGATE);
			if (r) {
				DRM_ERROR("set_clockgating_state(ungate) of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
			}
		}
		/* XXX handle errors */
		r = adev->ip_blocks[i].version->funcs->suspend(adev);
		/* XXX handle errors */
		if (r) {
			DRM_ERROR("suspend of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
		}
	}

	if (amdgpu_sriov_vf(adev))
		amdgpu_virt_release_full_gpu(adev, false);

	return 0;
}