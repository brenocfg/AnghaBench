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
struct TYPE_2__ {int /*<<< orphan*/  max_assignment; int /*<<< orphan*/  ih; int /*<<< orphan*/ * sdma_engine; int /*<<< orphan*/  gfx_ring0; int /*<<< orphan*/  mec_ring7; int /*<<< orphan*/  mec_ring6; int /*<<< orphan*/  mec_ring5; int /*<<< orphan*/  mec_ring4; int /*<<< orphan*/  mec_ring3; int /*<<< orphan*/  mec_ring2; int /*<<< orphan*/  mec_ring1; int /*<<< orphan*/  mec_ring0; int /*<<< orphan*/  kiq; } ;
struct amdgpu_device {TYPE_1__ doorbell_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_DOORBELL_GFX_RING0 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_IH ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_KIQ ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MAX_ASSIGNMENT ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MEC_RING0 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MEC_RING1 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MEC_RING2 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MEC_RING3 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MEC_RING4 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MEC_RING5 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MEC_RING6 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_MEC_RING7 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_sDMA_ENGINE0 ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_sDMA_ENGINE1 ; 

void legacy_doorbell_index_init(struct amdgpu_device *adev)
{
	adev->doorbell_index.kiq = AMDGPU_DOORBELL_KIQ;
	adev->doorbell_index.mec_ring0 = AMDGPU_DOORBELL_MEC_RING0;
	adev->doorbell_index.mec_ring1 = AMDGPU_DOORBELL_MEC_RING1;
	adev->doorbell_index.mec_ring2 = AMDGPU_DOORBELL_MEC_RING2;
	adev->doorbell_index.mec_ring3 = AMDGPU_DOORBELL_MEC_RING3;
	adev->doorbell_index.mec_ring4 = AMDGPU_DOORBELL_MEC_RING4;
	adev->doorbell_index.mec_ring5 = AMDGPU_DOORBELL_MEC_RING5;
	adev->doorbell_index.mec_ring6 = AMDGPU_DOORBELL_MEC_RING6;
	adev->doorbell_index.mec_ring7 = AMDGPU_DOORBELL_MEC_RING7;
	adev->doorbell_index.gfx_ring0 = AMDGPU_DOORBELL_GFX_RING0;
	adev->doorbell_index.sdma_engine[0] = AMDGPU_DOORBELL_sDMA_ENGINE0;
	adev->doorbell_index.sdma_engine[1] = AMDGPU_DOORBELL_sDMA_ENGINE1;
	adev->doorbell_index.ih = AMDGPU_DOORBELL_IH;
	adev->doorbell_index.max_assignment = AMDGPU_DOORBELL_MAX_ASSIGNMENT;
}