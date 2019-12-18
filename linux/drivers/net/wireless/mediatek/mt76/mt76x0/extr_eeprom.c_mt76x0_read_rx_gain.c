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
typedef  int u16 ;
struct mt76x02_rx_freq_cal {int* rssi_offset; int /*<<< orphan*/  lna_gain; } ;
struct TYPE_4__ {struct mt76x02_rx_freq_cal rx; } ;
struct TYPE_5__ {struct ieee80211_channel* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct mt76x02_dev {TYPE_1__ cal; TYPE_3__ mt76; } ;
struct ieee80211_channel {int /*<<< orphan*/  band; } ;
typedef  int s8 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  mt76x02_get_lna_gain (struct mt76x02_dev*,int*,int*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  mt76x02_get_rx_gain (struct mt76x02_dev*,int /*<<< orphan*/ ,int*,int*,int*) ; 

void mt76x0_read_rx_gain(struct mt76x02_dev *dev)
{
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	struct mt76x02_rx_freq_cal *caldata = &dev->cal.rx;
	s8 val, lna_5g[3], lna_2g;
	u16 rssi_offset;
	int i;

	mt76x02_get_rx_gain(dev, chan->band, &rssi_offset, &lna_2g, lna_5g);
	caldata->lna_gain = mt76x02_get_lna_gain(dev, &lna_2g, lna_5g, chan);

	for (i = 0; i < ARRAY_SIZE(caldata->rssi_offset); i++) {
		val = rssi_offset >> (8 * i);
		if (val < -10 || val > 10)
			val = 0;

		caldata->rssi_offset[i] = val;
	}
}