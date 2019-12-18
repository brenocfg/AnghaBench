#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct cpsw_common {int rx_ch_num; int tx_ch_num; TYPE_2__* txv; TYPE_1__* rxv; scalar_t__ hw_stats; } ;
struct cpdma_chan_stats {int dummy; } ;
struct TYPE_8__ {int stat_offset; } ;
struct TYPE_7__ {scalar_t__ stat_offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  ch; } ;
struct TYPE_5__ {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int CPSW_STATS_CH_LEN ; 
 int CPSW_STATS_COMMON_LEN ; 
 int /*<<< orphan*/  cpdma_chan_get_stats (int /*<<< orphan*/ ,struct cpdma_chan_stats*) ; 
 TYPE_4__* cpsw_gstrings_ch_stats ; 
 TYPE_3__* cpsw_gstrings_stats ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

void cpsw_get_ethtool_stats(struct net_device *ndev,
			    struct ethtool_stats *stats, u64 *data)
{
	u8 *p;
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	struct cpdma_chan_stats ch_stats;
	int i, l, ch;

	/* Collect Davinci CPDMA stats for Rx and Tx Channel */
	for (l = 0; l < CPSW_STATS_COMMON_LEN; l++)
		data[l] = readl(cpsw->hw_stats +
				cpsw_gstrings_stats[l].stat_offset);

	for (ch = 0; ch < cpsw->rx_ch_num; ch++) {
		cpdma_chan_get_stats(cpsw->rxv[ch].ch, &ch_stats);
		for (i = 0; i < CPSW_STATS_CH_LEN; i++, l++) {
			p = (u8 *)&ch_stats +
				cpsw_gstrings_ch_stats[i].stat_offset;
			data[l] = *(u32 *)p;
		}
	}

	for (ch = 0; ch < cpsw->tx_ch_num; ch++) {
		cpdma_chan_get_stats(cpsw->txv[ch].ch, &ch_stats);
		for (i = 0; i < CPSW_STATS_CH_LEN; i++, l++) {
			p = (u8 *)&ch_stats +
				cpsw_gstrings_ch_stats[i].stat_offset;
			data[l] = *(u32 *)p;
		}
	}
}