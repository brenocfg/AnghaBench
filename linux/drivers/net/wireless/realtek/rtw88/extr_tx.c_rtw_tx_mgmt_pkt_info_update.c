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
struct sk_buff {int dummy; } ;
struct rtw_tx_pkt_info {int use_rate; int rate_id; int dis_rate_fallback; } ;
struct rtw_dev {int dummy; } ;
struct ieee80211_tx_control {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void rtw_tx_mgmt_pkt_info_update(struct rtw_dev *rtwdev,
					struct rtw_tx_pkt_info *pkt_info,
					struct ieee80211_tx_control *control,
					struct sk_buff *skb)
{
	pkt_info->use_rate = true;
	pkt_info->rate_id = 6;
	pkt_info->dis_rate_fallback = true;
}