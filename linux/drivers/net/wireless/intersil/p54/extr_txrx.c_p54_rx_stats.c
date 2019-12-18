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
typedef  scalar_t__ u32 ;
struct survey_info {unsigned int time; unsigned int time_tx; unsigned int time_busy; int /*<<< orphan*/  noise; } ;
struct sk_buff {scalar_t__ data; } ;
struct p54_statistics {int /*<<< orphan*/ * sample_noise; int /*<<< orphan*/  sample_tx; int /*<<< orphan*/  sample_cca; int /*<<< orphan*/  noise; int /*<<< orphan*/  rx_bad_fcs; int /*<<< orphan*/  rts_success; int /*<<< orphan*/  rts_fail; int /*<<< orphan*/  tsf32; } ;
struct p54_hdr {int /*<<< orphan*/  req_id; scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ timestamp; unsigned int cached_cca; unsigned int cached_rssi; unsigned int cached_tx; unsigned int cca; unsigned int tx; unsigned int rssi; unsigned int active; } ;
struct TYPE_3__ {unsigned int dot11RTSFailureCount; unsigned int dot11RTSSuccessCount; unsigned int dot11FCSErrorCount; } ;
struct p54_common {scalar_t__ mode; scalar_t__ tsf_low32; int update_stats; int /*<<< orphan*/  stat_comp; TYPE_2__ survey_raw; int /*<<< orphan*/  noise; struct survey_info* survey; struct ieee80211_channel* curchan; scalar_t__ phy_idle; scalar_t__ phy_ps; TYPE_1__ stats; int /*<<< orphan*/  tsf_high32; } ;
struct ieee80211_channel {size_t hw_value; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 unsigned int USEC_PER_SEC ; 
 int /*<<< orphan*/  clamp (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  do_div (unsigned int,int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* p54_find_and_unlink_skb (struct p54_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54_rssi_to_dbm (struct p54_common*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void p54_rx_stats(struct p54_common *priv, struct sk_buff *skb)
{
	struct p54_hdr *hdr = (struct p54_hdr *) skb->data;
	struct p54_statistics *stats = (struct p54_statistics *) hdr->data;
	struct sk_buff *tmp;
	struct ieee80211_channel *chan;
	unsigned int i, rssi, tx, cca, dtime, dtotal, dcca, dtx, drssi, unit;
	u32 tsf32;

	if (unlikely(priv->mode == NL80211_IFTYPE_UNSPECIFIED))
		return ;

	tsf32 = le32_to_cpu(stats->tsf32);
	if (tsf32 < priv->tsf_low32)
		priv->tsf_high32++;
	priv->tsf_low32 = tsf32;

	priv->stats.dot11RTSFailureCount = le32_to_cpu(stats->rts_fail);
	priv->stats.dot11RTSSuccessCount = le32_to_cpu(stats->rts_success);
	priv->stats.dot11FCSErrorCount = le32_to_cpu(stats->rx_bad_fcs);

	priv->noise = p54_rssi_to_dbm(priv, le32_to_cpu(stats->noise));

	/*
	 * STSW450X LMAC API page 26 - 3.8 Statistics
	 * "The exact measurement period can be derived from the
	 * timestamp member".
	 */
	dtime = tsf32 - priv->survey_raw.timestamp;

	/*
	 * STSW450X LMAC API page 26 - 3.8.1 Noise histogram
	 * The LMAC samples RSSI, CCA and transmit state at regular
	 * periods (typically 8 times per 1k [as in 1024] usec).
	 */
	cca = le32_to_cpu(stats->sample_cca);
	tx = le32_to_cpu(stats->sample_tx);
	rssi = 0;
	for (i = 0; i < ARRAY_SIZE(stats->sample_noise); i++)
		rssi += le32_to_cpu(stats->sample_noise[i]);

	dcca = cca - priv->survey_raw.cached_cca;
	drssi = rssi - priv->survey_raw.cached_rssi;
	dtx = tx - priv->survey_raw.cached_tx;
	dtotal = dcca + drssi + dtx;

	/*
	 * update statistics when more than a second is over since the
	 * last call, or when a update is badly needed.
	 */
	if (dtotal && (priv->update_stats || dtime >= USEC_PER_SEC) &&
	    dtime >= dtotal) {
		priv->survey_raw.timestamp = tsf32;
		priv->update_stats = false;
		unit = dtime / dtotal;

		if (dcca) {
			priv->survey_raw.cca += dcca * unit;
			priv->survey_raw.cached_cca = cca;
		}
		if (dtx) {
			priv->survey_raw.tx += dtx * unit;
			priv->survey_raw.cached_tx = tx;
		}
		if (drssi) {
			priv->survey_raw.rssi += drssi * unit;
			priv->survey_raw.cached_rssi = rssi;
		}

		/* 1024 usec / 8 times = 128 usec / time */
		if (!(priv->phy_ps || priv->phy_idle))
			priv->survey_raw.active += dtotal * unit;
		else
			priv->survey_raw.active += (dcca + dtx) * unit;
	}

	chan = priv->curchan;
	if (chan) {
		struct survey_info *survey = &priv->survey[chan->hw_value];
		survey->noise = clamp(priv->noise, -128, 127);
		survey->time = priv->survey_raw.active;
		survey->time_tx = priv->survey_raw.tx;
		survey->time_busy = priv->survey_raw.tx +
			priv->survey_raw.cca;
		do_div(survey->time, 1024);
		do_div(survey->time_tx, 1024);
		do_div(survey->time_busy, 1024);
	}

	tmp = p54_find_and_unlink_skb(priv, hdr->req_id);
	dev_kfree_skb_any(tmp);
	complete(&priv->stat_comp);
}