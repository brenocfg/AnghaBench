#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct kgd_dev {int dummy; } ;
struct TYPE_10__ {scalar_t__ ready; } ;
struct amdgpu_ring {TYPE_5__ sched; } ;
struct TYPE_8__ {scalar_t__ num_physical_nodes; } ;
struct TYPE_9__ {TYPE_3__ xgmi; } ;
struct TYPE_6__ {struct amdgpu_ring ring; } ;
struct TYPE_7__ {TYPE_1__ kiq; } ;
struct amdgpu_device {scalar_t__ asic_type; int num_vmhubs; TYPE_4__ gmc; scalar_t__ in_gpu_reset; TYPE_2__ gfx; } ;

/* Variables and functions */
 scalar_t__ CHIP_VEGA20 ; 
 int EIO ; 
 int /*<<< orphan*/  amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_gmc_flush_gpu_tlb (struct amdgpu_device*,int,int,int) ; 
 int invalidate_tlbs_with_kiq (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kgd_gfx_v9_get_atc_vmid_pasid_mapping_pasid (struct kgd_dev*,int) ; 
 scalar_t__ kgd_gfx_v9_get_atc_vmid_pasid_mapping_valid (struct kgd_dev*,int) ; 

int kgd_gfx_v9_invalidate_tlbs(struct kgd_dev *kgd, uint16_t pasid)
{
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;
	int vmid, i;
	struct amdgpu_ring *ring = &adev->gfx.kiq.ring;
	uint32_t flush_type = 0;

	if (adev->in_gpu_reset)
		return -EIO;
	if (adev->gmc.xgmi.num_physical_nodes &&
		adev->asic_type == CHIP_VEGA20)
		flush_type = 2;

	if (ring->sched.ready)
		return invalidate_tlbs_with_kiq(adev, pasid, flush_type);

	for (vmid = 0; vmid < 16; vmid++) {
		if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid))
			continue;
		if (kgd_gfx_v9_get_atc_vmid_pasid_mapping_valid(kgd, vmid)) {
			if (kgd_gfx_v9_get_atc_vmid_pasid_mapping_pasid(kgd, vmid)
				== pasid) {
				for (i = 0; i < adev->num_vmhubs; i++)
					amdgpu_gmc_flush_gpu_tlb(adev, vmid,
								i, flush_type);
				break;
			}
		}
	}

	return 0;
}