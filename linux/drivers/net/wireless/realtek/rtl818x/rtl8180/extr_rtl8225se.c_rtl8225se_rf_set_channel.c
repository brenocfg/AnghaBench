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
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_conf {TYPE_2__ chandef; } ;
struct TYPE_3__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int rtl8187se_rf_readreg (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8187se_rf_writereg (struct ieee80211_hw*,int,int) ; 
 int* rtl8225se_chan ; 
 int /*<<< orphan*/  rtl8225sez2_rf_set_tx_power (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void rtl8225se_rf_set_channel(struct ieee80211_hw *dev,
				   struct ieee80211_conf *conf)
{
	int chan =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);

	rtl8225sez2_rf_set_tx_power(dev, chan);
	rtl8187se_rf_writereg(dev, 0x7, rtl8225se_chan[chan - 1]);
	if ((rtl8187se_rf_readreg(dev, 0x7) & 0x0F80) !=
		rtl8225se_chan[chan - 1])
		rtl8187se_rf_writereg(dev, 0x7, rtl8225se_chan[chan - 1]);
	usleep_range(10000, 20000);
}