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
typedef  int u64 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct bnx2 {scalar_t__ temp_stats_blk; scalar_t__ stats_blk; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP_ID (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_ID_5706_A0 ; 
 scalar_t__ BNX2_CHIP_ID_5706_A1 ; 
 scalar_t__ BNX2_CHIP_ID_5706_A2 ; 
 scalar_t__ BNX2_CHIP_ID_5708_A0 ; 
 int BNX2_NUM_STATS ; 
 int* bnx2_5706_stats_len_arr ; 
 int* bnx2_5708_stats_len_arr ; 
 unsigned long* bnx2_stats_offset_arr ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
bnx2_get_ethtool_stats(struct net_device *dev,
		struct ethtool_stats *stats, u64 *buf)
{
	struct bnx2 *bp = netdev_priv(dev);
	int i;
	u32 *hw_stats = (u32 *) bp->stats_blk;
	u32 *temp_stats = (u32 *) bp->temp_stats_blk;
	u8 *stats_len_arr = NULL;

	if (!hw_stats) {
		memset(buf, 0, sizeof(u64) * BNX2_NUM_STATS);
		return;
	}

	if ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A2) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_A0))
		stats_len_arr = bnx2_5706_stats_len_arr;
	else
		stats_len_arr = bnx2_5708_stats_len_arr;

	for (i = 0; i < BNX2_NUM_STATS; i++) {
		unsigned long offset;

		if (stats_len_arr[i] == 0) {
			/* skip this counter */
			buf[i] = 0;
			continue;
		}

		offset = bnx2_stats_offset_arr[i];
		if (stats_len_arr[i] == 4) {
			/* 4-byte counter */
			buf[i] = (u64) *(hw_stats + offset) +
				 *(temp_stats + offset);
			continue;
		}
		/* 8-byte counter */
		buf[i] = (((u64) *(hw_stats + offset)) << 32) +
			 *(hw_stats + offset + 1) +
			 (((u64) *(temp_stats + offset)) << 32) +
			 *(temp_stats + offset + 1);
	}
}