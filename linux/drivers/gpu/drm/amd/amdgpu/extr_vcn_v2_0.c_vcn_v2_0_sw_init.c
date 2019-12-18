#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct common_firmware_header {int /*<<< orphan*/  ucode_size_bytes; } ;
struct amdgpu_ring {int use_doorbell; int doorbell_index; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int /*<<< orphan*/  jpeg_pitch; int /*<<< orphan*/  nop; int /*<<< orphan*/  cmd; int /*<<< orphan*/  data1; int /*<<< orphan*/  data0; int /*<<< orphan*/  scratch9; int /*<<< orphan*/  gp_scratch8; int /*<<< orphan*/  ib_size; int /*<<< orphan*/  ib_bar_high; int /*<<< orphan*/  ib_bar_low; int /*<<< orphan*/  ib_vmid; int /*<<< orphan*/  context_id; } ;
struct TYPE_16__ {int num_enc_rings; TYPE_9__* inst; TYPE_6__ internal; int /*<<< orphan*/  pause_dpg_mode; TYPE_2__* fw; } ;
struct TYPE_13__ {int vcn_ring0_1; } ;
struct TYPE_14__ {TYPE_4__ vcn; } ;
struct TYPE_12__ {scalar_t__ load_type; int /*<<< orphan*/  fw_size; TYPE_1__* ucode; } ;
struct amdgpu_device {TYPE_7__ vcn; TYPE_5__ doorbell_index; TYPE_3__ firmware; } ;
struct TYPE_17__ {void* jpeg_pitch; void* nop; void* cmd; void* data1; void* data0; void* scratch9; } ;
struct TYPE_18__ {TYPE_8__ external; int /*<<< orphan*/  irq; struct amdgpu_ring ring_jpeg; struct amdgpu_ring* ring_enc; struct amdgpu_ring ring_dec; } ;
struct TYPE_11__ {scalar_t__ data; } ;
struct TYPE_10__ {size_t ucode_id; TYPE_2__* fw; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 size_t AMDGPU_UCODE_ID_VCN ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_VCN ; 
 void* SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 scalar_t__ VCN_2_0__SRCID__JPEG_DECODE ; 
 scalar_t__ VCN_2_0__SRCID__UVD_ENC_GENERAL_PURPOSE ; 
 scalar_t__ VCN_2_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int amdgpu_vcn_resume (struct amdgpu_device*) ; 
 int amdgpu_vcn_sw_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_CONTEXT_ID_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_CMD ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_CMD_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA0 ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA0_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA1 ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA1_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_GP_SCRATCH8_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_JPEG_PITCH ; 
 int /*<<< orphan*/  mmUVD_JPEG_PITCH_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_IB_64BIT_BAR_LOW_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_IB_VMID_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_NO_OP ; 
 int /*<<< orphan*/  mmUVD_NO_OP_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_RBC_IB_SIZE_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_SCRATCH9 ; 
 int /*<<< orphan*/  mmUVD_SCRATCH9_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  vcn_v2_0_pause_dpg_mode ; 

__attribute__((used)) static int vcn_v2_0_sw_init(void *handle)
{
	struct amdgpu_ring *ring;
	int i, r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* VCN DEC TRAP */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN,
			      VCN_2_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT,
			      &adev->vcn.inst->irq);
	if (r)
		return r;

	/* VCN ENC TRAP */
	for (i = 0; i < adev->vcn.num_enc_rings; ++i) {
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN,
				      i + VCN_2_0__SRCID__UVD_ENC_GENERAL_PURPOSE,
				      &adev->vcn.inst->irq);
		if (r)
			return r;
	}

	/* VCN JPEG TRAP */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN,
			      VCN_2_0__SRCID__JPEG_DECODE, &adev->vcn.inst->irq);
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

	ring->use_doorbell = true;
	ring->doorbell_index = adev->doorbell_index.vcn.vcn_ring0_1 << 1;

	sprintf(ring->name, "vcn_dec");
	r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst->irq, 0);
	if (r)
		return r;

	adev->vcn.internal.context_id = mmUVD_CONTEXT_ID_INTERNAL_OFFSET;
	adev->vcn.internal.ib_vmid = mmUVD_LMI_RBC_IB_VMID_INTERNAL_OFFSET;
	adev->vcn.internal.ib_bar_low = mmUVD_LMI_RBC_IB_64BIT_BAR_LOW_INTERNAL_OFFSET;
	adev->vcn.internal.ib_bar_high = mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH_INTERNAL_OFFSET;
	adev->vcn.internal.ib_size = mmUVD_RBC_IB_SIZE_INTERNAL_OFFSET;
	adev->vcn.internal.gp_scratch8 = mmUVD_GP_SCRATCH8_INTERNAL_OFFSET;

	adev->vcn.internal.scratch9 = mmUVD_SCRATCH9_INTERNAL_OFFSET;
	adev->vcn.inst->external.scratch9 = SOC15_REG_OFFSET(UVD, 0, mmUVD_SCRATCH9);
	adev->vcn.internal.data0 = mmUVD_GPCOM_VCPU_DATA0_INTERNAL_OFFSET;
	adev->vcn.inst->external.data0 = SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0);
	adev->vcn.internal.data1 = mmUVD_GPCOM_VCPU_DATA1_INTERNAL_OFFSET;
	adev->vcn.inst->external.data1 = SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1);
	adev->vcn.internal.cmd = mmUVD_GPCOM_VCPU_CMD_INTERNAL_OFFSET;
	adev->vcn.inst->external.cmd = SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD);
	adev->vcn.internal.nop = mmUVD_NO_OP_INTERNAL_OFFSET;
	adev->vcn.inst->external.nop = SOC15_REG_OFFSET(UVD, 0, mmUVD_NO_OP);

	for (i = 0; i < adev->vcn.num_enc_rings; ++i) {
		ring = &adev->vcn.inst->ring_enc[i];
		ring->use_doorbell = true;
		ring->doorbell_index = (adev->doorbell_index.vcn.vcn_ring0_1 << 1) + 2 + i;
		sprintf(ring->name, "vcn_enc%d", i);
		r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst->irq, 0);
		if (r)
			return r;
	}

	ring = &adev->vcn.inst->ring_jpeg;
	ring->use_doorbell = true;
	ring->doorbell_index = (adev->doorbell_index.vcn.vcn_ring0_1 << 1) + 1;
	sprintf(ring->name, "vcn_jpeg");
	r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst->irq, 0);
	if (r)
		return r;

	adev->vcn.pause_dpg_mode = vcn_v2_0_pause_dpg_mode;

	adev->vcn.internal.jpeg_pitch = mmUVD_JPEG_PITCH_INTERNAL_OFFSET;
	adev->vcn.inst->external.jpeg_pitch = SOC15_REG_OFFSET(UVD, 0, mmUVD_JPEG_PITCH);

	return 0;
}