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
typedef  int u64 ;
struct mtk_mac {int /*<<< orphan*/  hw; struct mtk_hw_stats* hw_stats; } ;
struct mtk_hw_stats {int rx_bytes; int rx_packets; int rx_overflow; int rx_fcs_errors; int rx_short_errors; int rx_long_errors; int rx_checksum_errors; int rx_flow_control_packets; int tx_skip; int tx_collisions; int tx_bytes; int tx_packets; int /*<<< orphan*/  syncp; scalar_t__ reg_offset; } ;

/* Variables and functions */
 unsigned int MTK_GDM1_TX_GBCNT ; 
 int mtk_r32 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void mtk_stats_update_mac(struct mtk_mac *mac)
{
	struct mtk_hw_stats *hw_stats = mac->hw_stats;
	unsigned int base = MTK_GDM1_TX_GBCNT;
	u64 stats;

	base += hw_stats->reg_offset;

	u64_stats_update_begin(&hw_stats->syncp);

	hw_stats->rx_bytes += mtk_r32(mac->hw, base);
	stats =  mtk_r32(mac->hw, base + 0x04);
	if (stats)
		hw_stats->rx_bytes += (stats << 32);
	hw_stats->rx_packets += mtk_r32(mac->hw, base + 0x08);
	hw_stats->rx_overflow += mtk_r32(mac->hw, base + 0x10);
	hw_stats->rx_fcs_errors += mtk_r32(mac->hw, base + 0x14);
	hw_stats->rx_short_errors += mtk_r32(mac->hw, base + 0x18);
	hw_stats->rx_long_errors += mtk_r32(mac->hw, base + 0x1c);
	hw_stats->rx_checksum_errors += mtk_r32(mac->hw, base + 0x20);
	hw_stats->rx_flow_control_packets +=
					mtk_r32(mac->hw, base + 0x24);
	hw_stats->tx_skip += mtk_r32(mac->hw, base + 0x28);
	hw_stats->tx_collisions += mtk_r32(mac->hw, base + 0x2c);
	hw_stats->tx_bytes += mtk_r32(mac->hw, base + 0x30);
	stats =  mtk_r32(mac->hw, base + 0x34);
	if (stats)
		hw_stats->tx_bytes += (stats << 32);
	hw_stats->tx_packets += mtk_r32(mac->hw, base + 0x38);
	u64_stats_update_end(&hw_stats->syncp);
}