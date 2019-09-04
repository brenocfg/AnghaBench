#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int BANK_SELECT (int /*<<< orphan*/ ) ; 
 int CACHE_UPDATE_MODE (int) ; 
 int EFFECTIVE_L1_QUEUE_SIZE (int) ; 
 int EFFECTIVE_L1_TLB_SIZE (int) ; 
 int EFFECTIVE_L2_QUEUE_SIZE (int) ; 
 int ENABLE_L2_FRAGMENT_PROCESSING ; 
 scalar_t__ MC_VM_MB_L1_TLB0_CNTL ; 
 scalar_t__ MC_VM_MB_L1_TLB1_CNTL ; 
 scalar_t__ MC_VM_MB_L1_TLB2_CNTL ; 
 scalar_t__ MC_VM_MB_L1_TLB3_CNTL ; 
 scalar_t__ MC_VM_MD_L1_TLB0_CNTL ; 
 scalar_t__ MC_VM_MD_L1_TLB1_CNTL ; 
 scalar_t__ MC_VM_MD_L1_TLB2_CNTL ; 
 scalar_t__ VM_CONTEXT0_CNTL ; 
 scalar_t__ VM_L2_CNTL ; 
 scalar_t__ VM_L2_CNTL2 ; 
 scalar_t__ VM_L2_CNTL3 ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  radeon_gart_table_vram_unpin (struct radeon_device*) ; 

__attribute__((used)) static void rv770_pcie_gart_disable(struct radeon_device *rdev)
{
	u32 tmp;
	int i;

	/* Disable all tables */
	for (i = 0; i < 7; i++)
		WREG32(VM_CONTEXT0_CNTL + (i * 4), 0);

	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_FRAGMENT_PROCESSING |
				EFFECTIVE_L2_QUEUE_SIZE(7));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, BANK_SELECT(0) | CACHE_UPDATE_MODE(2));
	/* Setup TLB control */
	tmp = EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5);
	WREG32(MC_VM_MD_L1_TLB0_CNTL, tmp);
	WREG32(MC_VM_MD_L1_TLB1_CNTL, tmp);
	WREG32(MC_VM_MD_L1_TLB2_CNTL, tmp);
	WREG32(MC_VM_MB_L1_TLB0_CNTL, tmp);
	WREG32(MC_VM_MB_L1_TLB1_CNTL, tmp);
	WREG32(MC_VM_MB_L1_TLB2_CNTL, tmp);
	WREG32(MC_VM_MB_L1_TLB3_CNTL, tmp);
	radeon_gart_table_vram_unpin(rdev);
}