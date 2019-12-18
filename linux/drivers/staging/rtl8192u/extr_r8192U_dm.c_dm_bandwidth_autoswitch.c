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
struct r8192_priv {scalar_t__ CurrentChannelBW; scalar_t__ undecorated_smoothed_pwdb; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int bforced_tx20Mhz; scalar_t__ threshold_40Mhzto20Mhz; scalar_t__ threshold_20Mhzto40Mhz; int /*<<< orphan*/  bautoswitch_enable; } ;
struct TYPE_4__ {TYPE_1__ bandwidth_auto_switch; } ;

/* Variables and functions */
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void dm_bandwidth_autoswitch(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20 || !priv->ieee80211->bandwidth_auto_switch.bautoswitch_enable)
		return;
	if (!priv->ieee80211->bandwidth_auto_switch.bforced_tx20Mhz) { /* If send packets in 40 Mhz in 20/40 */
		if (priv->undecorated_smoothed_pwdb <= priv->ieee80211->bandwidth_auto_switch.threshold_40Mhzto20Mhz)
			priv->ieee80211->bandwidth_auto_switch.bforced_tx20Mhz = true;
	} else { /* in force send packets in 20 Mhz in 20/40 */
		if (priv->undecorated_smoothed_pwdb >= priv->ieee80211->bandwidth_auto_switch.threshold_20Mhzto40Mhz)
			priv->ieee80211->bandwidth_auto_switch.bforced_tx20Mhz = false;
	}
}