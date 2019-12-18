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
typedef  scalar_t__ u8 ;
struct mt76_reg_pair {int member_0; scalar_t__ value; int /*<<< orphan*/  member_1; } ;
struct mt7601u_rate_power {TYPE_3__* cck; TYPE_2__* ofdm; } ;
struct cfg80211_chan_def {scalar_t__ width; struct ieee80211_channel* chan; } ;
struct mt7601u_dev {scalar_t__ bw; int chan_ext_below; struct cfg80211_chan_def chandef; int /*<<< orphan*/  state; TYPE_1__* ee; int /*<<< orphan*/  dev; } ;
struct ieee80211_channel {int hw_value; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
struct TYPE_6__ {int /*<<< orphan*/  bw20; } ;
struct TYPE_5__ {int /*<<< orphan*/  bw20; } ;
struct TYPE_4__ {int* chan_pwr; struct mt7601u_rate_power power_rate_table; int /*<<< orphan*/  lna_gain; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mt76_reg_pair*) ; 
 int FREQ_PLAN_REGS ; 
 int /*<<< orphan*/  MT7601U_STATE_SCANNING ; 
 scalar_t__ MT_BW_20 ; 
 scalar_t__ MT_BW_40 ; 
 int /*<<< orphan*/  MT_MCU_MEMMAP_BBP ; 
 int /*<<< orphan*/  MT_MCU_MEMMAP_RF ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_0 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_0 ; 
 int NL80211_CHAN_HT40MINUS ; 
 int NL80211_CHAN_HT40PLUS ; 
 scalar_t__ NL80211_CHAN_WIDTH_40 ; 
 int cfg80211_get_chandef_type (struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int int_to_s6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_agc_reset (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_apply_ch14_fixup (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  mt7601u_bbp_set_bw (struct mt7601u_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mt7601u_bbp_set_ctrlch (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  mt7601u_mac_set_ctrlch (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  mt7601u_rmw (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int) ; 
 int mt7601u_set_bw_filter (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  mt7601u_vco_cal (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int mt7601u_write_reg_pairs (struct mt7601u_dev*,int /*<<< orphan*/ ,struct mt76_reg_pair*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __mt7601u_phy_set_channel(struct mt7601u_dev *dev,
				     struct cfg80211_chan_def *chandef)
{
#define FREQ_PLAN_REGS	4
	static const u8 freq_plan[14][FREQ_PLAN_REGS] = {
		{ 0x99,	0x99,	0x09,	0x50 },
		{ 0x46,	0x44,	0x0a,	0x50 },
		{ 0xec,	0xee,	0x0a,	0x50 },
		{ 0x99,	0x99,	0x0b,	0x50 },
		{ 0x46,	0x44,	0x08,	0x51 },
		{ 0xec,	0xee,	0x08,	0x51 },
		{ 0x99,	0x99,	0x09,	0x51 },
		{ 0x46,	0x44,	0x0a,	0x51 },
		{ 0xec,	0xee,	0x0a,	0x51 },
		{ 0x99,	0x99,	0x0b,	0x51 },
		{ 0x46,	0x44,	0x08,	0x52 },
		{ 0xec,	0xee,	0x08,	0x52 },
		{ 0x99,	0x99,	0x09,	0x52 },
		{ 0x33,	0x33,	0x0b,	0x52 },
	};
	struct mt76_reg_pair channel_freq_plan[FREQ_PLAN_REGS] = {
		{ 17, 0 }, { 18, 0 }, { 19, 0 }, { 20, 0 },
	};
	struct mt76_reg_pair bbp_settings[3] = {
		{ 62, 0x37 - dev->ee->lna_gain },
		{ 63, 0x37 - dev->ee->lna_gain },
		{ 64, 0x37 - dev->ee->lna_gain },
	};

	struct ieee80211_channel *chan = chandef->chan;
	enum nl80211_channel_type chan_type =
		cfg80211_get_chandef_type(chandef);
	struct mt7601u_rate_power *t = &dev->ee->power_rate_table;
	int chan_idx;
	bool chan_ext_below;
	u8 bw;
	int i, ret;

	bw = MT_BW_20;
	chan_ext_below = (chan_type == NL80211_CHAN_HT40MINUS);
	chan_idx = chan->hw_value - 1;

	if (chandef->width == NL80211_CHAN_WIDTH_40) {
		bw = MT_BW_40;

		if (chan_idx > 1 && chan_type == NL80211_CHAN_HT40MINUS)
			chan_idx -= 2;
		else if (chan_idx < 12 && chan_type == NL80211_CHAN_HT40PLUS)
			chan_idx += 2;
		else
			dev_err(dev->dev, "Error: invalid 40MHz channel!!\n");
	}

	if (bw != dev->bw || chan_ext_below != dev->chan_ext_below) {
		dev_dbg(dev->dev, "Info: switching HT mode bw:%d below:%d\n",
			bw, chan_ext_below);

		mt7601u_bbp_set_bw(dev, bw);

		mt7601u_bbp_set_ctrlch(dev, chan_ext_below);
		mt7601u_mac_set_ctrlch(dev, chan_ext_below);
		dev->chan_ext_below = chan_ext_below;
	}

	for (i = 0; i < FREQ_PLAN_REGS; i++)
		channel_freq_plan[i].value = freq_plan[chan_idx][i];

	ret = mt7601u_write_reg_pairs(dev, MT_MCU_MEMMAP_RF,
				      channel_freq_plan, FREQ_PLAN_REGS);
	if (ret)
		return ret;

	mt7601u_rmw(dev, MT_TX_ALC_CFG_0, 0x3f3f,
		    dev->ee->chan_pwr[chan_idx] & 0x3f);

	ret = mt7601u_write_reg_pairs(dev, MT_MCU_MEMMAP_BBP,
				      bbp_settings, ARRAY_SIZE(bbp_settings));
	if (ret)
		return ret;

	mt7601u_vco_cal(dev);
	mt7601u_bbp_set_bw(dev, bw);
	ret = mt7601u_set_bw_filter(dev, false);
	if (ret)
		return ret;

	mt7601u_apply_ch14_fixup(dev, chan->hw_value);
	mt7601u_wr(dev, MT_TX_PWR_CFG_0, int_to_s6(t->ofdm[1].bw20) << 24 |
					 int_to_s6(t->ofdm[0].bw20) << 16 |
					 int_to_s6(t->cck[1].bw20) << 8 |
					 int_to_s6(t->cck[0].bw20));

	if (test_bit(MT7601U_STATE_SCANNING, &dev->state))
		mt7601u_agc_reset(dev);

	dev->chandef = *chandef;

	return 0;
}