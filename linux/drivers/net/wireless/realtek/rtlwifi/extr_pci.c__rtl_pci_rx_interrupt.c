#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ end; scalar_t__ tail; scalar_t__ len; scalar_t__ data; scalar_t__ cb; } ;
struct rtl_stats {scalar_t__ packet_report_type; int /*<<< orphan*/  hwerror; int /*<<< orphan*/  crc; scalar_t__ rx_bufshift; scalar_t__ rx_drvinfo_size; int /*<<< orphan*/  rate; int /*<<< orphan*/  signal; } ;
struct rtl_rx_desc {int dummy; } ;
struct rtl_rx_buffer_desc {int dummy; } ;
struct TYPE_11__ {int num_rx_inperiod; int num_tx_inperiod; } ;
struct TYPE_10__ {scalar_t__ current_bandtype; } ;
struct TYPE_9__ {scalar_t__ opmode; } ;
struct TYPE_8__ {int /*<<< orphan*/  rxbytesunicast; } ;
struct rtl_priv {TYPE_7__* cfg; scalar_t__ use_new_trx_flow; TYPE_4__ link_info; TYPE_3__ rtlhal; TYPE_2__ mac80211; TYPE_1__ stats; } ;
struct rtl_pci {unsigned int rxringcount; TYPE_5__* rx_ring; int /*<<< orphan*/  rxbuffersize; int /*<<< orphan*/  pdev; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  member_0; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;
typedef  int /*<<< orphan*/  rx_status ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_14__ {TYPE_6__* ops; } ;
struct TYPE_13__ {unsigned int (* rx_desc_buff_remained_cnt ) (struct ieee80211_hw*,size_t) ;scalar_t__ (* get_desc ) (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_desc ) (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ,size_t*) ;int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* rx_check_dma_ok ) (struct ieee80211_hw*,size_t*,size_t) ;int /*<<< orphan*/  (* query_rx_desc ) (struct ieee80211_hw*,struct rtl_stats*,struct ieee80211_rx_status*,size_t*,struct sk_buff*) ;} ;
struct TYPE_12__ {size_t idx; int next_rx_rp; struct rtl_rx_desc* desc; struct rtl_rx_buffer_desc* buffer_desc; struct sk_buff** rx_buf; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ C2H_PACKET ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 scalar_t__ FCS_LEN ; 
 int /*<<< orphan*/  HW_DESC_OWN ; 
 int /*<<< orphan*/  HW_DESC_RXERO ; 
 int /*<<< orphan*/  HW_DESC_RXPKT_LEN ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  LED_CTL_RX ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RTL_PCI_MAX_RX_COUNT ; 
 int RTL_PCI_RX_MPDU_QUEUE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _rtl_pci_init_one_rxdesc (struct ieee80211_hw*,struct sk_buff*,size_t*,int,int) ; 
 int /*<<< orphan*/  _rtl_pci_rx_to_mac80211 (struct ieee80211_hw*,struct sk_buff*,struct ieee80211_rx_status) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_beacon_statistic (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtl_c2hcmd_enqueue (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtl_collect_scan_list (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 
 struct ieee80211_hdr* rtl_get_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl_is_special_data (struct ieee80211_hw*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  rtl_lps_leave (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_p2p_info (struct ieee80211_hw*,void*,scalar_t__) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_recognize_peer (struct ieee80211_hw*,void*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_swlps_beacon (struct ieee80211_hw*,void*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 unsigned int stub1 (struct ieee80211_hw*,size_t) ; 
 scalar_t__ stub2 (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,struct rtl_stats*,struct ieee80211_rx_status*,size_t*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*,size_t*,size_t) ; 
 scalar_t__ stub5 (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void _rtl_pci_rx_interrupt(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	int rxring_idx = RTL_PCI_RX_MPDU_QUEUE;
	struct ieee80211_rx_status rx_status = { 0 };
	unsigned int count = rtlpci->rxringcount;
	u8 own;
	u8 tmp_one;
	bool unicast = false;
	u8 hw_queue = 0;
	unsigned int rx_remained_cnt = 0;
	struct rtl_stats stats = {
		.signal = 0,
		.rate = 0,
	};

	/*RX NORMAL PKT */
	while (count--) {
		struct ieee80211_hdr *hdr;
		__le16 fc;
		u16 len;
		/*rx buffer descriptor */
		struct rtl_rx_buffer_desc *buffer_desc = NULL;
		/*if use new trx flow, it means wifi info */
		struct rtl_rx_desc *pdesc = NULL;
		/*rx pkt */
		struct sk_buff *skb = rtlpci->rx_ring[rxring_idx].rx_buf[
				      rtlpci->rx_ring[rxring_idx].idx];
		struct sk_buff *new_skb;

		if (rtlpriv->use_new_trx_flow) {
			if (rx_remained_cnt == 0)
				rx_remained_cnt =
				rtlpriv->cfg->ops->rx_desc_buff_remained_cnt(hw,
								      hw_queue);
			if (rx_remained_cnt == 0)
				return;
			buffer_desc = &rtlpci->rx_ring[rxring_idx].buffer_desc[
				rtlpci->rx_ring[rxring_idx].idx];
			pdesc = (struct rtl_rx_desc *)skb->data;
		} else {	/* rx descriptor */
			pdesc = &rtlpci->rx_ring[rxring_idx].desc[
				rtlpci->rx_ring[rxring_idx].idx];

			own = (u8)rtlpriv->cfg->ops->get_desc(hw, (u8 *)pdesc,
							      false,
							      HW_DESC_OWN);
			if (own) /* wait data to be filled by hardware */
				return;
		}

		/* Reaching this point means: data is filled already
		 * AAAAAAttention !!!
		 * We can NOT access 'skb' before 'pci_unmap_single'
		 */
		pci_unmap_single(rtlpci->pdev, *((dma_addr_t *)skb->cb),
				 rtlpci->rxbuffersize, PCI_DMA_FROMDEVICE);

		/* get a new skb - if fail, old one will be reused */
		new_skb = dev_alloc_skb(rtlpci->rxbuffersize);
		if (unlikely(!new_skb))
			goto no_new;
		memset(&rx_status, 0, sizeof(rx_status));
		rtlpriv->cfg->ops->query_rx_desc(hw, &stats,
						 &rx_status, (u8 *)pdesc, skb);

		if (rtlpriv->use_new_trx_flow)
			rtlpriv->cfg->ops->rx_check_dma_ok(hw,
							   (u8 *)buffer_desc,
							   hw_queue);

		len = rtlpriv->cfg->ops->get_desc(hw, (u8 *)pdesc, false,
						  HW_DESC_RXPKT_LEN);

		if (skb->end - skb->tail > len) {
			skb_put(skb, len);
			if (rtlpriv->use_new_trx_flow)
				skb_reserve(skb, stats.rx_drvinfo_size +
					    stats.rx_bufshift + 24);
			else
				skb_reserve(skb, stats.rx_drvinfo_size +
					    stats.rx_bufshift);
		} else {
			RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
				 "skb->end - skb->tail = %d, len is %d\n",
				 skb->end - skb->tail, len);
			dev_kfree_skb_any(skb);
			goto new_trx_end;
		}
		/* handle command packet here */
		if (stats.packet_report_type == C2H_PACKET) {
			rtl_c2hcmd_enqueue(hw, skb);
			goto new_trx_end;
		}

		/* NOTICE This can not be use for mac80211,
		 * this is done in mac80211 code,
		 * if done here sec DHCP will fail
		 * skb_trim(skb, skb->len - 4);
		 */

		hdr = rtl_get_hdr(skb);
		fc = rtl_get_fc(skb);

		if (!stats.crc && !stats.hwerror && (skb->len > FCS_LEN)) {
			memcpy(IEEE80211_SKB_RXCB(skb), &rx_status,
			       sizeof(rx_status));

			if (is_broadcast_ether_addr(hdr->addr1)) {
				;/*TODO*/
			} else if (is_multicast_ether_addr(hdr->addr1)) {
				;/*TODO*/
			} else {
				unicast = true;
				rtlpriv->stats.rxbytesunicast += skb->len;
			}
			rtl_is_special_data(hw, skb, false, true);

			if (ieee80211_is_data(fc)) {
				rtlpriv->cfg->ops->led_control(hw, LED_CTL_RX);
				if (unicast)
					rtlpriv->link_info.num_rx_inperiod++;
			}

			rtl_collect_scan_list(hw, skb);

			/* static bcn for roaming */
			rtl_beacon_statistic(hw, skb);
			rtl_p2p_info(hw, (void *)skb->data, skb->len);
			/* for sw lps */
			rtl_swlps_beacon(hw, (void *)skb->data, skb->len);
			rtl_recognize_peer(hw, (void *)skb->data, skb->len);
			if (rtlpriv->mac80211.opmode == NL80211_IFTYPE_AP &&
			    rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G &&
			    (ieee80211_is_beacon(fc) ||
			     ieee80211_is_probe_resp(fc))) {
				dev_kfree_skb_any(skb);
			} else {
				_rtl_pci_rx_to_mac80211(hw, skb, rx_status);
			}
		} else {
			/* drop packets with errors or those too short */
			dev_kfree_skb_any(skb);
		}
new_trx_end:
		if (rtlpriv->use_new_trx_flow) {
			rtlpci->rx_ring[hw_queue].next_rx_rp += 1;
			rtlpci->rx_ring[hw_queue].next_rx_rp %=
					RTL_PCI_MAX_RX_COUNT;

			rx_remained_cnt--;
			rtl_write_word(rtlpriv, 0x3B4,
				       rtlpci->rx_ring[hw_queue].next_rx_rp);
		}
		if (((rtlpriv->link_info.num_rx_inperiod +
		      rtlpriv->link_info.num_tx_inperiod) > 8) ||
		      rtlpriv->link_info.num_rx_inperiod > 2)
			rtl_lps_leave(hw);
		skb = new_skb;
no_new:
		if (rtlpriv->use_new_trx_flow) {
			_rtl_pci_init_one_rxdesc(hw, skb, (u8 *)buffer_desc,
						 rxring_idx,
						 rtlpci->rx_ring[rxring_idx].idx);
		} else {
			_rtl_pci_init_one_rxdesc(hw, skb, (u8 *)pdesc,
						 rxring_idx,
						 rtlpci->rx_ring[rxring_idx].idx);
			if (rtlpci->rx_ring[rxring_idx].idx ==
			    rtlpci->rxringcount - 1)
				rtlpriv->cfg->ops->set_desc(hw, (u8 *)pdesc,
							    false,
							    HW_DESC_RXERO,
							    (u8 *)&tmp_one);
		}
		rtlpci->rx_ring[rxring_idx].idx =
				(rtlpci->rx_ring[rxring_idx].idx + 1) %
				rtlpci->rxringcount;
	}
}