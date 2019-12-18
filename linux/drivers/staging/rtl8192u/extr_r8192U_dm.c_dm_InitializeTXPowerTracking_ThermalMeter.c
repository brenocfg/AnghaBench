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
struct r8192_priv {int btxpower_tracking; int btxpower_trackingInit; scalar_t__ txpower_count; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ FwRWRF; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void dm_InitializeTXPowerTracking_ThermalMeter(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	/* Tx Power tracking by Thermal Meter requires Firmware R/W 3-wire. This mechanism
	 * can be enabled only when Firmware R/W 3-wire is enabled. Otherwise, frequent r/w
	 * 3-wire by driver causes RF to go into a wrong state.
	 */
	if (priv->ieee80211->FwRWRF)
		priv->btxpower_tracking = true;
	else
		priv->btxpower_tracking = false;
	priv->txpower_count       = 0;
	priv->btxpower_trackingInit = false;
}