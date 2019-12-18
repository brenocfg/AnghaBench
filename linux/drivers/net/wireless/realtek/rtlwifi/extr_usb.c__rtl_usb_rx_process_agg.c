#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct rtl_stats {int /*<<< orphan*/  crc; scalar_t__ rx_bufshift; scalar_t__ rx_drvinfo_size; int /*<<< orphan*/  rate; int /*<<< orphan*/  signal; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_rx_inperiod; } ;
struct TYPE_5__ {int /*<<< orphan*/  rxbytesunicast; } ;
struct rtl_priv {TYPE_4__ link_info; TYPE_3__* cfg; TYPE_1__ stats; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  member_0; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  rx_status ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_7__ {TYPE_2__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* query_rx_desc ) (struct ieee80211_hw*,struct rtl_stats*,struct ieee80211_rx_status*,int /*<<< orphan*/ *,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  LED_CTL_RX ; 
 scalar_t__ RTL_RX_DESC_SIZE ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 int /*<<< orphan*/  rtl_beacon_statistic (struct ieee80211_hw*,struct sk_buff*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,struct rtl_stats*,struct ieee80211_rx_status*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl_usb_rx_process_agg(struct ieee80211_hw *hw,
				    struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 *rxdesc = skb->data;
	struct ieee80211_hdr *hdr;
	bool unicast = false;
	__le16 fc;
	struct ieee80211_rx_status rx_status = {0};
	struct rtl_stats stats = {
		.signal = 0,
		.rate = 0,
	};

	skb_pull(skb, RTL_RX_DESC_SIZE);
	rtlpriv->cfg->ops->query_rx_desc(hw, &stats, &rx_status, rxdesc, skb);
	skb_pull(skb, (stats.rx_drvinfo_size + stats.rx_bufshift));
	hdr = (struct ieee80211_hdr *)(skb->data);
	fc = hdr->frame_control;
	if (!stats.crc) {
		memcpy(IEEE80211_SKB_RXCB(skb), &rx_status, sizeof(rx_status));

		if (is_broadcast_ether_addr(hdr->addr1)) {
			/*TODO*/;
		} else if (is_multicast_ether_addr(hdr->addr1)) {
			/*TODO*/
		} else {
			unicast = true;
			rtlpriv->stats.rxbytesunicast +=  skb->len;
		}

		if (ieee80211_is_data(fc)) {
			rtlpriv->cfg->ops->led_control(hw, LED_CTL_RX);

			if (unicast)
				rtlpriv->link_info.num_rx_inperiod++;
		}
		/* static bcn for roaming */
		rtl_beacon_statistic(hw, skb);
	}
}