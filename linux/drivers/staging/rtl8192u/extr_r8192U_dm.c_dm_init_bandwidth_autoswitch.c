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
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int bforced_tx20Mhz; int bautoswitch_enable; int /*<<< orphan*/  threshold_40Mhzto20Mhz; int /*<<< orphan*/  threshold_20Mhzto40Mhz; } ;
struct TYPE_3__ {TYPE_2__ bandwidth_auto_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BW_AUTO_SWITCH_HIGH_LOW ; 
 int /*<<< orphan*/  BW_AUTO_SWITCH_LOW_HIGH ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void dm_init_bandwidth_autoswitch(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	priv->ieee80211->bandwidth_auto_switch.threshold_20Mhzto40Mhz = BW_AUTO_SWITCH_LOW_HIGH;
	priv->ieee80211->bandwidth_auto_switch.threshold_40Mhzto20Mhz = BW_AUTO_SWITCH_HIGH_LOW;
	priv->ieee80211->bandwidth_auto_switch.bforced_tx20Mhz = false;
	priv->ieee80211->bandwidth_auto_switch.bautoswitch_enable = false;

}