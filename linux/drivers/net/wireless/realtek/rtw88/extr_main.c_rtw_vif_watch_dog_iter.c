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
typedef  int /*<<< orphan*/  u8 ;
struct rtw_watch_dog_iter_data {int active; struct rtw_vif* rtwvif; int /*<<< orphan*/  assoc_cnt; } ;
struct TYPE_4__ {scalar_t__ tx_cnt; scalar_t__ rx_cnt; scalar_t__ rx_unicast; scalar_t__ tx_unicast; } ;
struct rtw_vif {TYPE_2__ stats; } ;
struct TYPE_3__ {scalar_t__ assoc; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; scalar_t__ drv_priv; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ RTW_LPS_THRESHOLD ; 

__attribute__((used)) static void rtw_vif_watch_dog_iter(void *data, u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct rtw_watch_dog_iter_data *iter_data = data;
	struct rtw_vif *rtwvif = (struct rtw_vif *)vif->drv_priv;

	if (vif->type == NL80211_IFTYPE_STATION) {
		if (vif->bss_conf.assoc) {
			iter_data->assoc_cnt++;
			iter_data->rtwvif = rtwvif;
		}
		if (rtwvif->stats.tx_cnt > RTW_LPS_THRESHOLD ||
		    rtwvif->stats.rx_cnt > RTW_LPS_THRESHOLD)
			iter_data->active = true;
	} else {
		/* only STATION mode can enter lps */
		iter_data->active = true;
	}

	rtwvif->stats.tx_unicast = 0;
	rtwvif->stats.rx_unicast = 0;
	rtwvif->stats.tx_cnt = 0;
	rtwvif->stats.rx_cnt = 0;
}