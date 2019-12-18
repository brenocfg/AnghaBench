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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int tssi_cal_done; } ;
struct TYPE_5__ {struct ieee80211_channel* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct mt76x02_dev {TYPE_1__ cal; TYPE_3__ mt76; } ;
struct ieee80211_channel {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MCU_CAL_TSSI ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ mt76x02_ext_pa_enabled (struct mt76x02_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mt76x02_mcu_calibrate (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76x2_channel_silent (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_tssi_enabled (struct mt76x02_dev*) ; 

__attribute__((used)) static bool
mt76x2_phy_tssi_init_cal(struct mt76x02_dev *dev)
{
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	u32 flag = 0;

	if (!mt76x2_tssi_enabled(dev))
		return false;

	if (mt76x2_channel_silent(dev))
		return false;

	if (chan->band == NL80211_BAND_5GHZ)
		flag |= BIT(0);

	if (mt76x02_ext_pa_enabled(dev, chan->band))
		flag |= BIT(8);

	mt76x02_mcu_calibrate(dev, MCU_CAL_TSSI, flag);
	dev->cal.tssi_cal_done = true;
	return true;
}