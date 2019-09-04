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
struct TYPE_11__ {int hw; int sw; int valid; int late_initialized; } ;
struct TYPE_12__ {TYPE_5__ status; TYPE_4__* version; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__* funcs; } ;
struct TYPE_9__ {int (* set_clockgating_state ) (void*,int /*<<< orphan*/ ) ;int (* hw_fini ) (void*) ;int (* sw_fini ) (void*) ;int /*<<< orphan*/  (* late_fini ) (void*) ;int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ set_powergating_by_smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_STATE_UNGATE ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_GFX ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_GMC ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_SMC ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_UVD ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_VCE ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_VCN ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_device_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_vram_scratch_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_wb_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_dpm_set_powergating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_free_static_csa (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_virt_release_full_gpu (struct amdgpu_device*,int) ; 
 int stub1 (void*,int /*<<< orphan*/ ) ; 
 int stub2 (void*) ; 
 int stub3 (void*,int /*<<< orphan*/ ) ; 
 int stub4 (void*) ; 
 int stub5 (void*) ; 
 int /*<<< orphan*/  stub6 (void*) ; 

__attribute__((used)) static int amdgpu_device_ip_fini(struct amdgpu_device *adev)
{
	int i, r;

	amdgpu_amdkfd_device_fini(adev);
	/* need to disable SMC first */
	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.hw)
			continue;
		if (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC &&
			adev->ip_blocks[i].version->funcs->set_clockgating_state) {
			/* ungate blocks before hw fini so that we can shutdown the blocks safely */
			r = adev->ip_blocks[i].version->funcs->set_clockgating_state((void *)adev,
										     AMD_CG_STATE_UNGATE);
			if (r) {
				DRM_ERROR("set_clockgating_state(ungate) of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				return r;
			}
			if (adev->powerplay.pp_funcs->set_powergating_by_smu)
				amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_GFX, false);
			r = adev->ip_blocks[i].version->funcs->hw_fini((void *)adev);
			/* XXX handle errors */
			if (r) {
				DRM_DEBUG("hw_fini of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
			}
			adev->ip_blocks[i].status.hw = false;
			break;
		}
	}

	for (i = adev->num_ip_blocks - 1; i >= 0; i--) {
		if (!adev->ip_blocks[i].status.hw)
			continue;

		if (adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_UVD &&
			adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCE &&
			adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCN &&
			adev->ip_blocks[i].version->funcs->set_clockgating_state) {
			/* ungate blocks before hw fini so that we can shutdown the blocks safely */
			r = adev->ip_blocks[i].version->funcs->set_clockgating_state((void *)adev,
										     AMD_CG_STATE_UNGATE);
			if (r) {
				DRM_ERROR("set_clockgating_state(ungate) of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				return r;
			}
		}

		r = adev->ip_blocks[i].version->funcs->hw_fini((void *)adev);
		/* XXX handle errors */
		if (r) {
			DRM_DEBUG("hw_fini of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
		}

		adev->ip_blocks[i].status.hw = false;
	}


	for (i = adev->num_ip_blocks - 1; i >= 0; i--) {
		if (!adev->ip_blocks[i].status.sw)
			continue;

		if (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC) {
			amdgpu_free_static_csa(adev);
			amdgpu_device_wb_fini(adev);
			amdgpu_device_vram_scratch_fini(adev);
		}

		r = adev->ip_blocks[i].version->funcs->sw_fini((void *)adev);
		/* XXX handle errors */
		if (r) {
			DRM_DEBUG("sw_fini of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
		}
		adev->ip_blocks[i].status.sw = false;
		adev->ip_blocks[i].status.valid = false;
	}

	for (i = adev->num_ip_blocks - 1; i >= 0; i--) {
		if (!adev->ip_blocks[i].status.late_initialized)
			continue;
		if (adev->ip_blocks[i].version->funcs->late_fini)
			adev->ip_blocks[i].version->funcs->late_fini((void *)adev);
		adev->ip_blocks[i].status.late_initialized = false;
	}

	if (amdgpu_sriov_vf(adev))
		if (amdgpu_virt_release_full_gpu(adev, false))
			DRM_ERROR("failed to release exclusive mode on fini\n");

	return 0;
}