#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ beacon_interval; } ;
struct ipw_priv {int status; int quality; int missed_beacons; int last_missed_beacons; int last_rx_err; int last_tx_failures; int rx_packets; int last_rx_packets; int tx_packets; int last_tx_packets; int last_rate; int /*<<< orphan*/  gather_stats; TYPE_2__* ieee; int /*<<< orphan*/  exp_avg_rssi; int /*<<< orphan*/  average_missed_beacons; TYPE_1__ assoc_request; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_4__ {int perfect_rssi; int worst_rssi; } ;

/* Variables and functions */
 int BEACON_THRESHOLD ; 
 int HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_STATS (char*,int,...) ; 
 int /*<<< orphan*/  IPW_ORD_STAT_MISSED_BEACONS ; 
 int /*<<< orphan*/  IPW_ORD_STAT_RX_ERR_CRC ; 
 int /*<<< orphan*/  IPW_ORD_STAT_TX_FAILURE ; 
 int IPW_STATS_INTERVAL ; 
 int STATUS_ASSOCIATED ; 
 int /*<<< orphan*/  average_add (int /*<<< orphan*/ *,int) ; 
 int ipw_get_current_rate (struct ipw_priv*) ; 
 int ipw_get_max_rate (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_get_ordinal (struct ipw_priv*,int /*<<< orphan*/ ,int*,int*) ; 
 int le16_to_cpu (scalar_t__) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ipw_gather_stats(struct ipw_priv *priv)
{
	u32 rx_err, rx_err_delta, rx_packets_delta;
	u32 tx_failures, tx_failures_delta, tx_packets_delta;
	u32 missed_beacons_percent, missed_beacons_delta;
	u32 quality = 0;
	u32 len = sizeof(u32);
	s16 rssi;
	u32 beacon_quality, signal_quality, tx_quality, rx_quality,
	    rate_quality;
	u32 max_rate;

	if (!(priv->status & STATUS_ASSOCIATED)) {
		priv->quality = 0;
		return;
	}

	/* Update the statistics */
	ipw_get_ordinal(priv, IPW_ORD_STAT_MISSED_BEACONS,
			&priv->missed_beacons, &len);
	missed_beacons_delta = priv->missed_beacons - priv->last_missed_beacons;
	priv->last_missed_beacons = priv->missed_beacons;
	if (priv->assoc_request.beacon_interval) {
		missed_beacons_percent = missed_beacons_delta *
		    (HZ * le16_to_cpu(priv->assoc_request.beacon_interval)) /
		    (IPW_STATS_INTERVAL * 10);
	} else {
		missed_beacons_percent = 0;
	}
	average_add(&priv->average_missed_beacons, missed_beacons_percent);

	ipw_get_ordinal(priv, IPW_ORD_STAT_RX_ERR_CRC, &rx_err, &len);
	rx_err_delta = rx_err - priv->last_rx_err;
	priv->last_rx_err = rx_err;

	ipw_get_ordinal(priv, IPW_ORD_STAT_TX_FAILURE, &tx_failures, &len);
	tx_failures_delta = tx_failures - priv->last_tx_failures;
	priv->last_tx_failures = tx_failures;

	rx_packets_delta = priv->rx_packets - priv->last_rx_packets;
	priv->last_rx_packets = priv->rx_packets;

	tx_packets_delta = priv->tx_packets - priv->last_tx_packets;
	priv->last_tx_packets = priv->tx_packets;

	/* Calculate quality based on the following:
	 *
	 * Missed beacon: 100% = 0, 0% = 70% missed
	 * Rate: 60% = 1Mbs, 100% = Max
	 * Rx and Tx errors represent a straight % of total Rx/Tx
	 * RSSI: 100% = > -50,  0% = < -80
	 * Rx errors: 100% = 0, 0% = 50% missed
	 *
	 * The lowest computed quality is used.
	 *
	 */
#define BEACON_THRESHOLD 5
	beacon_quality = 100 - missed_beacons_percent;
	if (beacon_quality < BEACON_THRESHOLD)
		beacon_quality = 0;
	else
		beacon_quality = (beacon_quality - BEACON_THRESHOLD) * 100 /
		    (100 - BEACON_THRESHOLD);
	IPW_DEBUG_STATS("Missed beacon: %3d%% (%d%%)\n",
			beacon_quality, missed_beacons_percent);

	priv->last_rate = ipw_get_current_rate(priv);
	max_rate = ipw_get_max_rate(priv);
	rate_quality = priv->last_rate * 40 / max_rate + 60;
	IPW_DEBUG_STATS("Rate quality : %3d%% (%dMbs)\n",
			rate_quality, priv->last_rate / 1000000);

	if (rx_packets_delta > 100 && rx_packets_delta + rx_err_delta)
		rx_quality = 100 - (rx_err_delta * 100) /
		    (rx_packets_delta + rx_err_delta);
	else
		rx_quality = 100;
	IPW_DEBUG_STATS("Rx quality   : %3d%% (%u errors, %u packets)\n",
			rx_quality, rx_err_delta, rx_packets_delta);

	if (tx_packets_delta > 100 && tx_packets_delta + tx_failures_delta)
		tx_quality = 100 - (tx_failures_delta * 100) /
		    (tx_packets_delta + tx_failures_delta);
	else
		tx_quality = 100;
	IPW_DEBUG_STATS("Tx quality   : %3d%% (%u errors, %u packets)\n",
			tx_quality, tx_failures_delta, tx_packets_delta);

	rssi = priv->exp_avg_rssi;
	signal_quality =
	    (100 *
	     (priv->ieee->perfect_rssi - priv->ieee->worst_rssi) *
	     (priv->ieee->perfect_rssi - priv->ieee->worst_rssi) -
	     (priv->ieee->perfect_rssi - rssi) *
	     (15 * (priv->ieee->perfect_rssi - priv->ieee->worst_rssi) +
	      62 * (priv->ieee->perfect_rssi - rssi))) /
	    ((priv->ieee->perfect_rssi - priv->ieee->worst_rssi) *
	     (priv->ieee->perfect_rssi - priv->ieee->worst_rssi));
	if (signal_quality > 100)
		signal_quality = 100;
	else if (signal_quality < 1)
		signal_quality = 0;

	IPW_DEBUG_STATS("Signal level : %3d%% (%d dBm)\n",
			signal_quality, rssi);

	quality = min(rx_quality, signal_quality);
	quality = min(tx_quality, quality);
	quality = min(rate_quality, quality);
	quality = min(beacon_quality, quality);
	if (quality == beacon_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to missed beacons.\n",
				quality);
	if (quality == rate_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to rate quality.\n",
				quality);
	if (quality == tx_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to Tx quality.\n",
				quality);
	if (quality == rx_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to Rx quality.\n",
				quality);
	if (quality == signal_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to signal quality.\n",
				quality);

	priv->quality = quality;

	schedule_delayed_work(&priv->gather_stats, IPW_STATS_INTERVAL);
}