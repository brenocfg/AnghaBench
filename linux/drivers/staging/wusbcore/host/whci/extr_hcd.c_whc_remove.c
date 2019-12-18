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
struct wusbhc {int /*<<< orphan*/  uwb_rc; } ;
struct whc {int dummy; } ;
struct usb_hcd {int dummy; } ;
struct umc_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct usb_hcd* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  uwb_rc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whc_clean_up (struct whc*) ; 
 int /*<<< orphan*/  whc_dbg_clean_up (struct whc*) ; 
 int /*<<< orphan*/  wusbhc_b_destroy (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_destroy (struct wusbhc*) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

__attribute__((used)) static void whc_remove(struct umc_dev *umc)
{
	struct usb_hcd *usb_hcd = dev_get_drvdata(&umc->dev);
	struct wusbhc *wusbhc = usb_hcd_to_wusbhc(usb_hcd);
	struct whc *whc = wusbhc_to_whc(wusbhc);

	if (usb_hcd) {
		whc_dbg_clean_up(whc);
		wusbhc_b_destroy(wusbhc);
		usb_remove_hcd(usb_hcd);
		wusbhc_destroy(wusbhc);
		uwb_rc_put(wusbhc->uwb_rc);
		whc_clean_up(whc);
		usb_put_hcd(usb_hcd);
	}
}