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
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int NL80211_IFTYPE_P2P_CLIENT ; 
 int NL80211_IFTYPE_STATION ; 

__attribute__((used)) static bool wil_is_safe_switch(enum nl80211_iftype from,
			       enum nl80211_iftype to)
{
	if (from == NL80211_IFTYPE_STATION &&
	    to == NL80211_IFTYPE_P2P_CLIENT)
		return true;

	return false;
}