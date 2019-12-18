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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct rsi_common {int hw_data_qs_blocked; int min_rate; int wow_flags; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
typedef  enum opmode { ____Placeholder_opmode } opmode ;

/* Variables and functions */
 int RSI_OPMODE_STA ; 
 int RSI_WOW_ENABLED ; 
 int /*<<< orphan*/  STA_CONNECTED ; 
 int /*<<< orphan*/  STA_DISCONNECTED ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int /*<<< orphan*/  rsi_hal_send_sta_notify_frame (struct rsi_common*,int,int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__,int,int,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  rsi_send_auto_rate_request (struct rsi_common*,struct ieee80211_sta*,int,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  rsi_send_block_unblock_frame (struct rsi_common*,int) ; 

void rsi_inform_bss_status(struct rsi_common *common,
			   enum opmode opmode,
			   u8 status,
			   const u8 *addr,
			   u8 qos_enable,
			   u16 aid,
			   struct ieee80211_sta *sta,
			   u16 sta_id,
			   u16 assoc_cap,
			   struct ieee80211_vif *vif)
{
	if (status) {
		if (opmode == RSI_OPMODE_STA)
			common->hw_data_qs_blocked = true;
		rsi_hal_send_sta_notify_frame(common,
					      opmode,
					      STA_CONNECTED,
					      addr,
					      qos_enable,
					      aid, sta_id,
					      vif);
		if (common->min_rate == 0xffff)
			rsi_send_auto_rate_request(common, sta, sta_id, vif);
		if (opmode == RSI_OPMODE_STA &&
		    !(assoc_cap & WLAN_CAPABILITY_PRIVACY) &&
		    !rsi_send_block_unblock_frame(common, false))
			common->hw_data_qs_blocked = false;
	} else {
		if (opmode == RSI_OPMODE_STA)
			common->hw_data_qs_blocked = true;

		if (!(common->wow_flags & RSI_WOW_ENABLED))
			rsi_hal_send_sta_notify_frame(common, opmode,
						      STA_DISCONNECTED, addr,
						      qos_enable, aid, sta_id,
						      vif);
		if (opmode == RSI_OPMODE_STA)
			rsi_send_block_unblock_frame(common, true);
	}
}