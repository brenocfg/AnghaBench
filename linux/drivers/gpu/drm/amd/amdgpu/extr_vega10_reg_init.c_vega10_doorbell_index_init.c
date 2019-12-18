#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vcn_ring6_7; int /*<<< orphan*/  vcn_ring4_5; int /*<<< orphan*/  vcn_ring2_3; int /*<<< orphan*/  vcn_ring0_1; } ;
struct TYPE_4__ {int /*<<< orphan*/  vce_ring6_7; int /*<<< orphan*/  vce_ring4_5; int /*<<< orphan*/  vce_ring2_3; int /*<<< orphan*/  vce_ring0_1; int /*<<< orphan*/  uvd_ring6_7; int /*<<< orphan*/  uvd_ring4_5; int /*<<< orphan*/  uvd_ring2_3; int /*<<< orphan*/  uvd_ring0_1; } ;
struct TYPE_6__ {int max_assignment; int sdma_doorbell_range; int /*<<< orphan*/  last_non_cp; int /*<<< orphan*/  first_non_cp; TYPE_2__ vcn; TYPE_1__ uvd_vce; int /*<<< orphan*/  ih; int /*<<< orphan*/ * sdma_engine; int /*<<< orphan*/  gfx_ring0; int /*<<< orphan*/  userqueue_end; int /*<<< orphan*/  userqueue_start; int /*<<< orphan*/  mec_ring7; int /*<<< orphan*/  mec_ring6; int /*<<< orphan*/  mec_ring5; int /*<<< orphan*/  mec_ring4; int /*<<< orphan*/  mec_ring3; int /*<<< orphan*/  mec_ring2; int /*<<< orphan*/  mec_ring1; int /*<<< orphan*/  mec_ring0; int /*<<< orphan*/  kiq; } ;
struct amdgpu_device {TYPE_3__ doorbell_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_DOORBELL64_FIRST_NON_CP ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_GFX_RING0 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_IH ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_KIQ ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_LAST_NON_CP ; 
 int AMDGPU_DOORBELL64_MAX_ASSIGNMENT ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_MEC_RING0 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_MEC_RING1 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_MEC_RING2 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_MEC_RING3 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_MEC_RING4 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_MEC_RING5 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_MEC_RING6 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_MEC_RING7 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_USERQUEUE_END ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_USERQUEUE_START ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_UVD_RING0_1 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_UVD_RING2_3 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_UVD_RING4_5 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_UVD_RING6_7 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_VCE_RING0_1 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_VCE_RING2_3 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_VCE_RING4_5 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_VCE_RING6_7 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_VCN0_1 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_VCN2_3 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_VCN4_5 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_VCN6_7 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_sDMA_ENGINE0 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL64_sDMA_ENGINE1 ; 

void vega10_doorbell_index_init(struct amdgpu_device *adev)
{
	adev->doorbell_index.kiq = AMDGPU_DOORBELL64_KIQ;
	adev->doorbell_index.mec_ring0 = AMDGPU_DOORBELL64_MEC_RING0;
	adev->doorbell_index.mec_ring1 = AMDGPU_DOORBELL64_MEC_RING1;
	adev->doorbell_index.mec_ring2 = AMDGPU_DOORBELL64_MEC_RING2;
	adev->doorbell_index.mec_ring3 = AMDGPU_DOORBELL64_MEC_RING3;
	adev->doorbell_index.mec_ring4 = AMDGPU_DOORBELL64_MEC_RING4;
	adev->doorbell_index.mec_ring5 = AMDGPU_DOORBELL64_MEC_RING5;
	adev->doorbell_index.mec_ring6 = AMDGPU_DOORBELL64_MEC_RING6;
	adev->doorbell_index.mec_ring7 = AMDGPU_DOORBELL64_MEC_RING7;
	adev->doorbell_index.userqueue_start = AMDGPU_DOORBELL64_USERQUEUE_START;
	adev->doorbell_index.userqueue_end = AMDGPU_DOORBELL64_USERQUEUE_END;
	adev->doorbell_index.gfx_ring0 = AMDGPU_DOORBELL64_GFX_RING0;
	adev->doorbell_index.sdma_engine[0] = AMDGPU_DOORBELL64_sDMA_ENGINE0;
	adev->doorbell_index.sdma_engine[1] = AMDGPU_DOORBELL64_sDMA_ENGINE1;
	adev->doorbell_index.ih = AMDGPU_DOORBELL64_IH;
	adev->doorbell_index.uvd_vce.uvd_ring0_1 = AMDGPU_DOORBELL64_UVD_RING0_1;
	adev->doorbell_index.uvd_vce.uvd_ring2_3 = AMDGPU_DOORBELL64_UVD_RING2_3;
	adev->doorbell_index.uvd_vce.uvd_ring4_5 = AMDGPU_DOORBELL64_UVD_RING4_5;
	adev->doorbell_index.uvd_vce.uvd_ring6_7 = AMDGPU_DOORBELL64_UVD_RING6_7;
	adev->doorbell_index.uvd_vce.vce_ring0_1 = AMDGPU_DOORBELL64_VCE_RING0_1;
	adev->doorbell_index.uvd_vce.vce_ring2_3 = AMDGPU_DOORBELL64_VCE_RING2_3;
	adev->doorbell_index.uvd_vce.vce_ring4_5 = AMDGPU_DOORBELL64_VCE_RING4_5;
	adev->doorbell_index.uvd_vce.vce_ring6_7 = AMDGPU_DOORBELL64_VCE_RING6_7;
	adev->doorbell_index.vcn.vcn_ring0_1 = AMDGPU_DOORBELL64_VCN0_1;
	adev->doorbell_index.vcn.vcn_ring2_3 = AMDGPU_DOORBELL64_VCN2_3;
	adev->doorbell_index.vcn.vcn_ring4_5 = AMDGPU_DOORBELL64_VCN4_5;
	adev->doorbell_index.vcn.vcn_ring6_7 = AMDGPU_DOORBELL64_VCN6_7;

	adev->doorbell_index.first_non_cp = AMDGPU_DOORBELL64_FIRST_NON_CP;
	adev->doorbell_index.last_non_cp = AMDGPU_DOORBELL64_LAST_NON_CP;

	/* In unit of dword doorbell */
	adev->doorbell_index.max_assignment = AMDGPU_DOORBELL64_MAX_ASSIGNMENT << 1;
	adev->doorbell_index.sdma_doorbell_range = 4;
}