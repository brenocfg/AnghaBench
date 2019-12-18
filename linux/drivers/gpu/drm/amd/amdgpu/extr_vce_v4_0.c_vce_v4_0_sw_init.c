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
struct common_firmware_header {int /*<<< orphan*/  ucode_size_bytes; } ;
struct amdgpu_ring {int use_doorbell; int doorbell_index; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int num_rings; int /*<<< orphan*/  irq; struct amdgpu_ring* ring; TYPE_2__* fw; int /*<<< orphan*/  saved_bo; int /*<<< orphan*/  vcpu_bo; } ;
struct TYPE_10__ {int vce_ring0_1; int vce_ring2_3; } ;
struct TYPE_11__ {TYPE_4__ uvd_vce; } ;
struct TYPE_9__ {scalar_t__ load_type; int /*<<< orphan*/  fw_size; TYPE_1__* ucode; } ;
struct amdgpu_device {TYPE_6__ vce; TYPE_5__ doorbell_index; TYPE_3__ firmware; } ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {size_t ucode_id; TYPE_2__* fw; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 size_t AMDGPU_UCODE_ID_VCE ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_VCE0 ; 
 unsigned int VCE_V4_0_DATA_SIZE ; 
 scalar_t__ VCE_V4_0_FW_SIZE ; 
 unsigned int VCE_V4_0_STACK_SIZE ; 
 unsigned int amdgpu_bo_size (int /*<<< orphan*/ ) ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int amdgpu_vce_entity_init (struct amdgpu_device*) ; 
 int amdgpu_vce_resume (struct amdgpu_device*) ; 
 int amdgpu_vce_sw_init (struct amdgpu_device*,unsigned int) ; 
 int amdgpu_virt_alloc_mm_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vce_v4_0_sw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ring *ring;

	unsigned size;
	int r, i;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCE0, 167, &adev->vce.irq);
	if (r)
		return r;

	size  = VCE_V4_0_STACK_SIZE + VCE_V4_0_DATA_SIZE;
	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		size += VCE_V4_0_FW_SIZE;

	r = amdgpu_vce_sw_init(adev, size);
	if (r)
		return r;

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
		const struct common_firmware_header *hdr;
		unsigned size = amdgpu_bo_size(adev->vce.vcpu_bo);

		adev->vce.saved_bo = kvmalloc(size, GFP_KERNEL);
		if (!adev->vce.saved_bo)
			return -ENOMEM;

		hdr = (const struct common_firmware_header *)adev->vce.fw->data;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].ucode_id = AMDGPU_UCODE_ID_VCE;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].fw = adev->vce.fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(hdr->ucode_size_bytes), PAGE_SIZE);
		DRM_INFO("PSP loading VCE firmware\n");
	} else {
		r = amdgpu_vce_resume(adev);
		if (r)
			return r;
	}

	for (i = 0; i < adev->vce.num_rings; i++) {
		ring = &adev->vce.ring[i];
		sprintf(ring->name, "vce%d", i);
		if (amdgpu_sriov_vf(adev)) {
			/* DOORBELL only works under SRIOV */
			ring->use_doorbell = true;

			/* currently only use the first encoding ring for sriov,
			 * so set unused location for other unused rings.
			 */
			if (i == 0)
				ring->doorbell_index = adev->doorbell_index.uvd_vce.vce_ring0_1 * 2;
			else
				ring->doorbell_index = adev->doorbell_index.uvd_vce.vce_ring2_3 * 2 + 1;
		}
		r = amdgpu_ring_init(adev, ring, 512, &adev->vce.irq, 0);
		if (r)
			return r;
	}


	r = amdgpu_vce_entity_init(adev);
	if (r)
		return r;

	r = amdgpu_virt_alloc_mm_table(adev);
	if (r)
		return r;

	return r;
}