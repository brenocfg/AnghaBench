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
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DESC92C_RATE1M ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  QSLT_BEACON ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TX_DESC_SIZE ; 
 int USB_HWDESC_HEADER_LEN ; 
 int /*<<< orphan*/  clear_pci_tx_desc_content (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  set_tx_desc_first_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_hwseq_en (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_last_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_linip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_macid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_offset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_own (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_queue_sel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_rate_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_tx_buffer_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_tx_buffer_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_tx_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_use_rate (int /*<<< orphan*/ *,int) ; 

void rtl88ee_tx_fill_cmddesc(struct ieee80211_hw *hw,
			     u8 *pdesc8, bool firstseg,
			     bool lastseg, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 fw_queue = QSLT_BEACON;
	__le32 *pdesc = (__le32 *)pdesc8;

	dma_addr_t mapping = pci_map_single(rtlpci->pdev,
					    skb->data, skb->len,
					    PCI_DMA_TODEVICE);

	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;

	if (pci_dma_mapping_error(rtlpci->pdev, mapping)) {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
			 "DMA mapping error\n");
		return;
	}
	clear_pci_tx_desc_content(pdesc, TX_DESC_SIZE);

	if (firstseg)
		set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);

	set_tx_desc_tx_rate(pdesc, DESC92C_RATE1M);

	set_tx_desc_seq(pdesc, 0);

	set_tx_desc_linip(pdesc, 0);

	set_tx_desc_queue_sel(pdesc, fw_queue);

	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);

	set_tx_desc_tx_buffer_size(pdesc, (u16)(skb->len));

	set_tx_desc_tx_buffer_address(pdesc, mapping);

	set_tx_desc_rate_id(pdesc, 7);
	set_tx_desc_macid(pdesc, 0);

	set_tx_desc_own(pdesc, 1);

	set_tx_desc_pkt_size(pdesc, (u16)(skb->len));

	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);

	set_tx_desc_offset(pdesc, 0x20);

	set_tx_desc_use_rate(pdesc, 1);

	if (!ieee80211_is_data_qos(fc))
		set_tx_desc_hwseq_en(pdesc, 1);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "H2C Tx Cmd Content\n",
		      pdesc, TX_DESC_SIZE);
}