#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct tx_desc_8723e {int dummy; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct rtl_tcb_desc {scalar_t__ packet_bw; scalar_t__ ratr_index; scalar_t__ mac_id; scalar_t__ use_driver_rate; scalar_t__ rts_use_shortgi; scalar_t__ rts_use_shortpreamble; int /*<<< orphan*/  rts_rate; int /*<<< orphan*/  rts_sc; scalar_t__ rts_stbc; scalar_t__ cts_enable; scalar_t__ rts_enable; scalar_t__ use_shortpreamble; scalar_t__ use_shortgi; int /*<<< orphan*/  hw_rate; } ;
struct rtl_ps_ctl {scalar_t__ fwctrl_lps; } ;
struct TYPE_6__ {scalar_t__ useramask; } ;
struct rtl_priv {TYPE_3__ dm; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct rtl_mac {scalar_t__ opmode; int bw_40; int cur_40_prime_sc; scalar_t__ rdg_en; } ;
struct TYPE_5__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ control; } ;
struct TYPE_4__ {int cap; int ampdu_density; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; } ;
struct ieee80211_key_conf {int cipher; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int frame_control; int seq_ctrl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DESC92C_RATE54M ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 int /*<<< orphan*/  IEEE80211_FCTL_MOREFRAGS ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int /*<<< orphan*/  IEEE80211_SCTL_FRAG ; 
 int IEEE80211_SCTL_SEQ ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  USB_HWDESC_HEADER_LEN ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int _rtl8723e_map_hwqueue_to_fwqueue (struct sk_buff*,int) ; 
 int /*<<< orphan*/  clear_pci_tx_desc_content (int /*<<< orphan*/ *,int) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_ctl (int) ; 
 scalar_t__ ieee80211_is_data_qos (int) ; 
 scalar_t__ ieee80211_is_nullfunc (int) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_tcb_desc (struct ieee80211_hw*,struct ieee80211_tx_info*,struct ieee80211_sta*,struct sk_buff*,struct rtl_tcb_desc*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  set_tx_desc_agg_break (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_ampdu_density (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_bmc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_cts2self (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_data_bw (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_data_rate_fb_limit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_data_shortgi (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_disable_fb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_first_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_htc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_hw_rts_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_hwseq_en_8723 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_hwseq_sel_8723 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_last_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_linip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_macid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_tx_desc_max_agg_num (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_more_frag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_queue_sel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_rate_id (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_tx_desc_rdg_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_rts_bw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_rts_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_rts_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_rts_rate_fb_limit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_rts_sc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_rts_short (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_rts_stbc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_sec_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_seq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_tx_buffer_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_tx_buffer_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_tx_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_tx_sub_carrier (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_use_rate (int /*<<< orphan*/ *,int) ; 

void rtl8723e_tx_fill_desc(struct ieee80211_hw *hw,
			   struct ieee80211_hdr *hdr, u8 *pdesc_tx,
			   u8 *txbd, struct ieee80211_tx_info *info,
			   struct ieee80211_sta *sta,
			   struct sk_buff *skb,
			   u8 hw_queue, struct rtl_tcb_desc *ptcb_desc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool b_defaultadapter = true;
	/* bool b_trigger_ac = false; */
	u8 *pdesc8 = (u8 *)pdesc_tx;
	__le32 *pdesc = (__le32 *)pdesc8;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	u8 fw_qsel = _rtl8723e_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = ((hdr->seq_ctrl &
			  cpu_to_le16(IEEE80211_SCTL_FRAG)) == 0);

	bool lastseg = ((hdr->frame_control &
			 cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) == 0);

	dma_addr_t mapping = pci_map_single(rtlpci->pdev,
					    skb->data, skb->len,
					    PCI_DMA_TODEVICE);
	u8 bw_40 = 0;

	if (pci_dma_mapping_error(rtlpci->pdev, mapping)) {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
			 "DMA mapping error\n");
		return;
	}
	if (mac->opmode == NL80211_IFTYPE_STATION) {
		bw_40 = mac->bw_40;
	} else if (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC) {
		if (sta)
			bw_40 = sta->ht_cap.cap &
				IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	}

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;

	rtl_get_tcb_desc(hw, info, sta, skb, ptcb_desc);

	clear_pci_tx_desc_content(pdesc, sizeof(struct tx_desc_8723e));

	if (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) {
		firstseg = true;
		lastseg = true;
	}

	if (firstseg) {
		set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);

		set_tx_desc_tx_rate(pdesc, ptcb_desc->hw_rate);

		if (ptcb_desc->use_shortgi || ptcb_desc->use_shortpreamble)
			set_tx_desc_data_shortgi(pdesc, 1);

		if (info->flags & IEEE80211_TX_CTL_AMPDU) {
			set_tx_desc_agg_break(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x14);
		}
		set_tx_desc_seq(pdesc, seq_number);

		set_tx_desc_rts_enable(pdesc,
				       ((ptcb_desc->rts_enable &&
					!ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_hw_rts_enable(pdesc,
					  ((ptcb_desc->rts_enable ||
					  ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_cts2self(pdesc,
				     ((ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_rts_stbc(pdesc,
				     ((ptcb_desc->rts_stbc) ? 1 : 0));

		set_tx_desc_rts_rate(pdesc, ptcb_desc->rts_rate);
		set_tx_desc_rts_bw(pdesc, 0);
		set_tx_desc_rts_sc(pdesc, ptcb_desc->rts_sc);
		set_tx_desc_rts_short(pdesc,
				((ptcb_desc->rts_rate <= DESC92C_RATE54M) ?
				(ptcb_desc->rts_use_shortpreamble ? 1 : 0)
				: (ptcb_desc->rts_use_shortgi ? 1 : 0)));

		if (bw_40) {
			if (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) {
				set_tx_desc_data_bw(pdesc, 1);
				set_tx_desc_tx_sub_carrier(pdesc, 3);
			} else {
				set_tx_desc_data_bw(pdesc, 0);
				set_tx_desc_tx_sub_carrier(pdesc,
					mac->cur_40_prime_sc);
			}
		} else {
			set_tx_desc_data_bw(pdesc, 0);
			set_tx_desc_tx_sub_carrier(pdesc, 0);
		}

		set_tx_desc_linip(pdesc, 0);
		set_tx_desc_pkt_size(pdesc, (u16)skb->len);

		if (sta) {
			u8 ampdu_density = sta->ht_cap.ampdu_density;
			set_tx_desc_ampdu_density(pdesc, ampdu_density);
		}

		if (info->control.hw_key) {
			struct ieee80211_key_conf *keyconf =
			    info->control.hw_key;

			switch (keyconf->cipher) {
			case WLAN_CIPHER_SUITE_WEP40:
			case WLAN_CIPHER_SUITE_WEP104:
			case WLAN_CIPHER_SUITE_TKIP:
				set_tx_desc_sec_type(pdesc, 0x1);
				break;
			case WLAN_CIPHER_SUITE_CCMP:
				set_tx_desc_sec_type(pdesc, 0x3);
				break;
			default:
				set_tx_desc_sec_type(pdesc, 0x0);
				break;

			}
		}

		set_tx_desc_pkt_id(pdesc, 0);
		set_tx_desc_queue_sel(pdesc, fw_qsel);

		set_tx_desc_data_rate_fb_limit(pdesc, 0x1F);
		set_tx_desc_rts_rate_fb_limit(pdesc, 0xF);
		set_tx_desc_disable_fb(pdesc, 0);
		set_tx_desc_use_rate(pdesc, ptcb_desc->use_driver_rate ? 1 : 0);

		if (ieee80211_is_data_qos(fc)) {
			if (mac->rdg_en) {
				RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
					 "Enable RDG function.\n");
				set_tx_desc_rdg_enable(pdesc, 1);
				set_tx_desc_htc(pdesc, 1);
			}
		}
	}

	set_tx_desc_first_seg(pdesc, (firstseg ? 1 : 0));
	set_tx_desc_last_seg(pdesc, (lastseg ? 1 : 0));

	set_tx_desc_tx_buffer_size(pdesc, (u16)skb->len);

	set_tx_desc_tx_buffer_address(pdesc, mapping);

	if (rtlpriv->dm.useramask) {
		set_tx_desc_rate_id(pdesc, ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
	} else {
		set_tx_desc_rate_id(pdesc, 0xC + ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->ratr_index);
	}

	if ((!ieee80211_is_data_qos(fc)) && ppsc->fwctrl_lps) {
		set_tx_desc_hwseq_en_8723(pdesc, 1);
		/* set_tx_desc_hwseq_en(pdesc, 1); */
		/* set_tx_desc_pkt_id(pdesc, 8); */

		if (!b_defaultadapter)
			set_tx_desc_hwseq_sel_8723(pdesc, 1);
	/* set_tx_desc_qos(pdesc, 1); */
	}

	set_tx_desc_more_frag(pdesc, (lastseg ? 0 : 1));

	if (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr))) {
		set_tx_desc_bmc(pdesc, 1);
	}

	RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
}