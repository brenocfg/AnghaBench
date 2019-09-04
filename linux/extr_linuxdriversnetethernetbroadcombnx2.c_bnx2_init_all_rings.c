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
struct bnx2 {int num_tx_rings; int num_rx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_RLUP_RSS_COMMAND ; 
 int BNX2_RLUP_RSS_COMMAND_HASH_MASK ; 
 int BNX2_RLUP_RSS_COMMAND_RSS_WRITE_MASK ; 
 int BNX2_RLUP_RSS_COMMAND_WRITE ; 
 int /*<<< orphan*/  BNX2_RLUP_RSS_CONFIG ; 
 int BNX2_RLUP_RSS_CONFIG_IPV4_RSS_TYPE_ALL_XI ; 
 int BNX2_RLUP_RSS_CONFIG_IPV6_RSS_TYPE_ALL_XI ; 
 int /*<<< orphan*/  BNX2_RLUP_RSS_DATA ; 
 int BNX2_RXP_SCRATCH_RSS_TBL_MAX_ENTRIES ; 
 int /*<<< orphan*/  BNX2_RXP_SCRATCH_RSS_TBL_SZ ; 
 int /*<<< orphan*/  BNX2_TSCH_TSS_CFG ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int TX_TSS_CID ; 
 int /*<<< orphan*/  bnx2_clear_ring_states (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_init_rx_ring (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_init_tx_ring (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_reg_wr_ind (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_init_all_rings(struct bnx2 *bp)
{
	int i;
	u32 val;

	bnx2_clear_ring_states(bp);

	BNX2_WR(bp, BNX2_TSCH_TSS_CFG, 0);
	for (i = 0; i < bp->num_tx_rings; i++)
		bnx2_init_tx_ring(bp, i);

	if (bp->num_tx_rings > 1)
		BNX2_WR(bp, BNX2_TSCH_TSS_CFG, ((bp->num_tx_rings - 1) << 24) |
			(TX_TSS_CID << 7));

	BNX2_WR(bp, BNX2_RLUP_RSS_CONFIG, 0);
	bnx2_reg_wr_ind(bp, BNX2_RXP_SCRATCH_RSS_TBL_SZ, 0);

	for (i = 0; i < bp->num_rx_rings; i++)
		bnx2_init_rx_ring(bp, i);

	if (bp->num_rx_rings > 1) {
		u32 tbl_32 = 0;

		for (i = 0; i < BNX2_RXP_SCRATCH_RSS_TBL_MAX_ENTRIES; i++) {
			int shift = (i % 8) << 2;

			tbl_32 |= (i % (bp->num_rx_rings - 1)) << shift;
			if ((i % 8) == 7) {
				BNX2_WR(bp, BNX2_RLUP_RSS_DATA, tbl_32);
				BNX2_WR(bp, BNX2_RLUP_RSS_COMMAND, (i >> 3) |
					BNX2_RLUP_RSS_COMMAND_RSS_WRITE_MASK |
					BNX2_RLUP_RSS_COMMAND_WRITE |
					BNX2_RLUP_RSS_COMMAND_HASH_MASK);
				tbl_32 = 0;
			}
		}

		val = BNX2_RLUP_RSS_CONFIG_IPV4_RSS_TYPE_ALL_XI |
		      BNX2_RLUP_RSS_CONFIG_IPV6_RSS_TYPE_ALL_XI;

		BNX2_WR(bp, BNX2_RLUP_RSS_CONFIG, val);

	}
}