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
struct TYPE_4__ {scalar_t__ rx_cnt; int /*<<< orphan*/  rx_unicast; } ;
struct rtw_vif {TYPE_2__ stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_cnt; int /*<<< orphan*/  rx_unicast; } ;
struct rtw_dev {TYPE_1__ stats; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 scalar_t__ RTW_LPS_THRESHOLD ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_leave_lps_irqsafe (struct rtw_dev*,struct rtw_vif*) ; 

void rtw_rx_stats(struct rtw_dev *rtwdev, struct ieee80211_vif *vif,
		  struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr;
	struct rtw_vif *rtwvif;

	hdr = (struct ieee80211_hdr *)skb->data;

	if (!ieee80211_is_data(hdr->frame_control))
		return;

	if (!is_broadcast_ether_addr(hdr->addr1) &&
	    !is_multicast_ether_addr(hdr->addr1)) {
		rtwdev->stats.rx_unicast += skb->len;
		rtwdev->stats.rx_cnt++;
		if (vif) {
			rtwvif = (struct rtw_vif *)vif->drv_priv;
			rtwvif->stats.rx_unicast += skb->len;
			rtwvif->stats.rx_cnt++;
			if (rtwvif->stats.rx_cnt > RTW_LPS_THRESHOLD)
				rtw_leave_lps_irqsafe(rtwdev, rtwvif);
		}
	}
}