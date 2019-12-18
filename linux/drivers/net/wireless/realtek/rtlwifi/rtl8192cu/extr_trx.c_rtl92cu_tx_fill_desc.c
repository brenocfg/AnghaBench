#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct sk_buff {int len; } ;
struct rtl_tcb_desc {scalar_t__ ratr_index; scalar_t__ mac_id; scalar_t__ use_driver_rate; scalar_t__ rts_use_shortgi; scalar_t__ rts_use_shortpreamble; int /*<<< orphan*/  rts_rate; int /*<<< orphan*/  rts_sc; scalar_t__ rts_stbc; scalar_t__ cts_enable; scalar_t__ rts_enable; scalar_t__ use_shortpreamble; scalar_t__ use_shortgi; int /*<<< orphan*/  hw_rate; } ;
struct rtl_ps_ctl {scalar_t__ fwctrl_lps; scalar_t__ leisure_ps; } ;
struct TYPE_12__ {scalar_t__ useramask; } ;
struct rtl_priv {TYPE_6__ dm; } ;
struct rtl_mac {int cur_40_prime_sc; scalar_t__ rdg_en; int /*<<< orphan*/  bssid; int /*<<< orphan*/  vif; scalar_t__ bw_40; TYPE_3__* tids; } ;
struct TYPE_11__ {struct ieee80211_key_conf* hw_key; TYPE_1__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_5__ control; } ;
struct TYPE_10__ {size_t ampdu_density; } ;
struct ieee80211_sta {TYPE_4__ ht_cap; } ;
struct ieee80211_key_conf {int cipher; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  frame_control; } ;
typedef  enum rtl_desc_qsel { ____Placeholder_rtl_desc_qsel } rtl_desc_qsel ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_8__ {scalar_t__ agg_state; } ;
struct TYPE_9__ {TYPE_2__ agg; } ;
struct TYPE_7__ {size_t flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DESC_RATE54M ; 
 size_t IEEE80211_QOS_CTL_TID_MASK ; 
 int IEEE80211_SCTL_SEQ ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 size_t IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 size_t IEEE80211_TX_RC_DUP_DATA ; 
 scalar_t__ RTL_AGG_ON ; 
 int /*<<< orphan*/  RTL_DUMMY_OFFSET ; 
 int /*<<< orphan*/  RTL_TX_HEADER_SIZE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int _rtl8192cu_mq_to_descq (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl_fill_usb_tx_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl_tx_desc_checksum (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* ieee80211_find_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 size_t* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rtl_get_tcb_desc (struct ieee80211_hw*,struct ieee80211_tx_info*,struct ieee80211_sta*,struct sk_buff*,struct rtl_tcb_desc*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  set_tx_desc_agg_break (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_agg_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_ampdu_density (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  set_tx_desc_bmc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_cts2self (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_data_bw (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_data_rate_fb_limit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_data_sc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_data_shortgi (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_disable_fb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_htc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_hw_rts_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_hwseq_en (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_linip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_macid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_tx_desc_max_agg_num (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_more_frag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_qos (int /*<<< orphan*/ *,int) ; 
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
 int /*<<< orphan*/  set_tx_desc_tx_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_use_rate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 size_t* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

void rtl92cu_tx_fill_desc(struct ieee80211_hw *hw,
			  struct ieee80211_hdr *hdr, u8 *pdesc_tx,
			  u8 *pbd_desc_tx, struct ieee80211_tx_info *info,
			  struct ieee80211_sta *sta,
			  struct sk_buff *skb,
			  u8 queue_index,
			  struct rtl_tcb_desc *tcb_desc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool defaultadapter = true;
	u8 *qc = ieee80211_get_qos_ctl(hdr);
	u8 tid = qc[0] & IEEE80211_QOS_CTL_TID_MASK;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	u8 rate_flag = info->control.rates[0].flags;
	u16 pktlen = skb->len;
	enum rtl_desc_qsel fw_qsel = _rtl8192cu_mq_to_descq(hw, fc,
						skb_get_queue_mapping(skb));
	u8 *txdesc8;
	__le32 *txdesc;

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;
	rtl_get_tcb_desc(hw, info, sta, skb, tcb_desc);
	txdesc8 = skb_push(skb, RTL_TX_HEADER_SIZE);
	txdesc = (__le32 *)txdesc8;
	memset(txdesc, 0, RTL_TX_HEADER_SIZE);
	set_tx_desc_pkt_size(txdesc, pktlen);
	set_tx_desc_linip(txdesc, 0);
	set_tx_desc_pkt_offset(txdesc, RTL_DUMMY_OFFSET);
	set_tx_desc_offset(txdesc, RTL_TX_HEADER_SIZE);
	set_tx_desc_tx_rate(txdesc, tcb_desc->hw_rate);
	if (tcb_desc->use_shortgi || tcb_desc->use_shortpreamble)
		set_tx_desc_data_shortgi(txdesc, 1);
	if (mac->tids[tid].agg.agg_state == RTL_AGG_ON &&
		    info->flags & IEEE80211_TX_CTL_AMPDU) {
		set_tx_desc_agg_enable(txdesc, 1);
		set_tx_desc_max_agg_num(txdesc, 0x14);
	} else {
		set_tx_desc_agg_break(txdesc, 1);
	}
	set_tx_desc_seq(txdesc, seq_number);
	set_tx_desc_rts_enable(txdesc,
			       ((tcb_desc->rts_enable &&
				!tcb_desc->cts_enable) ? 1 : 0));
	set_tx_desc_hw_rts_enable(txdesc,
				  ((tcb_desc->rts_enable ||
				   tcb_desc->cts_enable) ? 1 : 0));
	set_tx_desc_cts2self(txdesc, ((tcb_desc->cts_enable) ? 1 : 0));
	set_tx_desc_rts_stbc(txdesc, ((tcb_desc->rts_stbc) ? 1 : 0));
	set_tx_desc_rts_rate(txdesc, tcb_desc->rts_rate);
	set_tx_desc_rts_bw(txdesc, 0);
	set_tx_desc_rts_sc(txdesc, tcb_desc->rts_sc);
	set_tx_desc_rts_short(txdesc,
			      ((tcb_desc->rts_rate <= DESC_RATE54M) ?
			       (tcb_desc->rts_use_shortpreamble ? 1 : 0)
			       : (tcb_desc->rts_use_shortgi ? 1 : 0)));
	if (mac->bw_40) {
		if (rate_flag & IEEE80211_TX_RC_DUP_DATA) {
			set_tx_desc_data_bw(txdesc, 1);
			set_tx_desc_data_sc(txdesc, 3);
		} else if(rate_flag & IEEE80211_TX_RC_40_MHZ_WIDTH){
			set_tx_desc_data_bw(txdesc, 1);
			set_tx_desc_data_sc(txdesc, mac->cur_40_prime_sc);
		} else {
			set_tx_desc_data_bw(txdesc, 0);
			set_tx_desc_data_sc(txdesc, 0);
		}
	} else {
		set_tx_desc_data_bw(txdesc, 0);
		set_tx_desc_data_sc(txdesc, 0);
	}
	rcu_read_lock();
	sta = ieee80211_find_sta(mac->vif, mac->bssid);
	if (sta) {
		u8 ampdu_density = sta->ht_cap.ampdu_density;

		set_tx_desc_ampdu_density(txdesc, ampdu_density);
	}
	rcu_read_unlock();
	if (info->control.hw_key) {
		struct ieee80211_key_conf *keyconf = info->control.hw_key;

		switch (keyconf->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
		case WLAN_CIPHER_SUITE_TKIP:
			set_tx_desc_sec_type(txdesc, 0x1);
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			set_tx_desc_sec_type(txdesc, 0x3);
			break;
		default:
			set_tx_desc_sec_type(txdesc, 0x0);
			break;
		}
	}
	set_tx_desc_pkt_id(txdesc, 0);
	set_tx_desc_queue_sel(txdesc, fw_qsel);
	set_tx_desc_data_rate_fb_limit(txdesc, 0x1F);
	set_tx_desc_rts_rate_fb_limit(txdesc, 0xF);
	set_tx_desc_disable_fb(txdesc, 0);
	set_tx_desc_use_rate(txdesc, tcb_desc->use_driver_rate ? 1 : 0);
	if (ieee80211_is_data_qos(fc)) {
		if (mac->rdg_en) {
			RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
				 "Enable RDG function\n");
			set_tx_desc_rdg_enable(txdesc, 1);
			set_tx_desc_htc(txdesc, 1);
		}
	}
	if (rtlpriv->dm.useramask) {
		set_tx_desc_rate_id(txdesc, tcb_desc->ratr_index);
		set_tx_desc_macid(txdesc, tcb_desc->mac_id);
	} else {
		set_tx_desc_rate_id(txdesc, 0xC + tcb_desc->ratr_index);
		set_tx_desc_macid(txdesc, tcb_desc->ratr_index);
	}
	if ((!ieee80211_is_data_qos(fc)) && ppsc->leisure_ps &&
	      ppsc->fwctrl_lps) {
		set_tx_desc_hwseq_en(txdesc, 1);
		set_tx_desc_pkt_id(txdesc, 8);
		if (!defaultadapter)
			set_tx_desc_qos(txdesc, 1);
	}
	if (ieee80211_has_morefrags(fc))
		set_tx_desc_more_frag(txdesc, 1);
	if (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr)))
		set_tx_desc_bmc(txdesc, 1);
	_rtl_fill_usb_tx_desc(txdesc);
	_rtl_tx_desc_checksum(txdesc);
	RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE, "==>\n");
}