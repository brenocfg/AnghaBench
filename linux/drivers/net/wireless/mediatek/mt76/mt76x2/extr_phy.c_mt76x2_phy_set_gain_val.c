#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ width; TYPE_2__* chan; } ;
struct TYPE_8__ {TYPE_3__ chandef; } ;
struct TYPE_5__ {scalar_t__ agc_gain_adjust; scalar_t__* agc_gain_cur; } ;
struct mt76x02_dev {TYPE_4__ mt76; TYPE_1__ cal; } ;
struct TYPE_6__ {scalar_t__ band; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int FIELD_PREP (int /*<<< orphan*/ ,scalar_t__) ; 
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP_AGC_GAIN ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_CHAN_WIDTH_40 ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_phy_dfs_adjust_agc (struct mt76x02_dev*) ; 
 scalar_t__ mt76x2_has_ext_lna (struct mt76x02_dev*) ; 

__attribute__((used)) static void
mt76x2_phy_set_gain_val(struct mt76x02_dev *dev)
{
	u32 val;
	u8 gain_val[2];

	gain_val[0] = dev->cal.agc_gain_cur[0] - dev->cal.agc_gain_adjust;
	gain_val[1] = dev->cal.agc_gain_cur[1] - dev->cal.agc_gain_adjust;

	val = 0x1836 << 16;
	if (!mt76x2_has_ext_lna(dev) &&
	    dev->mt76.chandef.width >= NL80211_CHAN_WIDTH_40)
		val = 0x1e42 << 16;

	if (mt76x2_has_ext_lna(dev) &&
	    dev->mt76.chandef.chan->band == NL80211_BAND_2GHZ &&
	    dev->mt76.chandef.width < NL80211_CHAN_WIDTH_40)
		val = 0x0f36 << 16;

	val |= 0xf8;

	mt76_wr(dev, MT_BBP(AGC, 8),
		val | FIELD_PREP(MT_BBP_AGC_GAIN, gain_val[0]));
	mt76_wr(dev, MT_BBP(AGC, 9),
		val | FIELD_PREP(MT_BBP_AGC_GAIN, gain_val[1]));

	if (dev->mt76.chandef.chan->flags & IEEE80211_CHAN_RADAR)
		mt76x02_phy_dfs_adjust_agc(dev);
}