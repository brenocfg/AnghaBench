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
struct TYPE_3__ {struct ieee80211_channel* chan; } ;
struct TYPE_4__ {TYPE_1__ chandef; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;
struct ieee80211_channel {scalar_t__ band; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CORE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mt76x0_phy_tssi_adc_calibrate(struct mt76x02_dev *dev, s16 *ltssi,
			      u8 *info)
{
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	u32 val;

	val = (chan->band == NL80211_BAND_5GHZ) ? 0x80055 : 0x80050;
	mt76_wr(dev, MT_BBP(CORE, 34), val);

	if (!mt76_poll_msec(dev, MT_BBP(CORE, 34), BIT(4), 0, 200)) {
		mt76_clear(dev, MT_BBP(CORE, 34), BIT(4));
		return -ETIMEDOUT;
	}

	*ltssi = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;
	if (chan->band == NL80211_BAND_5GHZ)
		*ltssi += 128;

	/* set packet info#1 mode */
	mt76_wr(dev, MT_BBP(CORE, 34), 0x80041);
	info[0] = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;

	/* set packet info#2 mode */
	mt76_wr(dev, MT_BBP(CORE, 34), 0x80042);
	info[1] = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;

	/* set packet info#3 mode */
	mt76_wr(dev, MT_BBP(CORE, 34), 0x80043);
	info[2] = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;

	return 0;
}