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
struct hl_device {int dummy; } ;

/* Variables and functions */
 int DMA_QM_0_GLBL_CFG1_DMA_STOP_SHIFT ; 
 int DMA_QM_1_GLBL_CFG1_DMA_STOP_SHIFT ; 
 int DMA_QM_2_GLBL_CFG1_DMA_STOP_SHIFT ; 
 int DMA_QM_3_GLBL_CFG1_DMA_STOP_SHIFT ; 
 int DMA_QM_4_GLBL_CFG1_DMA_STOP_SHIFT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmDMA_QM_0_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_1_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_2_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_3_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_4_GLBL_CFG1 ; 

__attribute__((used)) static void goya_dma_stall(struct hl_device *hdev)
{
	WREG32(mmDMA_QM_0_GLBL_CFG1, 1 << DMA_QM_0_GLBL_CFG1_DMA_STOP_SHIFT);
	WREG32(mmDMA_QM_1_GLBL_CFG1, 1 << DMA_QM_1_GLBL_CFG1_DMA_STOP_SHIFT);
	WREG32(mmDMA_QM_2_GLBL_CFG1, 1 << DMA_QM_2_GLBL_CFG1_DMA_STOP_SHIFT);
	WREG32(mmDMA_QM_3_GLBL_CFG1, 1 << DMA_QM_3_GLBL_CFG1_DMA_STOP_SHIFT);
	WREG32(mmDMA_QM_4_GLBL_CFG1, 1 << DMA_QM_4_GLBL_CFG1_DMA_STOP_SHIFT);
}