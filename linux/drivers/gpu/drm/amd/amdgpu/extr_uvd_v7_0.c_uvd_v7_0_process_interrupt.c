#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct amdgpu_iv_entry {int client_id; int src_id; int /*<<< orphan*/ * src_data; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ring_enc; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
#define  SOC15_IH_CLIENTID_UVD 129 
#define  SOC15_IH_CLIENTID_UVD1 128 
 int /*<<< orphan*/  amdgpu_fence_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v7_0_process_interrupt(struct amdgpu_device *adev,
				      struct amdgpu_irq_src *source,
				      struct amdgpu_iv_entry *entry)
{
	uint32_t ip_instance;

	switch (entry->client_id) {
	case SOC15_IH_CLIENTID_UVD:
		ip_instance = 0;
		break;
	case SOC15_IH_CLIENTID_UVD1:
		ip_instance = 1;
		break;
	default:
		DRM_ERROR("Unhandled client id: %d\n", entry->client_id);
		return 0;
	}

	DRM_DEBUG("IH: UVD TRAP\n");

	switch (entry->src_id) {
	case 124:
		amdgpu_fence_process(&adev->uvd.inst[ip_instance].ring);
		break;
	case 119:
		amdgpu_fence_process(&adev->uvd.inst[ip_instance].ring_enc[0]);
		break;
	case 120:
		if (!amdgpu_sriov_vf(adev))
			amdgpu_fence_process(&adev->uvd.inst[ip_instance].ring_enc[1]);
		break;
	default:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		break;
	}

	return 0;
}