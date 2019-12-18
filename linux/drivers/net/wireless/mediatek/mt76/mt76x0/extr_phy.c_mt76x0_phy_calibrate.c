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
struct TYPE_3__ {struct ieee80211_channel* chan; } ;
struct TYPE_4__ {TYPE_1__ chandef; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;
struct ieee80211_channel {scalar_t__ band; int hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBI ; 
 int /*<<< orphan*/  MCU_CAL_FULL ; 
 int /*<<< orphan*/  MCU_CAL_LC ; 
 int /*<<< orphan*/  MCU_CAL_R ; 
 int /*<<< orphan*/  MCU_CAL_RXDCOC ; 
 int /*<<< orphan*/  MCU_CAL_VCO ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_ENABLE_RX ; 
 int MT_MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_0 ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ is_mt7630 (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_mcu_calibrate (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_phy_tssi_dc_calibrate (struct mt76x02_dev*) ; 
 scalar_t__ mt76x0_tssi_enabled (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void mt76x0_phy_calibrate(struct mt76x02_dev *dev, bool power_on)
{
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	int is_5ghz = (chan->band == NL80211_BAND_5GHZ) ? 1 : 0;
	u32 val, tx_alc, reg_val;

	if (is_mt7630(dev))
		return;

	if (power_on) {
		mt76x02_mcu_calibrate(dev, MCU_CAL_R, 0);
		mt76x02_mcu_calibrate(dev, MCU_CAL_VCO, chan->hw_value);
		usleep_range(10, 20);

		if (mt76x0_tssi_enabled(dev)) {
			mt76_wr(dev, MT_MAC_SYS_CTRL,
				MT_MAC_SYS_CTRL_ENABLE_RX);
			mt76x0_phy_tssi_dc_calibrate(dev);
			mt76_wr(dev, MT_MAC_SYS_CTRL,
				MT_MAC_SYS_CTRL_ENABLE_TX |
				MT_MAC_SYS_CTRL_ENABLE_RX);
		}
	}

	tx_alc = mt76_rr(dev, MT_TX_ALC_CFG_0);
	mt76_wr(dev, MT_TX_ALC_CFG_0, 0);
	usleep_range(500, 700);

	reg_val = mt76_rr(dev, MT_BBP(IBI, 9));
	mt76_wr(dev, MT_BBP(IBI, 9), 0xffffff7e);

	if (is_5ghz) {
		if (chan->hw_value < 100)
			val = 0x701;
		else if (chan->hw_value < 140)
			val = 0x801;
		else
			val = 0x901;
	} else {
		val = 0x600;
	}

	mt76x02_mcu_calibrate(dev, MCU_CAL_FULL, val);
	msleep(350);
	mt76x02_mcu_calibrate(dev, MCU_CAL_LC, is_5ghz);
	usleep_range(15000, 20000);

	mt76_wr(dev, MT_BBP(IBI, 9), reg_val);
	mt76_wr(dev, MT_TX_ALC_CFG_0, tx_alc);
	mt76x02_mcu_calibrate(dev, MCU_CAL_RXDCOC, 1);
}