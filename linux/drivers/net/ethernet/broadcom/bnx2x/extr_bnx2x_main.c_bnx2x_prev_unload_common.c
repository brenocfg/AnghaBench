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
struct bnx2x_mac_vals {int /*<<< orphan*/ * bmac_val; scalar_t__ bmac_addr; int /*<<< orphan*/  emac_val; scalar_t__ emac_addr; int /*<<< orphan*/ * umac_val; scalar_t__* umac_addr; int /*<<< orphan*/  xmac_val; scalar_t__ xmac_addr; } ;
struct TYPE_2__ {int port; } ;
struct bnx2x {TYPE_1__ link_params; } ;
typedef  int /*<<< orphan*/  mac_vals ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,...) ; 
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BRB1_REG_NUM_OF_FULL_BLOCKS ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ DORQ_REG_NORM_CID_OFST ; 
 int MISC_REGISTERS_RESET_REG_1_RST_BRB1 ; 
 int /*<<< orphan*/  MISC_REG_RESET_REG_1 ; 
 int /*<<< orphan*/  NIG_REG_NIG_INT_STS_CLR_0 ; 
 scalar_t__ PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_prev_is_after_undi (struct bnx2x*) ; 
 scalar_t__ bnx2x_prev_is_path_marked (struct bnx2x*) ; 
 int bnx2x_prev_mark_path (struct bnx2x*,int) ; 
 int bnx2x_prev_mcp_done (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_prev_unload_close_mac (struct bnx2x*,struct bnx2x_mac_vals*) ; 
 int /*<<< orphan*/  bnx2x_prev_unload_undi_inc (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_reset_common (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_rx_filter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bnx2x_mac_vals*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bnx2x_prev_unload_common(struct bnx2x *bp)
{
	u32 reset_reg, tmp_reg = 0, rc;
	bool prev_undi = false;
	struct bnx2x_mac_vals mac_vals;

	/* It is possible a previous function received 'common' answer,
	 * but hasn't loaded yet, therefore creating a scenario of
	 * multiple functions receiving 'common' on the same path.
	 */
	BNX2X_DEV_INFO("Common unload Flow\n");

	memset(&mac_vals, 0, sizeof(mac_vals));

	if (bnx2x_prev_is_path_marked(bp))
		return bnx2x_prev_mcp_done(bp);

	reset_reg = REG_RD(bp, MISC_REG_RESET_REG_1);

	/* Reset should be performed after BRB is emptied */
	if (reset_reg & MISC_REGISTERS_RESET_REG_1_RST_BRB1) {
		u32 timer_count = 1000;

		/* Close the MAC Rx to prevent BRB from filling up */
		bnx2x_prev_unload_close_mac(bp, &mac_vals);

		/* close LLH filters for both ports towards the BRB */
		bnx2x_set_rx_filter(&bp->link_params, 0);
		bp->link_params.port ^= 1;
		bnx2x_set_rx_filter(&bp->link_params, 0);
		bp->link_params.port ^= 1;

		/* Check if the UNDI driver was previously loaded */
		if (bnx2x_prev_is_after_undi(bp)) {
			prev_undi = true;
			/* clear the UNDI indication */
			REG_WR(bp, DORQ_REG_NORM_CID_OFST, 0);
			/* clear possible idle check errors */
			REG_RD(bp, NIG_REG_NIG_INT_STS_CLR_0);
		}
		if (!CHIP_IS_E1x(bp))
			/* block FW from writing to host */
			REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 0);

		/* wait until BRB is empty */
		tmp_reg = REG_RD(bp, BRB1_REG_NUM_OF_FULL_BLOCKS);
		while (timer_count) {
			u32 prev_brb = tmp_reg;

			tmp_reg = REG_RD(bp, BRB1_REG_NUM_OF_FULL_BLOCKS);
			if (!tmp_reg)
				break;

			BNX2X_DEV_INFO("BRB still has 0x%08x\n", tmp_reg);

			/* reset timer as long as BRB actually gets emptied */
			if (prev_brb > tmp_reg)
				timer_count = 1000;
			else
				timer_count--;

			/* If UNDI resides in memory, manually increment it */
			if (prev_undi)
				bnx2x_prev_unload_undi_inc(bp, 1);

			udelay(10);
		}

		if (!timer_count)
			BNX2X_ERR("Failed to empty BRB, hope for the best\n");
	}

	/* No packets are in the pipeline, path is ready for reset */
	bnx2x_reset_common(bp);

	if (mac_vals.xmac_addr)
		REG_WR(bp, mac_vals.xmac_addr, mac_vals.xmac_val);
	if (mac_vals.umac_addr[0])
		REG_WR(bp, mac_vals.umac_addr[0], mac_vals.umac_val[0]);
	if (mac_vals.umac_addr[1])
		REG_WR(bp, mac_vals.umac_addr[1], mac_vals.umac_val[1]);
	if (mac_vals.emac_addr)
		REG_WR(bp, mac_vals.emac_addr, mac_vals.emac_val);
	if (mac_vals.bmac_addr) {
		REG_WR(bp, mac_vals.bmac_addr, mac_vals.bmac_val[0]);
		REG_WR(bp, mac_vals.bmac_addr + 4, mac_vals.bmac_val[1]);
	}

	rc = bnx2x_prev_mark_path(bp, prev_undi);
	if (rc) {
		bnx2x_prev_mcp_done(bp);
		return rc;
	}

	return bnx2x_prev_mcp_done(bp);
}