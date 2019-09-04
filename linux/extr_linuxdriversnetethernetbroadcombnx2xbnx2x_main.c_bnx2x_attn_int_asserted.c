#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ int_block; } ;
struct bnx2x {int attn_state; TYPE_1__ common; } ;

/* Variables and functions */
 int ATTN_GENERAL_ATTN_1 ; 
 int ATTN_GENERAL_ATTN_2 ; 
 int ATTN_GENERAL_ATTN_3 ; 
 int ATTN_GENERAL_ATTN_4 ; 
 int ATTN_GENERAL_ATTN_5 ; 
 int ATTN_GENERAL_ATTN_6 ; 
 int ATTN_HARD_WIRED_MASK ; 
 int ATTN_NIG_FOR_FUNC ; 
 int ATTN_SW_TIMER_4_FUNC ; 
 int BAR_IGU_INTMEM ; 
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int BP_PORT (struct bnx2x*) ; 
 int COMMAND_REG_ATTN_BITS_SET ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int GPIO_2_FUNC ; 
 int GPIO_3_FUNC ; 
 int GPIO_4_FUNC ; 
 int HC_REG_COMMAND_REG ; 
 scalar_t__ HW_LOCK_RESOURCE_PORT0_ATT_MASK ; 
 int IGU_CMD_ATTN_BIT_SET_UPPER ; 
 int IGU_REG_ATTENTION_ACK_BITS ; 
 scalar_t__ INT_BLOCK_HC ; 
 int MAX_IGU_ATTN_ACK_TO ; 
 int MISC_REG_AEU_GENERAL_ATTN_1 ; 
 int MISC_REG_AEU_GENERAL_ATTN_2 ; 
 int MISC_REG_AEU_GENERAL_ATTN_3 ; 
 int MISC_REG_AEU_GENERAL_ATTN_4 ; 
 int MISC_REG_AEU_GENERAL_ATTN_5 ; 
 int MISC_REG_AEU_GENERAL_ATTN_6 ; 
 int MISC_REG_AEU_MASK_ATTN_FUNC_0 ; 
 int MISC_REG_AEU_MASK_ATTN_FUNC_1 ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int NIG_REG_MASK_INTERRUPT_PORT0 ; 
 int NIG_REG_MASK_INTERRUPT_PORT1 ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  bnx2x_acquire_hw_lock (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_link_attn (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_release_hw_lock (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_attn_int_asserted(struct bnx2x *bp, u32 asserted)
{
	int port = BP_PORT(bp);
	u32 aeu_addr = port ? MISC_REG_AEU_MASK_ATTN_FUNC_1 :
			      MISC_REG_AEU_MASK_ATTN_FUNC_0;
	u32 nig_int_mask_addr = port ? NIG_REG_MASK_INTERRUPT_PORT1 :
				       NIG_REG_MASK_INTERRUPT_PORT0;
	u32 aeu_mask;
	u32 nig_mask = 0;
	u32 reg_addr;

	if (bp->attn_state & asserted)
		BNX2X_ERR("IGU ERROR\n");

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_PORT0_ATT_MASK + port);
	aeu_mask = REG_RD(bp, aeu_addr);

	DP(NETIF_MSG_HW, "aeu_mask %x  newly asserted %x\n",
	   aeu_mask, asserted);
	aeu_mask &= ~(asserted & 0x3ff);
	DP(NETIF_MSG_HW, "new mask %x\n", aeu_mask);

	REG_WR(bp, aeu_addr, aeu_mask);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_PORT0_ATT_MASK + port);

	DP(NETIF_MSG_HW, "attn_state %x\n", bp->attn_state);
	bp->attn_state |= asserted;
	DP(NETIF_MSG_HW, "new state %x\n", bp->attn_state);

	if (asserted & ATTN_HARD_WIRED_MASK) {
		if (asserted & ATTN_NIG_FOR_FUNC) {

			bnx2x_acquire_phy_lock(bp);

			/* save nig interrupt mask */
			nig_mask = REG_RD(bp, nig_int_mask_addr);

			/* If nig_mask is not set, no need to call the update
			 * function.
			 */
			if (nig_mask) {
				REG_WR(bp, nig_int_mask_addr, 0);

				bnx2x_link_attn(bp);
			}

			/* handle unicore attn? */
		}
		if (asserted & ATTN_SW_TIMER_4_FUNC)
			DP(NETIF_MSG_HW, "ATTN_SW_TIMER_4_FUNC!\n");

		if (asserted & GPIO_2_FUNC)
			DP(NETIF_MSG_HW, "GPIO_2_FUNC!\n");

		if (asserted & GPIO_3_FUNC)
			DP(NETIF_MSG_HW, "GPIO_3_FUNC!\n");

		if (asserted & GPIO_4_FUNC)
			DP(NETIF_MSG_HW, "GPIO_4_FUNC!\n");

		if (port == 0) {
			if (asserted & ATTN_GENERAL_ATTN_1) {
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_1!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_1, 0x0);
			}
			if (asserted & ATTN_GENERAL_ATTN_2) {
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_2!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_2, 0x0);
			}
			if (asserted & ATTN_GENERAL_ATTN_3) {
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_3!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_3, 0x0);
			}
		} else {
			if (asserted & ATTN_GENERAL_ATTN_4) {
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_4!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_4, 0x0);
			}
			if (asserted & ATTN_GENERAL_ATTN_5) {
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_5!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_5, 0x0);
			}
			if (asserted & ATTN_GENERAL_ATTN_6) {
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_6!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_6, 0x0);
			}
		}

	} /* if hardwired */

	if (bp->common.int_block == INT_BLOCK_HC)
		reg_addr = (HC_REG_COMMAND_REG + port*32 +
			    COMMAND_REG_ATTN_BITS_SET);
	else
		reg_addr = (BAR_IGU_INTMEM + IGU_CMD_ATTN_BIT_SET_UPPER*8);

	DP(NETIF_MSG_HW, "about to mask 0x%08x at %s addr 0x%x\n", asserted,
	   (bp->common.int_block == INT_BLOCK_HC) ? "HC" : "IGU", reg_addr);
	REG_WR(bp, reg_addr, asserted);

	/* now set back the mask */
	if (asserted & ATTN_NIG_FOR_FUNC) {
		/* Verify that IGU ack through BAR was written before restoring
		 * NIG mask. This loop should exit after 2-3 iterations max.
		 */
		if (bp->common.int_block != INT_BLOCK_HC) {
			u32 cnt = 0, igu_acked;
			do {
				igu_acked = REG_RD(bp,
						   IGU_REG_ATTENTION_ACK_BITS);
			} while (((igu_acked & ATTN_NIG_FOR_FUNC) == 0) &&
				 (++cnt < MAX_IGU_ATTN_ACK_TO));
			if (!igu_acked)
				DP(NETIF_MSG_HW,
				   "Failed to verify IGU ack on time\n");
			barrier();
		}
		REG_WR(bp, nig_int_mask_addr, nig_mask);
		bnx2x_release_phy_lock(bp);
	}
}