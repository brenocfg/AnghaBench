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
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmDMA_MACRO_RAZWI_HBW_RD_VLD ; 
 int /*<<< orphan*/  mmDMA_MACRO_RAZWI_HBW_WT_VLD ; 
 int /*<<< orphan*/  mmDMA_MACRO_RAZWI_LBW_RD_VLD ; 
 int /*<<< orphan*/  mmDMA_MACRO_RAZWI_LBW_WT_VLD ; 

__attribute__((used)) static void goya_print_razwi_info(struct hl_device *hdev)
{
	if (RREG32(mmDMA_MACRO_RAZWI_LBW_WT_VLD)) {
		dev_err(hdev->dev, "Illegal write to LBW\n");
		WREG32(mmDMA_MACRO_RAZWI_LBW_WT_VLD, 0);
	}

	if (RREG32(mmDMA_MACRO_RAZWI_LBW_RD_VLD)) {
		dev_err(hdev->dev, "Illegal read from LBW\n");
		WREG32(mmDMA_MACRO_RAZWI_LBW_RD_VLD, 0);
	}

	if (RREG32(mmDMA_MACRO_RAZWI_HBW_WT_VLD)) {
		dev_err(hdev->dev, "Illegal write to HBW\n");
		WREG32(mmDMA_MACRO_RAZWI_HBW_WT_VLD, 0);
	}

	if (RREG32(mmDMA_MACRO_RAZWI_HBW_RD_VLD)) {
		dev_err(hdev->dev, "Illegal read from HBW\n");
		WREG32(mmDMA_MACRO_RAZWI_HBW_RD_VLD, 0);
	}
}