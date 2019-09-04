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
struct vpe_dev {int /*<<< orphan*/  csc; int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPE_CLK_ENABLE ; 
 int /*<<< orphan*/  VPE_CLK_FORMAT_SELECT ; 
 int /*<<< orphan*/  VPE_CLK_RANGE_MAP ; 
 int /*<<< orphan*/  VPE_CLK_RESET ; 
 int /*<<< orphan*/  VPE_DEI_EDI_LUT_R0 ; 
 int /*<<< orphan*/  VPE_DEI_EDI_LUT_R1 ; 
 int /*<<< orphan*/  VPE_DEI_EDI_LUT_R2 ; 
 int /*<<< orphan*/  VPE_DEI_EDI_LUT_R3 ; 
 int /*<<< orphan*/  VPE_DEI_FMD_CONTROL_R0 ; 
 int /*<<< orphan*/  VPE_DEI_FMD_CONTROL_R1 ; 
 int /*<<< orphan*/  VPE_DEI_FMD_STATUS_R0 ; 
 int /*<<< orphan*/  VPE_DEI_FMD_STATUS_R1 ; 
 int /*<<< orphan*/  VPE_DEI_FMD_STATUS_R2 ; 
 int /*<<< orphan*/  VPE_DEI_FMD_WINDOW_R0 ; 
 int /*<<< orphan*/  VPE_DEI_FMD_WINDOW_R1 ; 
 int /*<<< orphan*/  VPE_DEI_FRAME_SIZE ; 
 int /*<<< orphan*/  VPE_EDI_CONFIG ; 
 int /*<<< orphan*/  VPE_INT0_ENABLE0 ; 
 int /*<<< orphan*/  VPE_INT0_ENABLE1 ; 
 int /*<<< orphan*/  VPE_INT0_STATUS0 ; 
 int /*<<< orphan*/  VPE_INT0_STATUS0_RAW ; 
 int /*<<< orphan*/  VPE_INT0_STATUS1 ; 
 int /*<<< orphan*/  VPE_INT0_STATUS1_RAW ; 
 int /*<<< orphan*/  VPE_MDT_BYPASS ; 
 int /*<<< orphan*/  VPE_MDT_SF_THRESHOLD ; 
 int /*<<< orphan*/  VPE_PID ; 
 int /*<<< orphan*/  VPE_SYSCONFIG ; 
 int /*<<< orphan*/  VPE_US1_R0 ; 
 int /*<<< orphan*/  VPE_US1_R1 ; 
 int /*<<< orphan*/  VPE_US1_R2 ; 
 int /*<<< orphan*/  VPE_US1_R3 ; 
 int /*<<< orphan*/  VPE_US1_R4 ; 
 int /*<<< orphan*/  VPE_US1_R5 ; 
 int /*<<< orphan*/  VPE_US1_R6 ; 
 int /*<<< orphan*/  VPE_US1_R7 ; 
 int /*<<< orphan*/  VPE_US2_R0 ; 
 int /*<<< orphan*/  VPE_US2_R1 ; 
 int /*<<< orphan*/  VPE_US2_R2 ; 
 int /*<<< orphan*/  VPE_US2_R3 ; 
 int /*<<< orphan*/  VPE_US2_R4 ; 
 int /*<<< orphan*/  VPE_US2_R5 ; 
 int /*<<< orphan*/  VPE_US2_R6 ; 
 int /*<<< orphan*/  VPE_US2_R7 ; 
 int /*<<< orphan*/  VPE_US3_R0 ; 
 int /*<<< orphan*/  VPE_US3_R1 ; 
 int /*<<< orphan*/  VPE_US3_R2 ; 
 int /*<<< orphan*/  VPE_US3_R3 ; 
 int /*<<< orphan*/  VPE_US3_R4 ; 
 int /*<<< orphan*/  VPE_US3_R5 ; 
 int /*<<< orphan*/  VPE_US3_R6 ; 
 int /*<<< orphan*/  VPE_US3_R7 ; 
 int /*<<< orphan*/  csc_dump_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_reg (struct vpe_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_dump_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpe_dbg (struct vpe_dev*,char*,...) ; 

__attribute__((used)) static void vpe_dump_regs(struct vpe_dev *dev)
{
#define DUMPREG(r) vpe_dbg(dev, "%-35s %08x\n", #r, read_reg(dev, VPE_##r))

	vpe_dbg(dev, "VPE Registers:\n");

	DUMPREG(PID);
	DUMPREG(SYSCONFIG);
	DUMPREG(INT0_STATUS0_RAW);
	DUMPREG(INT0_STATUS0);
	DUMPREG(INT0_ENABLE0);
	DUMPREG(INT0_STATUS1_RAW);
	DUMPREG(INT0_STATUS1);
	DUMPREG(INT0_ENABLE1);
	DUMPREG(CLK_ENABLE);
	DUMPREG(CLK_RESET);
	DUMPREG(CLK_FORMAT_SELECT);
	DUMPREG(CLK_RANGE_MAP);
	DUMPREG(US1_R0);
	DUMPREG(US1_R1);
	DUMPREG(US1_R2);
	DUMPREG(US1_R3);
	DUMPREG(US1_R4);
	DUMPREG(US1_R5);
	DUMPREG(US1_R6);
	DUMPREG(US1_R7);
	DUMPREG(US2_R0);
	DUMPREG(US2_R1);
	DUMPREG(US2_R2);
	DUMPREG(US2_R3);
	DUMPREG(US2_R4);
	DUMPREG(US2_R5);
	DUMPREG(US2_R6);
	DUMPREG(US2_R7);
	DUMPREG(US3_R0);
	DUMPREG(US3_R1);
	DUMPREG(US3_R2);
	DUMPREG(US3_R3);
	DUMPREG(US3_R4);
	DUMPREG(US3_R5);
	DUMPREG(US3_R6);
	DUMPREG(US3_R7);
	DUMPREG(DEI_FRAME_SIZE);
	DUMPREG(MDT_BYPASS);
	DUMPREG(MDT_SF_THRESHOLD);
	DUMPREG(EDI_CONFIG);
	DUMPREG(DEI_EDI_LUT_R0);
	DUMPREG(DEI_EDI_LUT_R1);
	DUMPREG(DEI_EDI_LUT_R2);
	DUMPREG(DEI_EDI_LUT_R3);
	DUMPREG(DEI_FMD_WINDOW_R0);
	DUMPREG(DEI_FMD_WINDOW_R1);
	DUMPREG(DEI_FMD_CONTROL_R0);
	DUMPREG(DEI_FMD_CONTROL_R1);
	DUMPREG(DEI_FMD_STATUS_R0);
	DUMPREG(DEI_FMD_STATUS_R1);
	DUMPREG(DEI_FMD_STATUS_R2);
#undef DUMPREG

	sc_dump_regs(dev->sc);
	csc_dump_regs(dev->csc);
}