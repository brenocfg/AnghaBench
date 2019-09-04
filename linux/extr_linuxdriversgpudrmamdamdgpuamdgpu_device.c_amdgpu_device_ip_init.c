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
struct TYPE_7__ {int sw; int hw; int /*<<< orphan*/  valid; } ;
struct TYPE_8__ {TYPE_3__ status; TYPE_2__* version; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__* funcs; } ;
struct TYPE_5__ {int (* sw_init ) (void*) ;int name; int (* hw_init ) (void*) ;} ;

/* Variables and functions */
 scalar_t__ AMD_IP_BLOCK_TYPE_GMC ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int amdgpu_allocate_static_csa (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_device_init (struct amdgpu_device*) ; 
 int amdgpu_device_vram_scratch_init (struct amdgpu_device*) ; 
 int amdgpu_device_wb_init (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_virt_init_data_exchange (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_virt_release_full_gpu (struct amdgpu_device*,int) ; 
 int stub1 (void*) ; 
 int stub2 (void*) ; 
 int stub3 (void*) ; 

__attribute__((used)) static int amdgpu_device_ip_init(struct amdgpu_device *adev)
{
	int i, r;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		r = adev->ip_blocks[i].version->funcs->sw_init((void *)adev);
		if (r) {
			DRM_ERROR("sw_init of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
			return r;
		}
		adev->ip_blocks[i].status.sw = true;

		/* need to do gmc hw init early so we can allocate gpu mem */
		if (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC) {
			r = amdgpu_device_vram_scratch_init(adev);
			if (r) {
				DRM_ERROR("amdgpu_vram_scratch_init failed %d\n", r);
				return r;
			}
			r = adev->ip_blocks[i].version->funcs->hw_init((void *)adev);
			if (r) {
				DRM_ERROR("hw_init %d failed %d\n", i, r);
				return r;
			}
			r = amdgpu_device_wb_init(adev);
			if (r) {
				DRM_ERROR("amdgpu_device_wb_init failed %d\n", r);
				return r;
			}
			adev->ip_blocks[i].status.hw = true;

			/* right after GMC hw init, we create CSA */
			if (amdgpu_sriov_vf(adev)) {
				r = amdgpu_allocate_static_csa(adev);
				if (r) {
					DRM_ERROR("allocate CSA failed %d\n", r);
					return r;
				}
			}
		}
	}

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.sw)
			continue;
		if (adev->ip_blocks[i].status.hw)
			continue;
		r = adev->ip_blocks[i].version->funcs->hw_init((void *)adev);
		if (r) {
			DRM_ERROR("hw_init of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
			return r;
		}
		adev->ip_blocks[i].status.hw = true;
	}

	amdgpu_amdkfd_device_init(adev);

	if (amdgpu_sriov_vf(adev)) {
		amdgpu_virt_init_data_exchange(adev);
		amdgpu_virt_release_full_gpu(adev, true);
	}

	return 0;
}