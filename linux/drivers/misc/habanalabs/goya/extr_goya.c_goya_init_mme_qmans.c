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
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 scalar_t__ CFG_BASE ; 
 int HW_CAP_MME ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goya_init_mme_cmdq (struct hl_device*) ; 
 int /*<<< orphan*/  goya_init_mme_qman (struct hl_device*) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mmMME_SM_BASE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  mmMME_SM_BASE_ADDRESS_LOW ; 
 scalar_t__ mmSYNC_MNGR_SOB_OBJ_0 ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

void goya_init_mme_qmans(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;
	u32 so_base_lo, so_base_hi;

	if (goya->hw_cap_initialized & HW_CAP_MME)
		return;

	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	WREG32(mmMME_SM_BASE_ADDRESS_LOW, so_base_lo);
	WREG32(mmMME_SM_BASE_ADDRESS_HIGH, so_base_hi);

	goya_init_mme_qman(hdev);
	goya_init_mme_cmdq(hdev);

	goya->hw_cap_initialized |= HW_CAP_MME;
}