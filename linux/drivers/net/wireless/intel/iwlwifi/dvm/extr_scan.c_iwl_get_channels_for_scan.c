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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct iwl_scan_channel {int type; int dsp_atten; int tx_gain; void* passive_dwell; void* active_dwell; void* channel; } ;
struct iwl_priv {TYPE_1__* scan_request; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_channel {int band; scalar_t__ hw_value; int flags; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {int n_channels; struct ieee80211_channel** channels; } ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_IR ; 
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*,int,...) ; 
 int IWL_SCAN_PROBE_MASK (scalar_t__) ; 
 int NL80211_BAND_5GHZ ; 
 int SCAN_CHANNEL_TYPE_ACTIVE ; 
 int SCAN_CHANNEL_TYPE_PASSIVE ; 
 void* cpu_to_le16 (scalar_t__) ; 
 scalar_t__ iwl_get_active_dwell_time (struct iwl_priv*,int,scalar_t__) ; 
 struct ieee80211_supported_band* iwl_get_hw_mode (struct iwl_priv*,int) ; 
 scalar_t__ iwl_get_passive_dwell_time (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 

__attribute__((used)) static int iwl_get_channels_for_scan(struct iwl_priv *priv,
				     struct ieee80211_vif *vif,
				     enum nl80211_band band,
				     u8 is_active, u8 n_probes,
				     struct iwl_scan_channel *scan_ch)
{
	struct ieee80211_channel *chan;
	const struct ieee80211_supported_band *sband;
	u16 passive_dwell = 0;
	u16 active_dwell = 0;
	int added, i;
	u16 channel;

	sband = iwl_get_hw_mode(priv, band);
	if (!sband)
		return 0;

	active_dwell = iwl_get_active_dwell_time(priv, band, n_probes);
	passive_dwell = iwl_get_passive_dwell_time(priv, band);

	if (passive_dwell <= active_dwell)
		passive_dwell = active_dwell + 1;

	for (i = 0, added = 0; i < priv->scan_request->n_channels; i++) {
		chan = priv->scan_request->channels[i];

		if (chan->band != band)
			continue;

		channel = chan->hw_value;
		scan_ch->channel = cpu_to_le16(channel);

		if (!is_active || (chan->flags & IEEE80211_CHAN_NO_IR))
			scan_ch->type = SCAN_CHANNEL_TYPE_PASSIVE;
		else
			scan_ch->type = SCAN_CHANNEL_TYPE_ACTIVE;

		if (n_probes)
			scan_ch->type |= IWL_SCAN_PROBE_MASK(n_probes);

		scan_ch->active_dwell = cpu_to_le16(active_dwell);
		scan_ch->passive_dwell = cpu_to_le16(passive_dwell);

		/* Set txpower levels to defaults */
		scan_ch->dsp_atten = 110;

		/* NOTE: if we were doing 6Mb OFDM for scans we'd use
		 * power level:
		 * scan_ch->tx_gain = ((1 << 5) | (2 << 3)) | 3;
		 */
		if (band == NL80211_BAND_5GHZ)
			scan_ch->tx_gain = ((1 << 5) | (3 << 3)) | 3;
		else
			scan_ch->tx_gain = ((1 << 5) | (5 << 3));

		IWL_DEBUG_SCAN(priv, "Scanning ch=%d prob=0x%X [%s %d]\n",
			       channel, le32_to_cpu(scan_ch->type),
			       (scan_ch->type & SCAN_CHANNEL_TYPE_ACTIVE) ?
				"ACTIVE" : "PASSIVE",
			       (scan_ch->type & SCAN_CHANNEL_TYPE_ACTIVE) ?
			       active_dwell : passive_dwell);

		scan_ch++;
		added++;
	}

	IWL_DEBUG_SCAN(priv, "total channels to scan %d\n", added);
	return added;
}