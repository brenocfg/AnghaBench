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
struct bnxt {int flags; scalar_t__ pri2cos_valid; scalar_t__ fw_tx_stats_ext_size; scalar_t__ fw_rx_stats_ext_size; } ;

/* Variables and functions */
 int BNXT_FLAG_PCIE_STATS ; 
 int BNXT_FLAG_PORT_STATS ; 
 int BNXT_FLAG_PORT_STATS_EXT ; 
 scalar_t__ BNXT_NUM_PCIE_STATS ; 
 scalar_t__ BNXT_NUM_PORT_STATS ; 
 scalar_t__ BNXT_NUM_STATS_PRI ; 
 scalar_t__ BNXT_NUM_SW_FUNC_STATS ; 
 int bnxt_get_num_ring_stats (struct bnxt*) ; 

__attribute__((used)) static int bnxt_get_num_stats(struct bnxt *bp)
{
	int num_stats = bnxt_get_num_ring_stats(bp);

	num_stats += BNXT_NUM_SW_FUNC_STATS;

	if (bp->flags & BNXT_FLAG_PORT_STATS)
		num_stats += BNXT_NUM_PORT_STATS;

	if (bp->flags & BNXT_FLAG_PORT_STATS_EXT) {
		num_stats += bp->fw_rx_stats_ext_size +
			     bp->fw_tx_stats_ext_size;
		if (bp->pri2cos_valid)
			num_stats += BNXT_NUM_STATS_PRI;
	}

	if (bp->flags & BNXT_FLAG_PCIE_STATS)
		num_stats += BNXT_NUM_PCIE_STATS;

	return num_stats;
}