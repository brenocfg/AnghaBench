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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  priority; int /*<<< orphan*/  len; scalar_t__ data; } ;
struct rtw_tx_pkt_info {int bmc; int sec_type; int ls; int /*<<< orphan*/  qsel; int /*<<< orphan*/  offset; int /*<<< orphan*/  tx_pkt_size; } ;
struct rtw_sta_info {struct ieee80211_vif* vif; } ;
struct rtw_dev {struct rtw_chip_info* chip; } ;
struct rtw_chip_info {int /*<<< orphan*/  tx_pkt_desc_sz; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_4__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ control; } ;
struct ieee80211_tx_control {TYPE_1__* sta; } ;
struct ieee80211_key_conf {int cipher; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_tx_data_pkt_info_update (struct rtw_dev*,struct rtw_tx_pkt_info*,struct ieee80211_tx_control*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtw_tx_mgmt_pkt_info_update (struct rtw_dev*,struct rtw_tx_pkt_info*,struct ieee80211_tx_control*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtw_tx_report_enable (struct rtw_dev*,struct rtw_tx_pkt_info*) ; 
 int /*<<< orphan*/  rtw_tx_stats (struct rtw_dev*,struct ieee80211_vif*,struct sk_buff*) ; 

void rtw_tx_pkt_info_update(struct rtw_dev *rtwdev,
			    struct rtw_tx_pkt_info *pkt_info,
			    struct ieee80211_tx_control *control,
			    struct sk_buff *skb)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct rtw_sta_info *si;
	struct ieee80211_vif *vif = NULL;
	__le16 fc = hdr->frame_control;
	u8 sec_type = 0;
	bool bmc;

	if (control->sta) {
		si = (struct rtw_sta_info *)control->sta->drv_priv;
		vif = si->vif;
	}

	if (ieee80211_is_mgmt(fc) || ieee80211_is_nullfunc(fc))
		rtw_tx_mgmt_pkt_info_update(rtwdev, pkt_info, control, skb);
	else if (ieee80211_is_data(fc))
		rtw_tx_data_pkt_info_update(rtwdev, pkt_info, control, skb);

	if (info->control.hw_key) {
		struct ieee80211_key_conf *key = info->control.hw_key;

		switch (key->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
		case WLAN_CIPHER_SUITE_TKIP:
			sec_type = 0x01;
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			sec_type = 0x03;
			break;
		default:
			break;
		}
	}

	bmc = is_broadcast_ether_addr(hdr->addr1) ||
	      is_multicast_ether_addr(hdr->addr1);

	if (info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS)
		rtw_tx_report_enable(rtwdev, pkt_info);

	pkt_info->bmc = bmc;
	pkt_info->sec_type = sec_type;
	pkt_info->tx_pkt_size = skb->len;
	pkt_info->offset = chip->tx_pkt_desc_sz;
	pkt_info->qsel = skb->priority;
	pkt_info->ls = true;

	/* maybe merge with tx status ? */
	rtw_tx_stats(rtwdev, vif, skb);
}