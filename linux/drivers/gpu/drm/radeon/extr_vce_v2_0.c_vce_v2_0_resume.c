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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int gpu_addr; } ;
struct radeon_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCE_CLOCK_GATING_A ; 
 int /*<<< orphan*/  VCE_CLOCK_GATING_B ; 
 int /*<<< orphan*/  VCE_LMI_CACHE_CTRL ; 
 int /*<<< orphan*/  VCE_LMI_CTRL ; 
 int /*<<< orphan*/  VCE_LMI_CTRL2 ; 
 int /*<<< orphan*/  VCE_LMI_SWAP_CNTL ; 
 int /*<<< orphan*/  VCE_LMI_SWAP_CNTL1 ; 
 int /*<<< orphan*/  VCE_LMI_VCPU_CACHE_40BIT_BAR ; 
 int /*<<< orphan*/  VCE_LMI_VM_CTRL ; 
 int /*<<< orphan*/  VCE_SYS_INT_EN ; 
 int VCE_SYS_INT_TRAP_INTERRUPT_EN ; 
 int /*<<< orphan*/  VCE_UENC_CLOCK_GATING ; 
 int /*<<< orphan*/  VCE_UENC_REG_CLOCK_GATING ; 
 int VCE_V2_0_DATA_SIZE ; 
 int VCE_V2_0_FW_SIZE ; 
 int VCE_V2_0_STACK_SIZE ; 
 int /*<<< orphan*/  VCE_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  VCE_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  VCE_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  VCE_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  VCE_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  VCE_VCPU_CACHE_SIZE2 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vce_v2_0_init_cg (struct radeon_device*) ; 

int vce_v2_0_resume(struct radeon_device *rdev)
{
	uint64_t addr = rdev->vce.gpu_addr;
	uint32_t size;

	WREG32_P(VCE_CLOCK_GATING_A, 0, ~(1 << 16));
	WREG32_P(VCE_UENC_CLOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WREG32_P(VCE_UENC_REG_CLOCK_GATING, 0x3F, ~0x3F);
	WREG32(VCE_CLOCK_GATING_B, 0xf7);

	WREG32(VCE_LMI_CTRL, 0x00398000);
	WREG32_P(VCE_LMI_CACHE_CTRL, 0x0, ~0x1);
	WREG32(VCE_LMI_SWAP_CNTL, 0);
	WREG32(VCE_LMI_SWAP_CNTL1, 0);
	WREG32(VCE_LMI_VM_CTRL, 0);

	WREG32(VCE_LMI_VCPU_CACHE_40BIT_BAR, addr >> 8);

	addr &= 0xff;
	size = VCE_V2_0_FW_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET0, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE0, size);

	addr += size;
	size = VCE_V2_0_STACK_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET1, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE1, size);

	addr += size;
	size = VCE_V2_0_DATA_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET2, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE2, size);

	WREG32_P(VCE_LMI_CTRL2, 0x0, ~0x100);

	WREG32_P(VCE_SYS_INT_EN, VCE_SYS_INT_TRAP_INTERRUPT_EN,
		 ~VCE_SYS_INT_TRAP_INTERRUPT_EN);

	vce_v2_0_init_cg(rdev);

	return 0;
}