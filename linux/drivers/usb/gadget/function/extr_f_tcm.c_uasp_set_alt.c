#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {scalar_t__ speed; } ;
struct usb_function {TYPE_2__* config; } ;
struct f_uas {int /*<<< orphan*/  flags; int /*<<< orphan*/  ep_in; int /*<<< orphan*/  ep_out; int /*<<< orphan*/  ep_cmd; int /*<<< orphan*/  ep_status; struct usb_function function; } ;
struct TYPE_4__ {TYPE_1__* cdev; } ;
struct TYPE_3__ {struct usb_gadget* gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBG_ENABLED ; 
 int /*<<< orphan*/  USBG_IS_UAS ; 
 int /*<<< orphan*/  USBG_USE_STREAMS ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int /*<<< orphan*/  config_ep_by_speed (struct usb_gadget*,struct usb_function*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int uasp_prepare_reqs (struct f_uas*) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 
 int usb_ep_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uasp_set_alt(struct f_uas *fu)
{
	struct usb_function *f = &fu->function;
	struct usb_gadget *gadget = f->config->cdev->gadget;
	int ret;

	fu->flags = USBG_IS_UAS;

	if (gadget->speed == USB_SPEED_SUPER)
		fu->flags |= USBG_USE_STREAMS;

	config_ep_by_speed(gadget, f, fu->ep_in);
	ret = usb_ep_enable(fu->ep_in);
	if (ret)
		goto err_b_in;

	config_ep_by_speed(gadget, f, fu->ep_out);
	ret = usb_ep_enable(fu->ep_out);
	if (ret)
		goto err_b_out;

	config_ep_by_speed(gadget, f, fu->ep_cmd);
	ret = usb_ep_enable(fu->ep_cmd);
	if (ret)
		goto err_cmd;
	config_ep_by_speed(gadget, f, fu->ep_status);
	ret = usb_ep_enable(fu->ep_status);
	if (ret)
		goto err_status;

	ret = uasp_prepare_reqs(fu);
	if (ret)
		goto err_wq;
	fu->flags |= USBG_ENABLED;

	pr_info("Using the UAS protocol\n");
	return;
err_wq:
	usb_ep_disable(fu->ep_status);
err_status:
	usb_ep_disable(fu->ep_cmd);
err_cmd:
	usb_ep_disable(fu->ep_out);
err_b_out:
	usb_ep_disable(fu->ep_in);
err_b_in:
	fu->flags = 0;
}