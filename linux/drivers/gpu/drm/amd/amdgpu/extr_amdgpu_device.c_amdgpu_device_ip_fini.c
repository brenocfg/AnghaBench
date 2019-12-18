#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  csa_obj; } ;
struct TYPE_8__ {int num_physical_nodes; } ;
struct TYPE_9__ {TYPE_1__ xgmi; } ;
struct amdgpu_device {int num_ip_blocks; TYPE_7__* ip_blocks; TYPE_3__ virt; TYPE_2__ gmc; } ;
struct TYPE_13__ {int hw; int sw; int valid; int late_initialized; } ;
struct TYPE_14__ {TYPE_6__ status; TYPE_5__* version; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_4__* funcs; } ;
struct TYPE_11__ {int (* hw_fini ) (void*) ;int (* sw_fini ) (void*) ;int /*<<< orphan*/  (* late_fini ) (void*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_STATE_UNGATE ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_GMC ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_SMC ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_device_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_set_cg_state (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_set_pg_state (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_vram_scratch_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_wb_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_free_static_csa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_ib_pool_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_pre_fini (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ucode_free_bo (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_virt_release_full_gpu (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_xgmi_remove_device (struct amdgpu_device*) ; 
 int stub1 (void*) ; 
 int stub2 (void*) ; 
 int stub3 (void*) ; 
 int /*<<< orphan*/  stub4 (void*) ; 

__attribute__((used)) static int amdgpu_device_ip_fini(struct amdgpu_device *adev)
{
	int i, r;

	amdgpu_ras_pre_fini(adev);

	if (adev->gmc.xgmi.num_physical_nodes > 1)
		amdgpu_xgmi_remove_device(adev);

	amdgpu_amdkfd_device_fini(adev);

	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_UNGATE);
	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_UNGATE);

	/* need to disable SMC first */
	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.hw)
			continue;
		if (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC) {
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
			amdgpu_ucode_free_bo(adev);
			amdgpu_free_static_csa(&adev->virt.csa_obj);
			amdgpu_device_wb_fini(adev);
			amdgpu_device_vram_scratch_fini(adev);
			amdgpu_ib_pool_fini(adev);
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

	amdgpu_ras_fini(adev);

	if (amdgpu_sriov_vf(adev))
		if (amdgpu_virt_release_full_gpu(adev, false))
			DRM_ERROR("failed to release exclusive mode on fini\n");

	return 0;
}