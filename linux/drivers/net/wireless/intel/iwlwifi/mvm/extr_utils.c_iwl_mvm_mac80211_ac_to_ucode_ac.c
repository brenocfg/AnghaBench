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
typedef  int /*<<< orphan*/  const u8 ;
typedef  enum ieee80211_ac_numbers { ____Placeholder_ieee80211_ac_numbers } ieee80211_ac_numbers ;

/* Variables and functions */
#define  AC_BE 131 
#define  AC_BK 130 
#define  AC_VI 129 
#define  AC_VO 128 

u8 iwl_mvm_mac80211_ac_to_ucode_ac(enum ieee80211_ac_numbers ac)
{
	static const u8 mac80211_ac_to_ucode_ac[] = {
		AC_VO,
		AC_VI,
		AC_BE,
		AC_BK
	};

	return mac80211_ac_to_ucode_ac[ac];
}