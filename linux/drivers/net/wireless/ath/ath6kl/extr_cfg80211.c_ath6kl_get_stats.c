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
typedef  scalar_t__ u64 ;
struct target_stats {scalar_t__ arp_replied; scalar_t__ arp_matched; scalar_t__ arp_received; scalar_t__ cs_ave_beacon_rssi; scalar_t__ cs_discon_cnt; scalar_t__ cs_connect_cnt; scalar_t__ cs_bmiss_cnt; scalar_t__ ccmp_replays; scalar_t__ ccmp_fmt_err; scalar_t__ tkip_fmt_err; scalar_t__ tkip_local_mic_fail; scalar_t__ rx_dupl_frame; scalar_t__ rx_decrypt_err; scalar_t__ rx_key_cache_miss; scalar_t__ rx_crc_err; scalar_t__ rx_err; scalar_t__ rx_frgment_pkt; scalar_t__ rx_bcast_byte; scalar_t__ rx_ucast_byte; scalar_t__ rx_bcast_pkt; scalar_t__ rx_ucast_rate; scalar_t__ rx_ucast_pkt; scalar_t__ tkip_cnter_measures_invoked; scalar_t__ tx_rts_fail_cnt; scalar_t__ tx_mult_retry_cnt; scalar_t__ tx_retry_cnt; scalar_t__ tx_fail_cnt; scalar_t__ tx_err; scalar_t__ tx_rts_success_cnt; scalar_t__ tx_bcast_byte; scalar_t__ tx_ucast_byte; scalar_t__ tx_bcast_pkt; scalar_t__ tx_ucast_pkt; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct ath6kl_vif {struct target_stats target_stats; struct ath6kl* ar; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int ATH6KL_STATS_LEN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int,int) ; 
 int /*<<< orphan*/  ath6kl_read_tgt_stats (struct ath6kl*,struct ath6kl_vif*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ath6kl_get_stats(struct net_device *dev,
			    struct ethtool_stats *stats,
			    u64 *data)
{
	struct ath6kl_vif *vif = netdev_priv(dev);
	struct ath6kl *ar = vif->ar;
	int i = 0;
	struct target_stats *tgt_stats;

	memset(data, 0, sizeof(u64) * ATH6KL_STATS_LEN);

	ath6kl_read_tgt_stats(ar, vif);

	tgt_stats = &vif->target_stats;

	data[i++] = tgt_stats->tx_ucast_pkt + tgt_stats->tx_bcast_pkt;
	data[i++] = tgt_stats->tx_ucast_byte + tgt_stats->tx_bcast_byte;
	data[i++] = tgt_stats->rx_ucast_pkt + tgt_stats->rx_bcast_pkt;
	data[i++] = tgt_stats->rx_ucast_byte + tgt_stats->rx_bcast_byte;

	data[i++] = tgt_stats->tx_ucast_pkt;
	data[i++] = tgt_stats->tx_bcast_pkt;
	data[i++] = tgt_stats->tx_ucast_byte;
	data[i++] = tgt_stats->tx_bcast_byte;
	data[i++] = tgt_stats->tx_rts_success_cnt;
	data[i++] = tgt_stats->tx_err;
	data[i++] = tgt_stats->tx_fail_cnt;
	data[i++] = tgt_stats->tx_retry_cnt;
	data[i++] = tgt_stats->tx_mult_retry_cnt;
	data[i++] = tgt_stats->tx_rts_fail_cnt;
	data[i++] = tgt_stats->tkip_cnter_measures_invoked;

	data[i++] = tgt_stats->rx_ucast_pkt;
	data[i++] = tgt_stats->rx_ucast_rate;
	data[i++] = tgt_stats->rx_bcast_pkt;
	data[i++] = tgt_stats->rx_ucast_byte;
	data[i++] = tgt_stats->rx_bcast_byte;
	data[i++] = tgt_stats->rx_frgment_pkt;
	data[i++] = tgt_stats->rx_err;
	data[i++] = tgt_stats->rx_crc_err;
	data[i++] = tgt_stats->rx_key_cache_miss;
	data[i++] = tgt_stats->rx_decrypt_err;
	data[i++] = tgt_stats->rx_dupl_frame;
	data[i++] = tgt_stats->tkip_local_mic_fail;
	data[i++] = tgt_stats->tkip_fmt_err;
	data[i++] = tgt_stats->ccmp_fmt_err;
	data[i++] = tgt_stats->ccmp_replays;

	data[i++] = tgt_stats->cs_bmiss_cnt;
	data[i++] = tgt_stats->cs_connect_cnt;
	data[i++] = tgt_stats->cs_discon_cnt;
	data[i++] = tgt_stats->cs_ave_beacon_rssi;
	data[i++] = tgt_stats->arp_received;
	data[i++] = tgt_stats->arp_matched;
	data[i++] = tgt_stats->arp_replied;

	if (i !=  ATH6KL_STATS_LEN) {
		WARN_ON_ONCE(1);
		ath6kl_err("ethtool stats error, i: %d  STATS_LEN: %d\n",
			   i, (int)ATH6KL_STATS_LEN);
	}
}