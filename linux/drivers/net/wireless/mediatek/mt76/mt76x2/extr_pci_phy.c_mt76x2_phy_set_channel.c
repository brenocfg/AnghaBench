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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  mcu_gain; } ;
struct TYPE_6__ {int channel_cal_done; int init_cal_done; TYPE_2__ rx; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct mt76x02_dev {int /*<<< orphan*/  cal_work; TYPE_3__ cal; TYPE_1__ mt76; } ;
struct ieee80211_channel {int band; int center_freq; int hw_value; } ;
struct cfg80211_chan_def {int center_freq1; int /*<<< orphan*/  width; struct ieee80211_channel* chan; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int BIT (int) ; 
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  MCU_CAL_R ; 
 int /*<<< orphan*/  MCU_CAL_RC ; 
 int /*<<< orphan*/  MCU_CAL_RXDCOC ; 
 scalar_t__ MT76XX_REV_E3 ; 
 int /*<<< orphan*/  MT76_SCANNING ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_CALIBRATE_INTERVAL ; 
 int /*<<< orphan*/  MT_EE_BT_RCAL_RESULT ; 
 int /*<<< orphan*/  MT_EXT_CCA_CFG ; 
 int MT_EXT_CCA_CFG_CCA0 ; 
 int MT_EXT_CCA_CFG_CCA1 ; 
 int MT_EXT_CCA_CFG_CCA2 ; 
 int MT_EXT_CCA_CFG_CCA3 ; 
 int MT_EXT_CCA_CFG_CCA_MASK ; 
 int /*<<< orphan*/  MT_TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_1 ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_1_TEMP_COMP ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_2 ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_2_TEMP_COMP ; 
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_80 128 
 int /*<<< orphan*/  RXO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_hw (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_init_agc_gain (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_mcu_calibrate (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_phy_set_band (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x02_phy_set_bw (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x2_configure_tx_delay (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x2_mcu_init_gain (struct mt76x02_dev*,int,int /*<<< orphan*/ ,int) ; 
 int mt76x2_mcu_set_channel (struct mt76x02_dev*,int,int,int,int) ; 
 int /*<<< orphan*/  mt76x2_phy_channel_calibrate (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_phy_set_antenna (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_phy_set_txpower (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_phy_set_txpower_regs (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_read_rx_gain (struct mt76x02_dev*) ; 
 scalar_t__ mt76x2_tssi_enabled (struct mt76x02_dev*) ; 
 scalar_t__ mt76xx_rev (struct mt76x02_dev*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt76x2_phy_set_channel(struct mt76x02_dev *dev,
			   struct cfg80211_chan_def *chandef)
{
	struct ieee80211_channel *chan = chandef->chan;
	bool scan = test_bit(MT76_SCANNING, &dev->mt76.state);
	enum nl80211_band band = chan->band;
	u8 channel;

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
	int ch_group_index;
	u8 bw, bw_index;
	int freq, freq1;
	int ret;

	dev->cal.channel_cal_done = false;
	freq = chandef->chan->center_freq;
	freq1 = chandef->center_freq1;
	channel = chan->hw_value;

	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_40:
		bw = 1;
		if (freq1 > freq) {
			bw_index = 1;
			ch_group_index = 0;
		} else {
			bw_index = 3;
			ch_group_index = 1;
		}
		channel += 2 - ch_group_index * 4;
		break;
	case NL80211_CHAN_WIDTH_80:
		ch_group_index = (freq - freq1 + 30) / 20;
		if (WARN_ON(ch_group_index < 0 || ch_group_index > 3))
			ch_group_index = 0;
		bw = 2;
		bw_index = ch_group_index;
		channel += 6 - ch_group_index * 4;
		break;
	default:
		bw = 0;
		bw_index = 0;
		ch_group_index = 0;
		break;
	}

	mt76x2_read_rx_gain(dev);
	mt76x2_phy_set_txpower_regs(dev, band);
	mt76x2_configure_tx_delay(dev, band, bw);
	mt76x2_phy_set_txpower(dev);

	mt76x02_phy_set_band(dev, chan->band, ch_group_index & 1);
	mt76x02_phy_set_bw(dev, chandef->width, ch_group_index);

	mt76_rmw(dev, MT_EXT_CCA_CFG,
		 (MT_EXT_CCA_CFG_CCA0 |
		  MT_EXT_CCA_CFG_CCA1 |
		  MT_EXT_CCA_CFG_CCA2 |
		  MT_EXT_CCA_CFG_CCA3 |
		  MT_EXT_CCA_CFG_CCA_MASK),
		 ext_cca_chan[ch_group_index]);

	ret = mt76x2_mcu_set_channel(dev, channel, bw, bw_index, scan);
	if (ret)
		return ret;

	mt76x2_mcu_init_gain(dev, channel, dev->cal.rx.mcu_gain, true);

	mt76x2_phy_set_antenna(dev);

	/* Enable LDPC Rx */
	if (mt76xx_rev(dev) >= MT76XX_REV_E3)
		mt76_set(dev, MT_BBP(RXO, 13), BIT(10));

	if (!dev->cal.init_cal_done) {
		u8 val = mt76x02_eeprom_get(dev, MT_EE_BT_RCAL_RESULT);

		if (val != 0xff)
			mt76x02_mcu_calibrate(dev, MCU_CAL_R, 0);
	}

	mt76x02_mcu_calibrate(dev, MCU_CAL_RXDCOC, channel);

	/* Rx LPF calibration */
	if (!dev->cal.init_cal_done)
		mt76x02_mcu_calibrate(dev, MCU_CAL_RC, 0);

	dev->cal.init_cal_done = true;

	mt76_wr(dev, MT_BBP(AGC, 61), 0xFF64A4E2);
	mt76_wr(dev, MT_BBP(AGC, 7), 0x08081010);
	mt76_wr(dev, MT_BBP(AGC, 11), 0x00000404);
	mt76_wr(dev, MT_BBP(AGC, 2), 0x00007070);
	mt76_wr(dev, MT_TXOP_CTRL_CFG, 0x04101B3F);

	if (scan)
		return 0;

	mt76x2_phy_channel_calibrate(dev, true);
	mt76x02_init_agc_gain(dev);

	/* init default values for temp compensation */
	if (mt76x2_tssi_enabled(dev)) {
		mt76_rmw_field(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP,
			       0x38);
		mt76_rmw_field(dev, MT_TX_ALC_CFG_2, MT_TX_ALC_CFG_2_TEMP_COMP,
			       0x38);
	}

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);

	return 0;
}