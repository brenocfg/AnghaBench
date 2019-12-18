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
typedef  int /*<<< orphan*/  u32 ;
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rtl_usb {int /*<<< orphan*/  udev; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _rtl_install_trx_info (struct rtl_usb*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl_tx_complete ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct urb *_rtl_usb_tx_urb_setup(struct ieee80211_hw *hw,
				struct sk_buff *skb, u32 ep_num)
{
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	struct urb *_urb;

	WARN_ON(NULL == skb);
	_urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!_urb) {
		kfree_skb(skb);
		return NULL;
	}
	_rtl_install_trx_info(rtlusb, skb, ep_num);
	usb_fill_bulk_urb(_urb, rtlusb->udev, usb_sndbulkpipe(rtlusb->udev,
			  ep_num), skb->data, skb->len, _rtl_tx_complete, skb);
	_urb->transfer_flags |= URB_ZERO_PACKET;
	return _urb;
}