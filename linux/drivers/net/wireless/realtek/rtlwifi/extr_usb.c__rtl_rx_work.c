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
struct sk_buff {int dummy; } ;
struct rtl_usb {int /*<<< orphan*/  usb_rx_segregate_hdl; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  intf; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_USB_STOP (struct rtl_usb*) ; 
 int /*<<< orphan*/  _rtl_rx_pre_process (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  _rtl_usb_rx_process_noagg (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* usb_get_intfdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl_rx_work(unsigned long param)
{
	struct rtl_usb *rtlusb = (struct rtl_usb *)param;
	struct ieee80211_hw *hw = usb_get_intfdata(rtlusb->intf);
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&rtlusb->rx_queue))) {
		if (unlikely(IS_USB_STOP(rtlusb))) {
			dev_kfree_skb_any(skb);
			continue;
		}

		if (likely(!rtlusb->usb_rx_segregate_hdl)) {
			_rtl_usb_rx_process_noagg(hw, skb);
		} else {
			/* TO DO */
			_rtl_rx_pre_process(hw, skb);
			pr_err("rx agg not supported\n");
		}
	}
}