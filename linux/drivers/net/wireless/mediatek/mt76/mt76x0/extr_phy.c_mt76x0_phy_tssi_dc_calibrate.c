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
typedef  int u32 ;
struct TYPE_6__ {int tssi_dc; } ;
struct TYPE_4__ {struct ieee80211_channel* chan; } ;
struct TYPE_5__ {TYPE_1__ chandef; } ;
struct mt76x02_dev {TYPE_3__ cal; TYPE_2__ mt76; } ;
struct ieee80211_channel {scalar_t__ band; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CORE ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_RF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_RF_BYPASS_0 ; 
 int /*<<< orphan*/  MT_RF_SETTING_0 ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  TXBE ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_rf_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_rf_rmw (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mt76x0_phy_tssi_dc_calibrate(struct mt76x02_dev *dev)
{
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	u32 val;

	if (chan->band == NL80211_BAND_5GHZ)
		mt76x0_rf_clear(dev, MT_RF(0, 67), 0xf);

	/* bypass ADDA control */
	mt76_wr(dev, MT_RF_SETTING_0, 0x60002237);
	mt76_wr(dev, MT_RF_BYPASS_0, 0xffffffff);

	/* bbp sw reset */
	mt76_set(dev, MT_BBP(CORE, 4), BIT(0));
	usleep_range(500, 1000);
	mt76_clear(dev, MT_BBP(CORE, 4), BIT(0));

	val = (chan->band == NL80211_BAND_5GHZ) ? 0x80055 : 0x80050;
	mt76_wr(dev, MT_BBP(CORE, 34), val);

	/* enable TX with DAC0 input */
	mt76_wr(dev, MT_BBP(TXBE, 6), BIT(31));

	mt76_poll_msec(dev, MT_BBP(CORE, 34), BIT(4), 0, 200);
	dev->cal.tssi_dc = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;

	/* stop bypass ADDA */
	mt76_wr(dev, MT_RF_BYPASS_0, 0);
	/* stop TX */
	mt76_wr(dev, MT_BBP(TXBE, 6), 0);
	/* bbp sw reset */
	mt76_set(dev, MT_BBP(CORE, 4), BIT(0));
	usleep_range(500, 1000);
	mt76_clear(dev, MT_BBP(CORE, 4), BIT(0));

	if (chan->band == NL80211_BAND_5GHZ)
		mt76x0_rf_rmw(dev, MT_RF(0, 67), 0xf, 0x4);
}