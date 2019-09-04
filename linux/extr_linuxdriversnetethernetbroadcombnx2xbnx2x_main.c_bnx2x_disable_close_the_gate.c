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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int MISC_AEU_GENERAL_MASK_REG_AEU_NIG_CLOSE_MASK ; 
 int MISC_AEU_GENERAL_MASK_REG_AEU_PXP_CLOSE_MASK ; 
 int MISC_REG_AEU_GENERAL_MASK ; 
 int MISC_REG_AEU_MASK_ATTN_FUNC_0 ; 
 int MISC_REG_AEU_MASK_ATTN_FUNC_1 ; 
 int /*<<< orphan*/  NETIF_MSG_IFDOWN ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 

void bnx2x_disable_close_the_gate(struct bnx2x *bp)
{
	u32 val;

	DP(NETIF_MSG_IFDOWN, "Disabling \"close the gates\"\n");

	if (CHIP_IS_E1(bp)) {
		int port = BP_PORT(bp);
		u32 addr = port ? MISC_REG_AEU_MASK_ATTN_FUNC_1 :
			MISC_REG_AEU_MASK_ATTN_FUNC_0;

		val = REG_RD(bp, addr);
		val &= ~(0x300);
		REG_WR(bp, addr, val);
	} else {
		val = REG_RD(bp, MISC_REG_AEU_GENERAL_MASK);
		val &= ~(MISC_AEU_GENERAL_MASK_REG_AEU_PXP_CLOSE_MASK |
			 MISC_AEU_GENERAL_MASK_REG_AEU_NIG_CLOSE_MASK);
		REG_WR(bp, MISC_REG_AEU_GENERAL_MASK, val);
	}
}