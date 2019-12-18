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
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMME_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmMME_QM_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC0_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC0_QM_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC1_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC1_QM_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC2_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC2_QM_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC3_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC3_QM_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC4_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC4_QM_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC5_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC5_QM_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC6_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC6_QM_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC7_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmTPC7_QM_GLBL_CFG0 ; 

__attribute__((used)) static void goya_disable_internal_queues(struct hl_device *hdev)
{
	WREG32(mmMME_QM_GLBL_CFG0, 0);
	WREG32(mmMME_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC0_QM_GLBL_CFG0, 0);
	WREG32(mmTPC0_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC1_QM_GLBL_CFG0, 0);
	WREG32(mmTPC1_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC2_QM_GLBL_CFG0, 0);
	WREG32(mmTPC2_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC3_QM_GLBL_CFG0, 0);
	WREG32(mmTPC3_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC4_QM_GLBL_CFG0, 0);
	WREG32(mmTPC4_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC5_QM_GLBL_CFG0, 0);
	WREG32(mmTPC5_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC6_QM_GLBL_CFG0, 0);
	WREG32(mmTPC6_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC7_QM_GLBL_CFG0, 0);
	WREG32(mmTPC7_CMDQ_GLBL_CFG0, 0);
}