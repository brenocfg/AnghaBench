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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_uap_bss_param {int /*<<< orphan*/  power_constraint; } ;
struct mwifiex_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail_len; int /*<<< orphan*/  tail; } ;
struct cfg80211_ap_settings {TYPE_1__ beacon; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_TPC_REQUEST ; 
 int /*<<< orphan*/ * cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mwifiex_set_tpc_params(struct mwifiex_private *priv,
			    struct mwifiex_uap_bss_param *bss_cfg,
			    struct cfg80211_ap_settings *params)
{
	const u8 *tpc_ie;

	tpc_ie = cfg80211_find_ie(WLAN_EID_TPC_REQUEST, params->beacon.tail,
				  params->beacon.tail_len);
	if (tpc_ie)
		bss_cfg->power_constraint = *(tpc_ie + 2);
	else
		bss_cfg->power_constraint = 0;
}