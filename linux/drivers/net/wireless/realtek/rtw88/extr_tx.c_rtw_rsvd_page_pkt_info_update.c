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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct rtw_tx_pkt_info {int use_rate; int rate_id; int dis_rate_fallback; int bmc; int ls; int /*<<< orphan*/  qsel; int /*<<< orphan*/  offset; int /*<<< orphan*/  tx_pkt_size; } ;
struct rtw_dev {struct rtw_chip_info* chip; } ;
struct rtw_chip_info {int /*<<< orphan*/  tx_pkt_desc_sz; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_DESC_QSEL_MGMT ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

void rtw_rsvd_page_pkt_info_update(struct rtw_dev *rtwdev,
				   struct rtw_tx_pkt_info *pkt_info,
				   struct sk_buff *skb)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	bool bmc;

	bmc = is_broadcast_ether_addr(hdr->addr1) ||
	      is_multicast_ether_addr(hdr->addr1);
	pkt_info->use_rate = true;
	pkt_info->rate_id = 6;
	pkt_info->dis_rate_fallback = true;
	pkt_info->bmc = bmc;
	pkt_info->tx_pkt_size = skb->len;
	pkt_info->offset = chip->tx_pkt_desc_sz;
	pkt_info->qsel = TX_DESC_QSEL_MGMT;
	pkt_info->ls = true;
}