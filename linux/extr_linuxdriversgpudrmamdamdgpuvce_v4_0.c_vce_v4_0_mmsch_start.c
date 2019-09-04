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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct mmsch_v1_0_init_header {int header_size; int vce_table_size; int uvd_table_size; } ;
struct amdgpu_mm_table {scalar_t__ cpu_addr; int /*<<< orphan*/  gpu_addr; } ;
struct TYPE_6__ {TYPE_2__* ring; } ;
struct TYPE_4__ {scalar_t__* wb; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_3__ vce; TYPE_1__ wb; } ;
struct TYPE_5__ {size_t wptr_offs; scalar_t__ wptr_old; scalar_t__ wptr; int /*<<< orphan*/  doorbell_index; } ;

/* Variables and functions */
 int EBUSY ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE ; 
 int VCE_MMSCH_VF_VMID__VF_CTX_VMID_MASK ; 
 int VCE_MMSCH_VF_VMID__VF_CTX_VMID__SHIFT ; 
 int /*<<< orphan*/  WDOORBELL32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmVCE_MMSCH_VF_CTX_ADDR_HI ; 
 int /*<<< orphan*/  mmVCE_MMSCH_VF_CTX_ADDR_LO ; 
 int /*<<< orphan*/  mmVCE_MMSCH_VF_CTX_SIZE ; 
 int /*<<< orphan*/  mmVCE_MMSCH_VF_MAILBOX_HOST ; 
 int /*<<< orphan*/  mmVCE_MMSCH_VF_MAILBOX_RESP ; 
 int /*<<< orphan*/  mmVCE_MMSCH_VF_VMID ; 
 int /*<<< orphan*/  udelay (int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vce_v4_0_mmsch_start(struct amdgpu_device *adev,
				struct amdgpu_mm_table *table)
{
	uint32_t data = 0, loop;
	uint64_t addr = table->gpu_addr;
	struct mmsch_v1_0_init_header *header = (struct mmsch_v1_0_init_header *)table->cpu_addr;
	uint32_t size;

	size = header->header_size + header->vce_table_size + header->uvd_table_size;

	/* 1, write to vce_mmsch_vf_ctx_addr_lo/hi register with GPU mc addr of memory descriptor location */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDR_LO), lower_32_bits(addr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDR_HI), upper_32_bits(addr));

	/* 2, update vmid of descriptor */
	data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_VMID));
	data &= ~VCE_MMSCH_VF_VMID__VF_CTX_VMID_MASK;
	data |= (0 << VCE_MMSCH_VF_VMID__VF_CTX_VMID__SHIFT); /* use domain0 for MM scheduler */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_VMID), data);

	/* 3, notify mmsch about the size of this descriptor */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_SIZE), size);

	/* 4, set resp to zero */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP), 0);

	WDOORBELL32(adev->vce.ring[0].doorbell_index, 0);
	adev->wb.wb[adev->vce.ring[0].wptr_offs] = 0;
	adev->vce.ring[0].wptr = 0;
	adev->vce.ring[0].wptr_old = 0;

	/* 5, kick off the initialization and wait until VCE_MMSCH_VF_MAILBOX_RESP becomes non-zero */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_HOST), 0x10000001);

	data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP));
	loop = 1000;
	while ((data & 0x10000002) != 0x10000002) {
		udelay(10);
		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP));
		loop--;
		if (!loop)
			break;
	}

	if (!loop) {
		dev_err(adev->dev, "failed to init MMSCH, mmVCE_MMSCH_VF_MAILBOX_RESP = %x\n", data);
		return -EBUSY;
	}

	return 0;
}