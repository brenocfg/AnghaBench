#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int avg_rssi_all; int low_gain; int agc_gain_adjust; scalar_t__* agc_gain_init; scalar_t__* agc_gain_cur; } ;
struct mt76x02_dev {TYPE_1__ cal; int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_RX_STAT_1 ; 
 int mt76_get_min_avg_rssi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int mt76x02_get_low_rssi_gain_thresh (struct mt76x02_dev*) ; 
 int mt76x02_get_rssi_gain_thresh (struct mt76x02_dev*) ; 
 scalar_t__ mt76x02_phy_adjust_vga_gain (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x0_phy_set_gain_val (struct mt76x02_dev*) ; 

__attribute__((used)) static void
mt76x0_phy_update_channel_gain(struct mt76x02_dev *dev)
{
	bool gain_change;
	u8 gain_delta;
	int low_gain;

	dev->cal.avg_rssi_all = mt76_get_min_avg_rssi(&dev->mt76);
	if (!dev->cal.avg_rssi_all)
		dev->cal.avg_rssi_all = -75;

	low_gain = (dev->cal.avg_rssi_all > mt76x02_get_rssi_gain_thresh(dev)) +
		(dev->cal.avg_rssi_all > mt76x02_get_low_rssi_gain_thresh(dev));

	gain_change = dev->cal.low_gain < 0 ||
		      (dev->cal.low_gain & 2) ^ (low_gain & 2);
	dev->cal.low_gain = low_gain;

	if (!gain_change) {
		if (mt76x02_phy_adjust_vga_gain(dev))
			mt76x0_phy_set_gain_val(dev);
		return;
	}

	dev->cal.agc_gain_adjust = (low_gain == 2) ? 0 : 10;
	gain_delta = (low_gain == 2) ? 10 : 0;

	dev->cal.agc_gain_cur[0] = dev->cal.agc_gain_init[0] - gain_delta;
	mt76x0_phy_set_gain_val(dev);

	/* clear false CCA counters */
	mt76_rr(dev, MT_RX_STAT_1);
}