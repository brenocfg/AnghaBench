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
struct TYPE_7__ {TYPE_2__* chan; } ;
struct TYPE_8__ {TYPE_3__ chandef; } ;
struct TYPE_5__ {scalar_t__ agc_gain_adjust; scalar_t__* agc_gain_cur; } ;
struct mt76x02_dev {TYPE_4__ mt76; TYPE_1__ cal; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP_AGC_GAIN ; 
 int /*<<< orphan*/  is_mt7630 (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mt76x02_phy_dfs_adjust_agc (struct mt76x02_dev*) ; 

__attribute__((used)) static void mt76x0_phy_set_gain_val(struct mt76x02_dev *dev)
{
	u8 gain = dev->cal.agc_gain_cur[0] - dev->cal.agc_gain_adjust;

	mt76_rmw_field(dev, MT_BBP(AGC, 8), MT_BBP_AGC_GAIN, gain);

	if ((dev->mt76.chandef.chan->flags & IEEE80211_CHAN_RADAR) &&
	    !is_mt7630(dev))
		mt76x02_phy_dfs_adjust_agc(dev);
}