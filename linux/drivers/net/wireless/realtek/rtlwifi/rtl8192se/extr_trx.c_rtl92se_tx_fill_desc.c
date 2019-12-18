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
typedef  int u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct rtl_tcb_desc {int mac_id; scalar_t__ use_driver_rate; int /*<<< orphan*/  ratr_index; scalar_t__ packet_bw; scalar_t__ rts_use_shortgi; scalar_t__ rts_use_shortpreamble; int /*<<< orphan*/  rts_rate; int /*<<< orphan*/  rts_sc; scalar_t__ rts_stbc; scalar_t__ cts_enable; scalar_t__ rts_enable; scalar_t__ use_shortpreamble; scalar_t__ use_shortgi; int /*<<< orphan*/  hw_rate; } ;
struct TYPE_3__ {scalar_t__ useramask; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct rtl_mac {scalar_t__ opmode; int bw_40; int /*<<< orphan*/  cur_40_prime_sc; } ;
struct rtl_hal {scalar_t__ version; } ;
struct TYPE_4__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ control; } ;
struct ieee80211_sta {scalar_t__ bandwidth; } ;
struct ieee80211_key_conf {int cipher; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int frame_control; int seq_ctrl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PCI_TX_DESC_CONTENT (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DESC_RATE11M ; 
 int /*<<< orphan*/  DESC_RATE12M ; 
 int /*<<< orphan*/  DESC_RATE1M ; 
 int /*<<< orphan*/  DESC_RATE2M ; 
 int /*<<< orphan*/  DESC_RATE54M ; 
 int /*<<< orphan*/  DESC_RATE5_5M ; 
 int /*<<< orphan*/  DESC_RATEMCS0 ; 
 int /*<<< orphan*/  IEEE80211_FCTL_MOREFRAGS ; 
 int /*<<< orphan*/  IEEE80211_SCTL_FRAG ; 
 int IEEE80211_SCTL_SEQ ; 
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_TX_DESC_AGG_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_CTS_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_RATE_FB_LIMIT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LINIP (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_MACID (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_NON_QOS (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PACKET_ID (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_QUEUE_SEL (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RA_BRSR_ID (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RSVD_MACID (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_BANDWIDTH (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_RATE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_SHORT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_STBC (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_SUB_CARRIER (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEC_TYPE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEQ (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TXHT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BANDWIDTH (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_ADDRESS (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_SIZE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_RATE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_SHORT (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_SUB_CARRIER (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_USER_RATE (int*,int) ; 
 int /*<<< orphan*/  TX_DESC_SIZE_RTL8192S ; 
 scalar_t__ VERSION_8192S_ACUT ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int _rtl92se_map_hwqueue_to_fwqueue (struct sk_buff*,int) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ctl (int) ; 
 int /*<<< orphan*/  ieee80211_is_data_qos (int) ; 
 scalar_t__ ieee80211_is_nullfunc (int) ; 
 int le16_to_cpu (int) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_tcb_desc (struct ieee80211_hw*,struct ieee80211_tx_info*,struct ieee80211_sta*,struct sk_buff*,struct rtl_tcb_desc*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92se_tx_fill_desc(struct ieee80211_hw *hw,
		struct ieee80211_hdr *hdr, u8 *pdesc_tx,
		u8 *pbd_desc_tx, struct ieee80211_tx_info *info,
		struct ieee80211_sta *sta,
		struct sk_buff *skb,
		u8 hw_queue, struct rtl_tcb_desc *ptcb_desc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 *pdesc = pdesc_tx;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	u8 reserved_macid = 0;
	u8 fw_qsel = _rtl92se_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = (!(hdr->seq_ctrl & cpu_to_le16(IEEE80211_SCTL_FRAG)));
	bool lastseg = (!(hdr->frame_control &
			cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)));
	dma_addr_t mapping = pci_map_single(rtlpci->pdev, skb->data, skb->len,
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
			bw_40 = sta->bandwidth >= IEEE80211_STA_RX_BW_40;
	}

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;

	rtl_get_tcb_desc(hw, info, sta, skb, ptcb_desc);

	CLEAR_PCI_TX_DESC_CONTENT(pdesc, TX_DESC_SIZE_RTL8192S);

	if (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) {
		firstseg = true;
		lastseg = true;
	}

	if (firstseg) {
		if (rtlpriv->dm.useramask) {
			/* set txdesc macId */
			if (ptcb_desc->mac_id < 32) {
				SET_TX_DESC_MACID(pdesc, ptcb_desc->mac_id);
				reserved_macid |= ptcb_desc->mac_id;
			}
		}
		SET_TX_DESC_RSVD_MACID(pdesc, reserved_macid);

		SET_TX_DESC_TXHT(pdesc, ((ptcb_desc->hw_rate >=
				 DESC_RATEMCS0) ? 1 : 0));

		if (rtlhal->version == VERSION_8192S_ACUT) {
			if (ptcb_desc->hw_rate == DESC_RATE1M ||
			    ptcb_desc->hw_rate  == DESC_RATE2M ||
			    ptcb_desc->hw_rate == DESC_RATE5_5M ||
			    ptcb_desc->hw_rate == DESC_RATE11M) {
				ptcb_desc->hw_rate = DESC_RATE12M;
			}
		}

		SET_TX_DESC_TX_RATE(pdesc, ptcb_desc->hw_rate);

		if (ptcb_desc->use_shortgi || ptcb_desc->use_shortpreamble)
			SET_TX_DESC_TX_SHORT(pdesc, 0);

		/* Aggregation related */
		if (info->flags & IEEE80211_TX_CTL_AMPDU)
			SET_TX_DESC_AGG_ENABLE(pdesc, 1);

		/* For AMPDU, we must insert SSN into TX_DESC */
		SET_TX_DESC_SEQ(pdesc, seq_number);

		/* Protection mode related */
		/* For 92S, if RTS/CTS are set, HW will execute RTS. */
		/* We choose only one protection mode to execute */
		SET_TX_DESC_RTS_ENABLE(pdesc, ((ptcb_desc->rts_enable &&
				!ptcb_desc->cts_enable) ? 1 : 0));
		SET_TX_DESC_CTS_ENABLE(pdesc, ((ptcb_desc->cts_enable) ?
				       1 : 0));
		SET_TX_DESC_RTS_STBC(pdesc, ((ptcb_desc->rts_stbc) ? 1 : 0));

		SET_TX_DESC_RTS_RATE(pdesc, ptcb_desc->rts_rate);
		SET_TX_DESC_RTS_BANDWIDTH(pdesc, 0);
		SET_TX_DESC_RTS_SUB_CARRIER(pdesc, ptcb_desc->rts_sc);
		SET_TX_DESC_RTS_SHORT(pdesc, ((ptcb_desc->rts_rate <=
		       DESC_RATE54M) ?
		       (ptcb_desc->rts_use_shortpreamble ? 1 : 0)
		       : (ptcb_desc->rts_use_shortgi ? 1 : 0)));


		/* Set Bandwidth and sub-channel settings. */
		if (bw_40) {
			if (ptcb_desc->packet_bw) {
				SET_TX_DESC_TX_BANDWIDTH(pdesc, 1);
				/* use duplicated mode */
				SET_TX_DESC_TX_SUB_CARRIER(pdesc, 0);
			} else {
				SET_TX_DESC_TX_BANDWIDTH(pdesc, 0);
				SET_TX_DESC_TX_SUB_CARRIER(pdesc,
						   mac->cur_40_prime_sc);
			}
		} else {
			SET_TX_DESC_TX_BANDWIDTH(pdesc, 0);
			SET_TX_DESC_TX_SUB_CARRIER(pdesc, 0);
		}

		/* 3 Fill necessary field in First Descriptor */
		/*DWORD 0*/
		SET_TX_DESC_LINIP(pdesc, 0);
		SET_TX_DESC_OFFSET(pdesc, 32);
		SET_TX_DESC_PKT_SIZE(pdesc, (u16) skb->len);

		/*DWORD 1*/
		SET_TX_DESC_RA_BRSR_ID(pdesc, ptcb_desc->ratr_index);

		/* Fill security related */
		if (info->control.hw_key) {
			struct ieee80211_key_conf *keyconf;

			keyconf = info->control.hw_key;
			switch (keyconf->cipher) {
			case WLAN_CIPHER_SUITE_WEP40:
			case WLAN_CIPHER_SUITE_WEP104:
				SET_TX_DESC_SEC_TYPE(pdesc, 0x1);
				break;
			case WLAN_CIPHER_SUITE_TKIP:
				SET_TX_DESC_SEC_TYPE(pdesc, 0x2);
				break;
			case WLAN_CIPHER_SUITE_CCMP:
				SET_TX_DESC_SEC_TYPE(pdesc, 0x3);
				break;
			default:
				SET_TX_DESC_SEC_TYPE(pdesc, 0x0);
				break;

			}
		}

		/* Set Packet ID */
		SET_TX_DESC_PACKET_ID(pdesc, 0);

		/* We will assign magement queue to BK. */
		SET_TX_DESC_QUEUE_SEL(pdesc, fw_qsel);

		/* Alwasy enable all rate fallback range */
		SET_TX_DESC_DATA_RATE_FB_LIMIT(pdesc, 0x1F);

		/* Fix: I don't kown why hw use 6.5M to tx when set it */
		SET_TX_DESC_USER_RATE(pdesc,
				      ptcb_desc->use_driver_rate ? 1 : 0);

		/* Set NON_QOS bit. */
		if (!ieee80211_is_data_qos(fc))
			SET_TX_DESC_NON_QOS(pdesc, 1);

	}

	/* Fill fields that are required to be initialized
	 * in all of the descriptors */
	/*DWORD 0 */
	SET_TX_DESC_FIRST_SEG(pdesc, (firstseg ? 1 : 0));
	SET_TX_DESC_LAST_SEG(pdesc, (lastseg ? 1 : 0));

	/* DWORD 7 */
	SET_TX_DESC_TX_BUFFER_SIZE(pdesc, (u16) skb->len);

	/* DOWRD 8 */
	SET_TX_DESC_TX_BUFFER_ADDRESS(pdesc, mapping);

	RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
}