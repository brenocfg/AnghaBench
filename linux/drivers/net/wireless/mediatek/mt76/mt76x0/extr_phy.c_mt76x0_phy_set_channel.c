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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  hw; int /*<<< orphan*/  state; } ;
struct mt76x02_dev {int /*<<< orphan*/  cal_work; TYPE_2__ mt76; } ;
struct cfg80211_chan_def {int center_freq1; int const width; TYPE_1__* chan; } ;
struct TYPE_3__ {int center_freq; int hw_value; int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CORE ; 
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  MT76_SCANNING ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_CALIBRATE_INTERVAL ; 
 int /*<<< orphan*/  MT_EXT_CCA_CFG ; 
 int MT_EXT_CCA_CFG_CCA0 ; 
 int MT_EXT_CCA_CFG_CCA1 ; 
 int MT_EXT_CCA_CFG_CCA2 ; 
 int MT_EXT_CCA_CFG_CCA3 ; 
 int MT_EXT_CCA_CFG_CCA_MASK ; 
 int /*<<< orphan*/  MT_RF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_TX_SW_CFG0 ; 
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_80 128 
 int /*<<< orphan*/  RF_A_BAND ; 
 int /*<<< orphan*/  RF_BW_20 ; 
 int /*<<< orphan*/  RF_BW_40 ; 
 int /*<<< orphan*/  RF_BW_80 ; 
 int /*<<< orphan*/  RF_G_BAND ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mt76_is_usb (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_init_agc_gain (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_phy_set_band (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_phy_set_bw (struct mt76x02_dev*,int const,int) ; 
 int /*<<< orphan*/  mt76x0_phy_bbp_set_bw (struct mt76x02_dev*,int const) ; 
 int /*<<< orphan*/  mt76x0_phy_calibrate (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x0_phy_set_band (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_phy_set_chan_bbp_params (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_phy_set_chan_rf_params (struct mt76x02_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_phy_set_txpower (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x0_read_rx_gain (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x0_rf_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mt76x0_phy_set_channel(struct mt76x02_dev *dev,
			    struct cfg80211_chan_def *chandef)
{
	u32 ext_cca_chan[4] = {
		[0] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(0)),
		[1] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(1)),
		[2] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(2)),
		[3] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(3)),
	};
	bool scan = test_bit(MT76_SCANNING, &dev->mt76.state);
	int ch_group_index, freq, freq1;
	u8 channel;
	u32 val;
	u16 rf_bw_band;

	freq = chandef->chan->center_freq;
	freq1 = chandef->center_freq1;
	channel = chandef->chan->hw_value;
	rf_bw_band = (channel <= 14) ? RF_G_BAND : RF_A_BAND;

	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_40:
		if (freq1 > freq)
			ch_group_index = 0;
		else
			ch_group_index = 1;
		channel += 2 - ch_group_index * 4;
		rf_bw_band |= RF_BW_40;
		break;
	case NL80211_CHAN_WIDTH_80:
		ch_group_index = (freq - freq1 + 30) / 20;
		if (WARN_ON(ch_group_index < 0 || ch_group_index > 3))
			ch_group_index = 0;
		channel += 6 - ch_group_index * 4;
		rf_bw_band |= RF_BW_80;
		break;
	default:
		ch_group_index = 0;
		rf_bw_band |= RF_BW_20;
		break;
	}

	if (mt76_is_usb(dev)) {
		mt76x0_phy_bbp_set_bw(dev, chandef->width);
	} else {
		if (chandef->width == NL80211_CHAN_WIDTH_80 ||
		    chandef->width == NL80211_CHAN_WIDTH_40)
			val = 0x201;
		else
			val = 0x601;
		mt76_wr(dev, MT_TX_SW_CFG0, val);
	}
	mt76x02_phy_set_bw(dev, chandef->width, ch_group_index);
	mt76x02_phy_set_band(dev, chandef->chan->band,
			     ch_group_index & 1);

	mt76_rmw(dev, MT_EXT_CCA_CFG,
		 (MT_EXT_CCA_CFG_CCA0 |
		  MT_EXT_CCA_CFG_CCA1 |
		  MT_EXT_CCA_CFG_CCA2 |
		  MT_EXT_CCA_CFG_CCA3 |
		  MT_EXT_CCA_CFG_CCA_MASK),
		 ext_cca_chan[ch_group_index]);

	mt76x0_phy_set_band(dev, chandef->chan->band);
	mt76x0_phy_set_chan_rf_params(dev, channel, rf_bw_band);

	/* set Japan Tx filter at channel 14 */
	if (channel == 14)
		mt76_set(dev, MT_BBP(CORE, 1), 0x20);
	else
		mt76_clear(dev, MT_BBP(CORE, 1), 0x20);

	mt76x0_read_rx_gain(dev);
	mt76x0_phy_set_chan_bbp_params(dev, rf_bw_band);

	/* enable vco */
	mt76x0_rf_set(dev, MT_RF(0, 4), BIT(7));
	if (scan)
		return;

	mt76x02_init_agc_gain(dev);
	mt76x0_phy_calibrate(dev, false);
	mt76x0_phy_set_txpower(dev);

	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
}