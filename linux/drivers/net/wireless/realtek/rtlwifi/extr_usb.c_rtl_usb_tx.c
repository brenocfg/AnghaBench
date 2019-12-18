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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct rtl_usb {int /*<<< orphan*/  (* usb_mq_to_hwq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct rtl_tcb_desc {int dummy; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  _rtl_usb_transmit (struct ieee80211_hw*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl_usb_tx_preprocess (struct ieee80211_hw*,struct ieee80211_sta*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  is_hal_stop (struct rtl_hal*) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl_usb_tx(struct ieee80211_hw *hw,
		      struct ieee80211_sta *sta,
		      struct sk_buff *skb,
		      struct rtl_tcb_desc *dummy)
{
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;
	u16 hw_queue;

	if (unlikely(is_hal_stop(rtlhal)))
		goto err_free;
	hw_queue = rtlusb->usb_mq_to_hwq(fc, skb_get_queue_mapping(skb));
	_rtl_usb_tx_preprocess(hw, sta, skb, hw_queue);
	_rtl_usb_transmit(hw, skb, hw_queue);
	return NETDEV_TX_OK;

err_free:
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}