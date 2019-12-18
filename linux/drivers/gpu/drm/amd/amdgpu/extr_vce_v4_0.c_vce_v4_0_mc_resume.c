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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int gpu_addr; } ;
struct TYPE_5__ {scalar_t__ load_type; TYPE_1__* ucode; } ;
struct amdgpu_device {TYPE_3__ vce; TYPE_2__ firmware; } ;
struct TYPE_4__ {int tmr_mc_addr_lo; scalar_t__ tmr_mc_addr_hi; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 size_t AMDGPU_UCODE_ID_VCE ; 
 int AMDGPU_VCE_FIRMWARE_OFFSET ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE ; 
 int VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK ; 
 int VCE_V4_0_DATA_SIZE ; 
 int VCE_V4_0_FW_SIZE ; 
 int VCE_V4_0_STACK_SIZE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmVCE_CLOCK_GATING_A ; 
 int /*<<< orphan*/  mmVCE_CLOCK_GATING_B ; 
 int /*<<< orphan*/  mmVCE_LMI_CACHE_CTRL ; 
 int /*<<< orphan*/  mmVCE_LMI_CTRL ; 
 int /*<<< orphan*/  mmVCE_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmVCE_LMI_SWAP_CNTL ; 
 int /*<<< orphan*/  mmVCE_LMI_SWAP_CNTL1 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_40BIT_BAR0 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_40BIT_BAR1 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_40BIT_BAR2 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_64BIT_BAR0 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_64BIT_BAR1 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_64BIT_BAR2 ; 
 int /*<<< orphan*/  mmVCE_LMI_VM_CTRL ; 
 int /*<<< orphan*/  mmVCE_SYS_INT_EN ; 
 int /*<<< orphan*/  mmVCE_UENC_CLOCK_GATING ; 
 int /*<<< orphan*/  mmVCE_UENC_REG_CLOCK_GATING ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE2 ; 

__attribute__((used)) static void vce_v4_0_mc_resume(struct amdgpu_device *adev)
{
	uint32_t offset, size;
	uint64_t tmr_mc_addr;

	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_A), 0, ~(1 << 16));
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING), 0x1FF000, ~0xFF9FF000);
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_REG_CLOCK_GATING), 0x3F, ~0x3F);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_B), 0x1FF);

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CTRL), 0x00398000);
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CACHE_CTRL), 0x0, ~0x1);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_SWAP_CNTL), 0);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_SWAP_CNTL1), 0);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VM_CTRL), 0);

	offset = AMDGPU_VCE_FIRMWARE_OFFSET;

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
		tmr_mc_addr = (uint64_t)(adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].tmr_mc_addr_hi) << 32 |
										adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].tmr_mc_addr_lo;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_40BIT_BAR0),
			(tmr_mc_addr >> 8));
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_64BIT_BAR0),
			(tmr_mc_addr >> 40) & 0xff);
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), 0);
	} else {
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_40BIT_BAR0),
			(adev->vce.gpu_addr >> 8));
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_64BIT_BAR0),
			(adev->vce.gpu_addr >> 40) & 0xff);
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), offset & ~0x0f000000);
	}

	size = VCE_V4_0_FW_SIZE;
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE0), size);

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_40BIT_BAR1), (adev->vce.gpu_addr >> 8));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_64BIT_BAR1), (adev->vce.gpu_addr >> 40) & 0xff);
	offset = (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) ? offset + size : 0;
	size = VCE_V4_0_STACK_SIZE;
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET1), (offset & ~0x0f000000) | (1 << 24));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE1), size);

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_40BIT_BAR2), (adev->vce.gpu_addr >> 8));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_64BIT_BAR2), (adev->vce.gpu_addr >> 40) & 0xff);
	offset += size;
	size = VCE_V4_0_DATA_SIZE;
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET2), (offset & ~0x0f000000) | (2 << 24));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE2), size);

	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CTRL2), 0x0, ~0x100);
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SYS_INT_EN),
			VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK,
			~VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK);
}