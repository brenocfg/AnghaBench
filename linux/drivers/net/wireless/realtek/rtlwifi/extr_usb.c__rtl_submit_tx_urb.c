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
struct urb {scalar_t__ context; } ;
struct sk_buff {int dummy; } ;
struct rtl_usb {int /*<<< orphan*/  tx_submitted; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void _rtl_submit_tx_urb(struct ieee80211_hw *hw, struct urb *_urb)
{
	int err;
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	usb_anchor_urb(_urb, &rtlusb->tx_submitted);
	err = usb_submit_urb(_urb, GFP_ATOMIC);
	if (err < 0) {
		struct sk_buff *skb;

		pr_err("Failed to submit urb\n");
		usb_unanchor_urb(_urb);
		skb = (struct sk_buff *)_urb->context;
		kfree_skb(skb);
	}
	usb_free_urb(_urb);
}