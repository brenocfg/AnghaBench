#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int num_vcn_inst; int harvest_config; int num_enc_rings; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ vcn; } ;

/* Variables and functions */
 int AMDGPU_VCN_HARVEST_VCN0 ; 
 int AMDGPU_VCN_HARVEST_VCN1 ; 
 int CC_UVD_HARVESTING__UVD_DISABLE_MASK ; 
 scalar_t__ CHIP_ARCTURUS ; 
 int ENOENT ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int VCN25_MAX_HW_INSTANCES_ARCTURUS ; 
 int /*<<< orphan*/  mmCC_UVD_HARVESTING ; 
 int /*<<< orphan*/  vcn_v2_5_set_dec_ring_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v2_5_set_enc_ring_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v2_5_set_irq_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v2_5_set_jpeg_ring_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int vcn_v2_5_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	if (adev->asic_type == CHIP_ARCTURUS) {
		u32 harvest;
		int i;

		adev->vcn.num_vcn_inst = VCN25_MAX_HW_INSTANCES_ARCTURUS;
		for (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			harvest = RREG32_SOC15(UVD, i, mmCC_UVD_HARVESTING);
			if (harvest & CC_UVD_HARVESTING__UVD_DISABLE_MASK)
				adev->vcn.harvest_config |= 1 << i;
		}

		if (adev->vcn.harvest_config == (AMDGPU_VCN_HARVEST_VCN0 |
						 AMDGPU_VCN_HARVEST_VCN1))
			/* both instances are harvested, disable the block */
			return -ENOENT;
	} else
		adev->vcn.num_vcn_inst = 1;

	adev->vcn.num_enc_rings = 2;

	vcn_v2_5_set_dec_ring_funcs(adev);
	vcn_v2_5_set_enc_ring_funcs(adev);
	vcn_v2_5_set_jpeg_ring_funcs(adev);
	vcn_v2_5_set_irq_funcs(adev);

	return 0;
}