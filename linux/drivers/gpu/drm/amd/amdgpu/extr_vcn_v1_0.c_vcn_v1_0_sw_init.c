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
struct common_firmware_header {int /*<<< orphan*/  ucode_size_bytes; } ;
struct amdgpu_ring {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {void* jpeg_pitch; void* nop; void* cmd; void* data1; void* data0; void* scratch9; } ;
struct TYPE_14__ {int num_enc_rings; TYPE_6__* inst; TYPE_4__ internal; int /*<<< orphan*/  pause_dpg_mode; TYPE_2__* fw; } ;
struct TYPE_10__ {scalar_t__ load_type; int /*<<< orphan*/  fw_size; TYPE_1__* ucode; } ;
struct amdgpu_device {TYPE_7__ vcn; TYPE_3__ firmware; } ;
struct TYPE_12__ {void* jpeg_pitch; void* nop; void* cmd; void* data1; void* data0; void* scratch9; } ;
struct TYPE_13__ {TYPE_5__ external; int /*<<< orphan*/  irq; struct amdgpu_ring ring_jpeg; struct amdgpu_ring* ring_enc; struct amdgpu_ring ring_dec; } ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {size_t ucode_id; TYPE_2__* fw; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 size_t AMDGPU_UCODE_ID_VCN ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_VCN ; 
 void* SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int VCN_1_0__SRCID__UVD_ENC_GENERAL_PURPOSE ; 
 int VCN_1_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int amdgpu_vcn_resume (struct amdgpu_device*) ; 
 int amdgpu_vcn_sw_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_CMD ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA0 ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA1 ; 
 int /*<<< orphan*/  mmUVD_JPEG_PITCH ; 
 int /*<<< orphan*/  mmUVD_NO_OP ; 
 int /*<<< orphan*/  mmUVD_SCRATCH9 ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  vcn_v1_0_pause_dpg_mode ; 

__attribute__((used)) static int vcn_v1_0_sw_init(void *handle)
{
	struct amdgpu_ring *ring;
	int i, r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* VCN DEC TRAP */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN,
			VCN_1_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT, &adev->vcn.inst->irq);
	if (r)
		return r;

	/* VCN ENC TRAP */
	for (i = 0; i < adev->vcn.num_enc_rings; ++i) {
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN, i + VCN_1_0__SRCID__UVD_ENC_GENERAL_PURPOSE,
					&adev->vcn.inst->irq);
		if (r)
			return r;
	}

	/* VCN JPEG TRAP */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN, 126, &adev->vcn.inst->irq);
	if (r)
		return r;

	r = amdgpu_vcn_sw_init(adev);
	if (r)
		return r;

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
		const struct common_firmware_header *hdr;
		hdr = (const struct common_firmware_header *)adev->vcn.fw->data;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].ucode_id = AMDGPU_UCODE_ID_VCN;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].fw = adev->vcn.fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(hdr->ucode_size_bytes), PAGE_SIZE);
		DRM_INFO("PSP loading VCN firmware\n");
	}

	r = amdgpu_vcn_resume(adev);
	if (r)
		return r;

	ring = &adev->vcn.inst->ring_dec;
	sprintf(ring->name, "vcn_dec");
	r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst->irq, 0);
	if (r)
		return r;

	adev->vcn.internal.scratch9 = adev->vcn.inst->external.scratch9 =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_SCRATCH9);
	adev->vcn.internal.data0 = adev->vcn.inst->external.data0 =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0);
	adev->vcn.internal.data1 = adev->vcn.inst->external.data1 =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1);
	adev->vcn.internal.cmd = adev->vcn.inst->external.cmd =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD);
	adev->vcn.internal.nop = adev->vcn.inst->external.nop =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_NO_OP);

	for (i = 0; i < adev->vcn.num_enc_rings; ++i) {
		ring = &adev->vcn.inst->ring_enc[i];
		sprintf(ring->name, "vcn_enc%d", i);
		r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst->irq, 0);
		if (r)
			return r;
	}

	ring = &adev->vcn.inst->ring_jpeg;
	sprintf(ring->name, "vcn_jpeg");
	r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst->irq, 0);
	if (r)
		return r;

	adev->vcn.pause_dpg_mode = vcn_v1_0_pause_dpg_mode;
	adev->vcn.internal.jpeg_pitch = adev->vcn.inst->external.jpeg_pitch =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_JPEG_PITCH);

	return 0;
}