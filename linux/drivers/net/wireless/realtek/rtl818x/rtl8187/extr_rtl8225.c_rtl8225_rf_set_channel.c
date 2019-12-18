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
struct rtl8187_priv {TYPE_3__* rf; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct ieee80211_conf {TYPE_2__ chandef; } ;
struct TYPE_6__ {scalar_t__ init; } ;
struct TYPE_4__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/ * rtl8225_chan ; 
 scalar_t__ rtl8225_rf_init ; 
 int /*<<< orphan*/  rtl8225_rf_set_tx_power (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8225_write (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8225z2_b_rf_set_tx_power (struct ieee80211_hw*,int) ; 
 scalar_t__ rtl8225z2_rf_init ; 
 int /*<<< orphan*/  rtl8225z2_rf_set_tx_power (struct ieee80211_hw*,int) ; 

__attribute__((used)) static void rtl8225_rf_set_channel(struct ieee80211_hw *dev,
				   struct ieee80211_conf *conf)
{
	struct rtl8187_priv *priv = dev->priv;
	int chan =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);

	if (priv->rf->init == rtl8225_rf_init)
		rtl8225_rf_set_tx_power(dev, chan);
	else if (priv->rf->init == rtl8225z2_rf_init)
		rtl8225z2_rf_set_tx_power(dev, chan);
	else
		rtl8225z2_b_rf_set_tx_power(dev, chan);

	rtl8225_write(dev, 0x7, rtl8225_chan[chan - 1]);
	msleep(10);
}