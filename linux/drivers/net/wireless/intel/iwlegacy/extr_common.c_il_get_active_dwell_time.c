#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct il_priv {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int IL_ACTIVE_DWELL_FACTOR_24GHZ ; 
 int IL_ACTIVE_DWELL_FACTOR_52GHZ ; 
 scalar_t__ IL_ACTIVE_DWELL_TIME_24 ; 
 scalar_t__ IL_ACTIVE_DWELL_TIME_52 ; 
 int NL80211_BAND_5GHZ ; 

u16
il_get_active_dwell_time(struct il_priv *il, enum nl80211_band band,
			 u8 n_probes)
{
	if (band == NL80211_BAND_5GHZ)
		return IL_ACTIVE_DWELL_TIME_52 +
		    IL_ACTIVE_DWELL_FACTOR_52GHZ * (n_probes + 1);
	else
		return IL_ACTIVE_DWELL_TIME_24 +
		    IL_ACTIVE_DWELL_FACTOR_24GHZ * (n_probes + 1);
}