#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mt76x2_tx_power_info {int delta_bw40; int delta_bw80; int target_power; TYPE_2__* chain; } ;
struct mt76_rate_power {int dummy; } ;
struct TYPE_4__ {int width; struct ieee80211_channel* chan; } ;
struct TYPE_6__ {struct mt76_rate_power rate_power; int /*<<< orphan*/  txpower_cur; int /*<<< orphan*/  txpower_conf; TYPE_1__ chandef; } ;
struct mt76x02_dev {int target_power; int* target_power_delta; TYPE_3__ mt76; } ;
struct ieee80211_channel {int dummy; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;
struct TYPE_5__ {int target_power; int delta; } ;

/* Variables and functions */
 int NL80211_CHAN_WIDTH_40 ; 
 int NL80211_CHAN_WIDTH_80 ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mt76x02_add_rate_power_offset (struct mt76_rate_power*,int) ; 
 int /*<<< orphan*/  mt76x02_get_max_rate_power (struct mt76_rate_power*) ; 
 int /*<<< orphan*/  mt76x02_limit_rate_power (struct mt76_rate_power*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_phy_set_txpower (struct mt76x02_dev*,int,int) ; 
 int mt76x2_get_min_rate_power (struct mt76_rate_power*) ; 
 int /*<<< orphan*/  mt76x2_get_power_info (struct mt76x02_dev*,struct mt76x2_tx_power_info*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  mt76x2_get_rate_power (struct mt76x02_dev*,struct mt76_rate_power*,struct ieee80211_channel*) ; 

void mt76x2_phy_set_txpower(struct mt76x02_dev *dev)
{
	enum nl80211_chan_width width = dev->mt76.chandef.width;
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	struct mt76x2_tx_power_info txp;
	int txp_0, txp_1, delta = 0;
	struct mt76_rate_power t = {};
	int base_power, gain;

	mt76x2_get_power_info(dev, &txp, chan);

	if (width == NL80211_CHAN_WIDTH_40)
		delta = txp.delta_bw40;
	else if (width == NL80211_CHAN_WIDTH_80)
		delta = txp.delta_bw80;

	mt76x2_get_rate_power(dev, &t, chan);
	mt76x02_add_rate_power_offset(&t, txp.target_power + delta);
	mt76x02_limit_rate_power(&t, dev->mt76.txpower_conf);
	dev->mt76.txpower_cur = mt76x02_get_max_rate_power(&t);

	base_power = mt76x2_get_min_rate_power(&t);
	delta = base_power - txp.target_power;
	txp_0 = txp.chain[0].target_power + txp.chain[0].delta + delta;
	txp_1 = txp.chain[1].target_power + txp.chain[1].delta + delta;

	gain = min(txp_0, txp_1);
	if (gain < 0) {
		base_power -= gain;
		txp_0 -= gain;
		txp_1 -= gain;
	} else if (gain > 0x2f) {
		base_power -= gain - 0x2f;
		txp_0 = 0x2f;
		txp_1 = 0x2f;
	}

	mt76x02_add_rate_power_offset(&t, -base_power);
	dev->target_power = txp.target_power;
	dev->target_power_delta[0] = txp_0 - txp.chain[0].target_power;
	dev->target_power_delta[1] = txp_1 - txp.chain[0].target_power;
	dev->mt76.rate_power = t;

	mt76x02_phy_set_txpower(dev, txp_0, txp_1);
}