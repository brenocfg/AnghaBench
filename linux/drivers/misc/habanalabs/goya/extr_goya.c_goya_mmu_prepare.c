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
struct hl_device {struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int GOYA_MMU_REGS_NUM ; 
 int HW_CAP_MMU ; 
 int MME_QM_GLBL_SECURE_PROPS_ASID_MASK ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  goya_mmu_prepare_reg (struct hl_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * goya_mmu_regs ; 

__attribute__((used)) static void goya_mmu_prepare(struct hl_device *hdev, u32 asid)
{
	struct goya_device *goya = hdev->asic_specific;
	int i;

	if (!(goya->hw_cap_initialized & HW_CAP_MMU))
		return;

	if (asid & ~MME_QM_GLBL_SECURE_PROPS_ASID_MASK) {
		WARN(1, "asid %u is too big\n", asid);
		return;
	}

	/* zero the MMBP and ASID bits and then set the ASID */
	for (i = 0 ; i < GOYA_MMU_REGS_NUM ; i++)
		goya_mmu_prepare_reg(hdev, goya_mmu_regs[i], asid);
}