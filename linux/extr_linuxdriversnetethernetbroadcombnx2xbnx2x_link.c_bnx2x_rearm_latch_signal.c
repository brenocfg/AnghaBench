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
typedef  int u8 ;
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ NIG_REG_LATCH_STATUS_0 ; 
 scalar_t__ NIG_REG_STATUS_INTERRUPT_PORT0 ; 
 int /*<<< orphan*/  NIG_STATUS_EMAC0_MI_INT ; 
 int REG_RD (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_bits_dis (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_bits_en (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_rearm_latch_signal(struct bnx2x *bp, u8 port,
				     u8 exp_mi_int)
{
	u32 latch_status = 0;

	/* Disable the MI INT ( external phy int ) by writing 1 to the
	 * status register. Link down indication is high-active-signal,
	 * so in this case we need to write the status to clear the XOR
	 */
	/* Read Latched signals */
	latch_status = REG_RD(bp,
				    NIG_REG_LATCH_STATUS_0 + port*8);
	DP(NETIF_MSG_LINK, "latch_status = 0x%x\n", latch_status);
	/* Handle only those with latched-signal=up.*/
	if (exp_mi_int)
		bnx2x_bits_en(bp,
			      NIG_REG_STATUS_INTERRUPT_PORT0
			      + port*4,
			      NIG_STATUS_EMAC0_MI_INT);
	else
		bnx2x_bits_dis(bp,
			       NIG_REG_STATUS_INTERRUPT_PORT0
			       + port*4,
			       NIG_STATUS_EMAC0_MI_INT);

	if (latch_status & 1) {

		/* For all latched-signal=up : Re-Arm Latch signals */
		REG_WR(bp, NIG_REG_LATCH_STATUS_0 + port*8,
		       (latch_status & 0xfffe) | (latch_status & 1));
	}
	/* For all latched-signal=up,Write original_signal to status */
}