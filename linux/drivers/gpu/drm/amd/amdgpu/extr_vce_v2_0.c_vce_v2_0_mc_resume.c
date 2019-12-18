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
typedef  int uint32_t ;
struct TYPE_2__ {int gpu_addr; } ;
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int AMDGPU_VCE_FIRMWARE_OFFSET ; 
 int /*<<< orphan*/  VCE_SYS_INT_EN ; 
 int /*<<< orphan*/  VCE_SYS_INT_TRAP_INTERRUPT_EN ; 
 int VCE_V2_0_DATA_SIZE ; 
 int VCE_V2_0_FW_SIZE ; 
 int VCE_V2_0_STACK_SIZE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmVCE_CLOCK_GATING_A ; 
 int /*<<< orphan*/  mmVCE_CLOCK_GATING_B ; 
 int /*<<< orphan*/  mmVCE_LMI_CACHE_CTRL ; 
 int /*<<< orphan*/  mmVCE_LMI_CTRL ; 
 int /*<<< orphan*/  mmVCE_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmVCE_LMI_SWAP_CNTL ; 
 int /*<<< orphan*/  mmVCE_LMI_SWAP_CNTL1 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_40BIT_BAR ; 
 int /*<<< orphan*/  mmVCE_LMI_VM_CTRL ; 
 int /*<<< orphan*/  mmVCE_UENC_CLOCK_GATING ; 
 int /*<<< orphan*/  mmVCE_UENC_REG_CLOCK_GATING ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE2 ; 

__attribute__((used)) static void vce_v2_0_mc_resume(struct amdgpu_device *adev)
{
	uint32_t size, offset;

	WREG32_P(mmVCE_CLOCK_GATING_A, 0, ~(1 << 16));
	WREG32_P(mmVCE_UENC_CLOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WREG32_P(mmVCE_UENC_REG_CLOCK_GATING, 0x3F, ~0x3F);
	WREG32(mmVCE_CLOCK_GATING_B, 0xf7);

	WREG32(mmVCE_LMI_CTRL, 0x00398000);
	WREG32_P(mmVCE_LMI_CACHE_CTRL, 0x0, ~0x1);
	WREG32(mmVCE_LMI_SWAP_CNTL, 0);
	WREG32(mmVCE_LMI_SWAP_CNTL1, 0);
	WREG32(mmVCE_LMI_VM_CTRL, 0);

	WREG32(mmVCE_LMI_VCPU_CACHE_40BIT_BAR, (adev->vce.gpu_addr >> 8));

	offset = AMDGPU_VCE_FIRMWARE_OFFSET;
	size = VCE_V2_0_FW_SIZE;
	WREG32(mmVCE_VCPU_CACHE_OFFSET0, offset & 0x7fffffff);
	WREG32(mmVCE_VCPU_CACHE_SIZE0, size);

	offset += size;
	size = VCE_V2_0_STACK_SIZE;
	WREG32(mmVCE_VCPU_CACHE_OFFSET1, offset & 0x7fffffff);
	WREG32(mmVCE_VCPU_CACHE_SIZE1, size);

	offset += size;
	size = VCE_V2_0_DATA_SIZE;
	WREG32(mmVCE_VCPU_CACHE_OFFSET2, offset & 0x7fffffff);
	WREG32(mmVCE_VCPU_CACHE_SIZE2, size);

	WREG32_P(mmVCE_LMI_CTRL2, 0x0, ~0x100);
	WREG32_FIELD(VCE_SYS_INT_EN, VCE_SYS_INT_TRAP_INTERRUPT_EN, 1);
}