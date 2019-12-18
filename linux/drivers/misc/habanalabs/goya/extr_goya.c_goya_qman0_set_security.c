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
struct hl_device {struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int HW_CAP_MMU ; 
 int /*<<< orphan*/  QMAN_DMA_FULLY_TRUSTED ; 
 int /*<<< orphan*/  QMAN_DMA_PARTLY_TRUSTED ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDMA_QM_0_GLBL_PROT ; 

__attribute__((used)) static void goya_qman0_set_security(struct hl_device *hdev, bool secure)
{
	struct goya_device *goya = hdev->asic_specific;

	if (!(goya->hw_cap_initialized & HW_CAP_MMU))
		return;

	if (secure)
		WREG32(mmDMA_QM_0_GLBL_PROT, QMAN_DMA_FULLY_TRUSTED);
	else
		WREG32(mmDMA_QM_0_GLBL_PROT, QMAN_DMA_PARTLY_TRUSTED);

	RREG32(mmDMA_QM_0_GLBL_PROT);
}