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
typedef  int u16 ;
struct il_priv {TYPE_2__* vif; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_3__ {int beacon_int; } ;
struct TYPE_4__ {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int IL_CHANNEL_TUNE_TIME ; 
 int IL_PASSIVE_DWELL_BASE ; 
 int IL_PASSIVE_DWELL_TIME_24 ; 
 int IL_PASSIVE_DWELL_TIME_52 ; 
 int NL80211_BAND_2GHZ ; 
 scalar_t__ il_is_any_associated (struct il_priv*) ; 
 int min (int,int) ; 

u16
il_get_passive_dwell_time(struct il_priv *il, enum nl80211_band band,
			  struct ieee80211_vif *vif)
{
	u16 value;

	u16 passive =
	    (band ==
	     NL80211_BAND_2GHZ) ? IL_PASSIVE_DWELL_BASE +
	    IL_PASSIVE_DWELL_TIME_24 : IL_PASSIVE_DWELL_BASE +
	    IL_PASSIVE_DWELL_TIME_52;

	if (il_is_any_associated(il)) {
		/*
		 * If we're associated, we clamp the maximum passive
		 * dwell time to be 98% of the smallest beacon interval
		 * (minus 2 * channel tune time)
		 */
		value = il->vif ? il->vif->bss_conf.beacon_int : 0;
		if (value > IL_PASSIVE_DWELL_BASE || !value)
			value = IL_PASSIVE_DWELL_BASE;
		value = (value * 98) / 100 - IL_CHANNEL_TUNE_TIME * 2;
		passive = min(value, passive);
	}

	return passive;
}