#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_12__ {int /*<<< orphan*/  arp_matched; int /*<<< orphan*/  arp_replied; int /*<<< orphan*/  arp_received; } ;
struct TYPE_11__ {int /*<<< orphan*/  wow_evt_discarded; scalar_t__ wow_host_evt_wakeups; scalar_t__ wow_host_pkt_wakeups; int /*<<< orphan*/  wow_pkt_dropped; } ;
struct TYPE_10__ {int /*<<< orphan*/  cs_rssi; int /*<<< orphan*/  cs_snr; int /*<<< orphan*/  cs_last_roam_msec; int /*<<< orphan*/  cs_ave_beacon_rssi; int /*<<< orphan*/  cs_discon_cnt; int /*<<< orphan*/  cs_connect_cnt; int /*<<< orphan*/  cs_low_rssi_cnt; int /*<<< orphan*/  cs_bmiss_cnt; } ;
struct TYPE_9__ {int /*<<< orphan*/  pwr_save_failure_cnt; } ;
struct tkip_ccmp_stats {int /*<<< orphan*/  ccmp_replays; int /*<<< orphan*/  ccmp_fmt_err; int /*<<< orphan*/  tkip_fmt_err; int /*<<< orphan*/  tkip_cnter_measures_invoked; int /*<<< orphan*/  tkip_local_mic_fail; } ;
struct TYPE_8__ {int /*<<< orphan*/  ucast_rate; int /*<<< orphan*/  dupl_frame; int /*<<< orphan*/  decrypt_err; int /*<<< orphan*/  key_cache_miss; int /*<<< orphan*/  crc_err; int /*<<< orphan*/  err; int /*<<< orphan*/  frgment_pkt; int /*<<< orphan*/  bcast_byte; int /*<<< orphan*/  bcast_pkt; int /*<<< orphan*/  mcast_byte; int /*<<< orphan*/  mcast_pkt; int /*<<< orphan*/  ucast_byte; int /*<<< orphan*/  ucast_pkt; int /*<<< orphan*/  byte; int /*<<< orphan*/  pkt; } ;
struct TYPE_13__ {int /*<<< orphan*/  ucast_rate; int /*<<< orphan*/  rts_fail_cnt; int /*<<< orphan*/  mult_retry_cnt; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  fail_cnt; int /*<<< orphan*/  err; int /*<<< orphan*/ * pkt_per_ac; int /*<<< orphan*/  rts_success_cnt; int /*<<< orphan*/  bcast_byte; int /*<<< orphan*/  bcast_pkt; int /*<<< orphan*/  mcast_byte; int /*<<< orphan*/  mcast_pkt; int /*<<< orphan*/  ucast_byte; int /*<<< orphan*/  ucast_pkt; int /*<<< orphan*/  byte; int /*<<< orphan*/  pkt; } ;
struct TYPE_14__ {struct tkip_ccmp_stats tkip_ccmp_stats; TYPE_1__ rx; TYPE_6__ tx; } ;
struct wmi_target_stats {TYPE_5__ arp_stats; TYPE_4__ wow_stats; int /*<<< orphan*/  lq_val; TYPE_3__ cserv_stats; int /*<<< orphan*/  noise_floor_calib; TYPE_2__ pm_stats; TYPE_7__ stats; } ;
struct target_stats {void* arp_matched; void* arp_replied; void* arp_received; int /*<<< orphan*/  wow_evt_discarded; int /*<<< orphan*/  wow_host_evt_wakeups; int /*<<< orphan*/  wow_host_pkt_wakeups; int /*<<< orphan*/  wow_pkt_dropped; void* lq_val; void* cs_rssi; int /*<<< orphan*/  cs_snr; int /*<<< orphan*/  cs_last_roam_msec; void* cs_ave_beacon_rssi; int /*<<< orphan*/  cs_discon_cnt; int /*<<< orphan*/  cs_connect_cnt; int /*<<< orphan*/  cs_low_rssi_cnt; int /*<<< orphan*/  cs_bmiss_cnt; void* noise_floor_calib; int /*<<< orphan*/  pwr_save_fail_cnt; int /*<<< orphan*/  ccmp_replays; int /*<<< orphan*/  ccmp_fmt_err; int /*<<< orphan*/  tkip_fmt_err; int /*<<< orphan*/  tkip_cnter_measures_invoked; int /*<<< orphan*/  tkip_local_mic_fail; void* rx_ucast_rate; int /*<<< orphan*/  rx_dupl_frame; int /*<<< orphan*/  rx_decrypt_err; int /*<<< orphan*/  rx_key_cache_miss; int /*<<< orphan*/  rx_crc_err; int /*<<< orphan*/  rx_err; int /*<<< orphan*/  rx_frgment_pkt; int /*<<< orphan*/  rx_bcast_byte; int /*<<< orphan*/  rx_bcast_pkt; int /*<<< orphan*/  rx_mcast_byte; int /*<<< orphan*/  rx_mcast_pkt; int /*<<< orphan*/  rx_ucast_byte; int /*<<< orphan*/  rx_ucast_pkt; int /*<<< orphan*/  rx_byte; int /*<<< orphan*/  rx_pkt; void* tx_ucast_rate; int /*<<< orphan*/  tx_rts_fail_cnt; int /*<<< orphan*/  tx_mult_retry_cnt; int /*<<< orphan*/  tx_retry_cnt; int /*<<< orphan*/  tx_fail_cnt; int /*<<< orphan*/  tx_err; int /*<<< orphan*/ * tx_pkt_per_ac; int /*<<< orphan*/  tx_rts_success_cnt; int /*<<< orphan*/  tx_bcast_byte; int /*<<< orphan*/  tx_bcast_pkt; int /*<<< orphan*/  tx_mcast_byte; int /*<<< orphan*/  tx_mcast_pkt; int /*<<< orphan*/  tx_ucast_byte; int /*<<< orphan*/  tx_ucast_pkt; int /*<<< orphan*/  tx_byte; int /*<<< orphan*/  tx_pkt; } ;
struct ath6kl_vif {int /*<<< orphan*/  flags; struct target_stats target_stats; struct ath6kl* ar; } ;
struct ath6kl {int /*<<< orphan*/  event_wq; int /*<<< orphan*/  wmi; } ;
typedef  void* s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_TRC ; 
 int /*<<< orphan*/  STATS_UPDATE_PEND ; 
 size_t WMM_NUM_AC ; 
 void* a_sle16_to_cpu (int /*<<< orphan*/ ) ; 
 void* a_sle32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 void* ath6kl_wmi_get_rate (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_update_target_stats(struct ath6kl_vif *vif, u8 *ptr, u32 len)
{
	struct wmi_target_stats *tgt_stats =
		(struct wmi_target_stats *) ptr;
	struct ath6kl *ar = vif->ar;
	struct target_stats *stats = &vif->target_stats;
	struct tkip_ccmp_stats *ccmp_stats;
	s32 rate;
	u8 ac;

	if (len < sizeof(*tgt_stats))
		return;

	ath6kl_dbg(ATH6KL_DBG_TRC, "updating target stats\n");

	stats->tx_pkt += le32_to_cpu(tgt_stats->stats.tx.pkt);
	stats->tx_byte += le32_to_cpu(tgt_stats->stats.tx.byte);
	stats->tx_ucast_pkt += le32_to_cpu(tgt_stats->stats.tx.ucast_pkt);
	stats->tx_ucast_byte += le32_to_cpu(tgt_stats->stats.tx.ucast_byte);
	stats->tx_mcast_pkt += le32_to_cpu(tgt_stats->stats.tx.mcast_pkt);
	stats->tx_mcast_byte += le32_to_cpu(tgt_stats->stats.tx.mcast_byte);
	stats->tx_bcast_pkt  += le32_to_cpu(tgt_stats->stats.tx.bcast_pkt);
	stats->tx_bcast_byte += le32_to_cpu(tgt_stats->stats.tx.bcast_byte);
	stats->tx_rts_success_cnt +=
		le32_to_cpu(tgt_stats->stats.tx.rts_success_cnt);

	for (ac = 0; ac < WMM_NUM_AC; ac++)
		stats->tx_pkt_per_ac[ac] +=
			le32_to_cpu(tgt_stats->stats.tx.pkt_per_ac[ac]);

	stats->tx_err += le32_to_cpu(tgt_stats->stats.tx.err);
	stats->tx_fail_cnt += le32_to_cpu(tgt_stats->stats.tx.fail_cnt);
	stats->tx_retry_cnt += le32_to_cpu(tgt_stats->stats.tx.retry_cnt);
	stats->tx_mult_retry_cnt +=
		le32_to_cpu(tgt_stats->stats.tx.mult_retry_cnt);
	stats->tx_rts_fail_cnt +=
		le32_to_cpu(tgt_stats->stats.tx.rts_fail_cnt);

	rate = a_sle32_to_cpu(tgt_stats->stats.tx.ucast_rate);
	stats->tx_ucast_rate = ath6kl_wmi_get_rate(ar->wmi, rate);

	stats->rx_pkt += le32_to_cpu(tgt_stats->stats.rx.pkt);
	stats->rx_byte += le32_to_cpu(tgt_stats->stats.rx.byte);
	stats->rx_ucast_pkt += le32_to_cpu(tgt_stats->stats.rx.ucast_pkt);
	stats->rx_ucast_byte += le32_to_cpu(tgt_stats->stats.rx.ucast_byte);
	stats->rx_mcast_pkt += le32_to_cpu(tgt_stats->stats.rx.mcast_pkt);
	stats->rx_mcast_byte += le32_to_cpu(tgt_stats->stats.rx.mcast_byte);
	stats->rx_bcast_pkt += le32_to_cpu(tgt_stats->stats.rx.bcast_pkt);
	stats->rx_bcast_byte += le32_to_cpu(tgt_stats->stats.rx.bcast_byte);
	stats->rx_frgment_pkt += le32_to_cpu(tgt_stats->stats.rx.frgment_pkt);
	stats->rx_err += le32_to_cpu(tgt_stats->stats.rx.err);
	stats->rx_crc_err += le32_to_cpu(tgt_stats->stats.rx.crc_err);
	stats->rx_key_cache_miss +=
		le32_to_cpu(tgt_stats->stats.rx.key_cache_miss);
	stats->rx_decrypt_err += le32_to_cpu(tgt_stats->stats.rx.decrypt_err);
	stats->rx_dupl_frame += le32_to_cpu(tgt_stats->stats.rx.dupl_frame);

	rate = a_sle32_to_cpu(tgt_stats->stats.rx.ucast_rate);
	stats->rx_ucast_rate = ath6kl_wmi_get_rate(ar->wmi, rate);

	ccmp_stats = &tgt_stats->stats.tkip_ccmp_stats;

	stats->tkip_local_mic_fail +=
		le32_to_cpu(ccmp_stats->tkip_local_mic_fail);
	stats->tkip_cnter_measures_invoked +=
		le32_to_cpu(ccmp_stats->tkip_cnter_measures_invoked);
	stats->tkip_fmt_err += le32_to_cpu(ccmp_stats->tkip_fmt_err);

	stats->ccmp_fmt_err += le32_to_cpu(ccmp_stats->ccmp_fmt_err);
	stats->ccmp_replays += le32_to_cpu(ccmp_stats->ccmp_replays);

	stats->pwr_save_fail_cnt +=
		le32_to_cpu(tgt_stats->pm_stats.pwr_save_failure_cnt);
	stats->noise_floor_calib =
		a_sle32_to_cpu(tgt_stats->noise_floor_calib);

	stats->cs_bmiss_cnt +=
		le32_to_cpu(tgt_stats->cserv_stats.cs_bmiss_cnt);
	stats->cs_low_rssi_cnt +=
		le32_to_cpu(tgt_stats->cserv_stats.cs_low_rssi_cnt);
	stats->cs_connect_cnt +=
		le16_to_cpu(tgt_stats->cserv_stats.cs_connect_cnt);
	stats->cs_discon_cnt +=
		le16_to_cpu(tgt_stats->cserv_stats.cs_discon_cnt);

	stats->cs_ave_beacon_rssi =
		a_sle16_to_cpu(tgt_stats->cserv_stats.cs_ave_beacon_rssi);

	stats->cs_last_roam_msec =
		tgt_stats->cserv_stats.cs_last_roam_msec;
	stats->cs_snr = tgt_stats->cserv_stats.cs_snr;
	stats->cs_rssi = a_sle16_to_cpu(tgt_stats->cserv_stats.cs_rssi);

	stats->lq_val = le32_to_cpu(tgt_stats->lq_val);

	stats->wow_pkt_dropped +=
		le32_to_cpu(tgt_stats->wow_stats.wow_pkt_dropped);
	stats->wow_host_pkt_wakeups +=
		tgt_stats->wow_stats.wow_host_pkt_wakeups;
	stats->wow_host_evt_wakeups +=
		tgt_stats->wow_stats.wow_host_evt_wakeups;
	stats->wow_evt_discarded +=
		le16_to_cpu(tgt_stats->wow_stats.wow_evt_discarded);

	stats->arp_received = le32_to_cpu(tgt_stats->arp_stats.arp_received);
	stats->arp_replied = le32_to_cpu(tgt_stats->arp_stats.arp_replied);
	stats->arp_matched = le32_to_cpu(tgt_stats->arp_stats.arp_matched);

	if (test_bit(STATS_UPDATE_PEND, &vif->flags)) {
		clear_bit(STATS_UPDATE_PEND, &vif->flags);
		wake_up(&ar->event_wq);
	}
}