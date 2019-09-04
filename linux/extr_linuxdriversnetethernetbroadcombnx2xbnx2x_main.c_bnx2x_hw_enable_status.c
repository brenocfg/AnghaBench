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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  CFC_REG_WEAK_ENABLE_PF ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGU_REG_PCI_PF_MSIX_EN ; 
 int /*<<< orphan*/  IGU_REG_PCI_PF_MSIX_FUNC_MASK ; 
 int /*<<< orphan*/  IGU_REG_PCI_PF_MSI_EN ; 
 int /*<<< orphan*/  PBF_REG_DISABLE_PF ; 
 int /*<<< orphan*/  PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR ; 
 int /*<<< orphan*/  PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int /*<<< orphan*/  PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR ; 
 int /*<<< orphan*/  REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_hw_enable_status(struct bnx2x *bp)
{
	u32 val;

	val = REG_RD(bp, CFC_REG_WEAK_ENABLE_PF);
	DP(BNX2X_MSG_SP, "CFC_REG_WEAK_ENABLE_PF is 0x%x\n", val);

	val = REG_RD(bp, PBF_REG_DISABLE_PF);
	DP(BNX2X_MSG_SP, "PBF_REG_DISABLE_PF is 0x%x\n", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSI_EN);
	DP(BNX2X_MSG_SP, "IGU_REG_PCI_PF_MSI_EN is 0x%x\n", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSIX_EN);
	DP(BNX2X_MSG_SP, "IGU_REG_PCI_PF_MSIX_EN is 0x%x\n", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSIX_FUNC_MASK);
	DP(BNX2X_MSG_SP, "IGU_REG_PCI_PF_MSIX_FUNC_MASK is 0x%x\n", val);

	val = REG_RD(bp, PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR);
	DP(BNX2X_MSG_SP, "PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR is 0x%x\n", val);

	val = REG_RD(bp, PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR);
	DP(BNX2X_MSG_SP, "PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR is 0x%x\n", val);

	val = REG_RD(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER);
	DP(BNX2X_MSG_SP, "PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER is 0x%x\n",
	   val);
}