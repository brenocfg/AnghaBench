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
typedef  int u16 ;
struct TYPE_4__ {int state; } ;
struct isp1760_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ep; TYPE_2__ gadget; TYPE_1__* isp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ADDRESS ; 
 int DC_DEVEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int USB_STATE_ADDRESS ; 
 int USB_STATE_DEFAULT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  isp1760_udc_ctrl_send_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1760_udc_write (struct isp1760_udc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_set_state (TYPE_2__*,int) ; 

__attribute__((used)) static int isp1760_udc_set_address(struct isp1760_udc *udc, u16 addr)
{
	if (addr > 127) {
		dev_dbg(udc->isp->dev, "invalid device address %u\n", addr);
		return -EINVAL;
	}

	if (udc->gadget.state != USB_STATE_DEFAULT &&
	    udc->gadget.state != USB_STATE_ADDRESS) {
		dev_dbg(udc->isp->dev, "can't set address in state %u\n",
			udc->gadget.state);
		return -EINVAL;
	}

	usb_gadget_set_state(&udc->gadget, addr ? USB_STATE_ADDRESS :
			     USB_STATE_DEFAULT);

	isp1760_udc_write(udc, DC_ADDRESS, DC_DEVEN | addr);

	spin_lock(&udc->lock);
	isp1760_udc_ctrl_send_status(&udc->ep[0], USB_DIR_OUT);
	spin_unlock(&udc->lock);

	return 0;
}