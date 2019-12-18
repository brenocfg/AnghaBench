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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DESC_RATE1M ; 
 int /*<<< orphan*/  QSLT_BEACON ; 
 int /*<<< orphan*/  RTL_TX_DESC_SIZE ; 
 int RTL_TX_HEADER_SIZE ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  set_tx_desc_first_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_hwseq_en (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_last_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_linip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_macid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_offset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_own (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_queue_sel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_rate_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_tx_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_use_rate (int /*<<< orphan*/ *,int) ; 

void rtl92cu_tx_fill_cmddesc(struct ieee80211_hw *hw,
			     u8 *pdesc8, bool firstseg,
			     bool lastseg, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 fw_queue = QSLT_BEACON;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;
	__le32 *pdesc = (__le32 *)pdesc8;

	memset((void *)pdesc, 0, RTL_TX_HEADER_SIZE);
	if (firstseg)
		set_tx_desc_offset(pdesc, RTL_TX_HEADER_SIZE);
	set_tx_desc_tx_rate(pdesc, DESC_RATE1M);
	set_tx_desc_seq(pdesc, 0);
	set_tx_desc_linip(pdesc, 0);
	set_tx_desc_queue_sel(pdesc, fw_queue);
	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);
	set_tx_desc_rate_id(pdesc, 7);
	set_tx_desc_macid(pdesc, 0);
	set_tx_desc_own(pdesc, 1);
	set_tx_desc_pkt_size(pdesc, (u16)skb->len);
	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);
	set_tx_desc_offset(pdesc, 0x20);
	set_tx_desc_use_rate(pdesc, 1);
	if (!ieee80211_is_data_qos(fc)) {
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	}
	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD, "H2C Tx Cmd Content",
		      pdesc, RTL_TX_DESC_SIZE);
}