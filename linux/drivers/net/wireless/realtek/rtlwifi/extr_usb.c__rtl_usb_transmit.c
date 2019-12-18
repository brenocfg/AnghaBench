#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct urb {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ep_mapping; } ;
struct rtl_usb {TYPE_1__ ep_map; int /*<<< orphan*/ * usb_tx_aggregate_hdl; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rtl_txq { ____Placeholder_rtl_txq } rtl_txq ;

/* Variables and functions */
 int IS_USB_STOP (struct rtl_usb*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _rtl_submit_tx_urb (struct ieee80211_hw*,struct urb*) ; 
 struct urb* _rtl_usb_tx_urb_setup (struct ieee80211_hw*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void _rtl_usb_transmit(struct ieee80211_hw *hw, struct sk_buff *skb,
		       enum rtl_txq qnum)
{
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	u32 ep_num;
	struct urb *_urb = NULL;
	struct sk_buff *_skb = NULL;

	WARN_ON(NULL == rtlusb->usb_tx_aggregate_hdl);
	if (unlikely(IS_USB_STOP(rtlusb))) {
		pr_err("USB device is stopping...\n");
		kfree_skb(skb);
		return;
	}
	ep_num = rtlusb->ep_map.ep_mapping[qnum];
	_skb = skb;
	_urb = _rtl_usb_tx_urb_setup(hw, _skb, ep_num);
	if (unlikely(!_urb)) {
		pr_err("Can't allocate urb. Drop skb!\n");
		kfree_skb(skb);
		return;
	}
	_rtl_submit_tx_urb(hw, _urb);
}