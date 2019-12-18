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
struct usb_interface {int dummy; } ;
struct ieee80211_hw {struct ar5523* priv; } ;
struct ar5523 {int /*<<< orphan*/  wq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_USB_DISCONNECTED ; 
 int /*<<< orphan*/  ar5523_cancel_rx_cmd (struct ar5523*) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 int /*<<< orphan*/  ar5523_free_rx_bufs (struct ar5523*) ; 
 int /*<<< orphan*/  ar5523_free_rx_cmd (struct ar5523*) ; 
 int /*<<< orphan*/  ar5523_free_tx_cmd (struct ar5523*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ieee80211_hw* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ar5523_disconnect(struct usb_interface *intf)
{
	struct ieee80211_hw *hw = usb_get_intfdata(intf);
	struct ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "detaching\n");
	set_bit(AR5523_USB_DISCONNECTED, &ar->flags);

	ieee80211_unregister_hw(hw);

	ar5523_cancel_rx_cmd(ar);
	ar5523_free_tx_cmd(ar);
	ar5523_free_rx_cmd(ar);
	ar5523_free_rx_bufs(ar);

	destroy_workqueue(ar->wq);

	ieee80211_free_hw(hw);
	usb_set_intfdata(intf, NULL);
}