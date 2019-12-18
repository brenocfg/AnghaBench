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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  bcn_rx_inperiod; } ;
struct TYPE_4__ {scalar_t__ opmode; scalar_t__ link_state; int /*<<< orphan*/  bssid; } ;
struct rtl_priv {TYPE_1__ link_info; TYPE_2__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 scalar_t__ FCS_LEN ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_beacon_statistic(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;

	if (rtlpriv->mac80211.opmode != NL80211_IFTYPE_STATION)
		return;

	if (rtlpriv->mac80211.link_state < MAC80211_LINKED)
		return;

	/* check if this really is a beacon */
	if (!ieee80211_is_beacon(hdr->frame_control) &&
	    !ieee80211_is_probe_resp(hdr->frame_control))
		return;

	/* min. beacon length + FCS_LEN */
	if (skb->len <= 40 + FCS_LEN)
		return;

	/* and only beacons from the associated BSSID, please */
	if (!ether_addr_equal(hdr->addr3, rtlpriv->mac80211.bssid))
		return;

	rtlpriv->link_info.bcn_rx_inperiod++;
}