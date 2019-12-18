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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct cfg80211_beacon_data {int /*<<< orphan*/  tail_len; int /*<<< orphan*/  tail; } ;
typedef  enum state_11d_t { ____Placeholder_state_11d_t } state_11d_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11D_I ; 
 int ENABLE_11D ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_SNMP_MIB ; 
 int /*<<< orphan*/  WLAN_EID_COUNTRY ; 
 int /*<<< orphan*/ * cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

void mwifiex_config_uap_11d(struct mwifiex_private *priv,
			    struct cfg80211_beacon_data *beacon_data)
{
	enum state_11d_t state_11d;
	const u8 *country_ie;

	country_ie = cfg80211_find_ie(WLAN_EID_COUNTRY, beacon_data->tail,
				      beacon_data->tail_len);
	if (country_ie) {
		/* Send cmd to FW to enable 11D function */
		state_11d = ENABLE_11D;
		if (mwifiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
				     HostCmd_ACT_GEN_SET, DOT11D_I,
				     &state_11d, true)) {
			mwifiex_dbg(priv->adapter, ERROR,
				    "11D: failed to enable 11D\n");
		}
	}
}