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
typedef  scalar_t__ u32 ;
struct usb_ctrlrequest {int /*<<< orphan*/  wValue; } ;
struct TYPE_4__ {int state; } ;
struct cdns3_device {TYPE_2__ gadget; TYPE_1__* regs; int /*<<< orphan*/  dev; } ;
typedef  enum usb_device_state { ____Placeholder_usb_device_state } usb_device_state ;
struct TYPE_3__ {int /*<<< orphan*/  usb_cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ USB_CMD_FADDR (scalar_t__) ; 
 scalar_t__ USB_CMD_SET_ADDR ; 
 scalar_t__ USB_DEVICE_MAX_ADDRESS ; 
 int /*<<< orphan*/  USB_STATE_ADDRESS ; 
 int USB_STATE_CONFIGURED ; 
 int /*<<< orphan*/  USB_STATE_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_req_ep0_set_address(struct cdns3_device *priv_dev,
				     struct usb_ctrlrequest *ctrl_req)
{
	enum usb_device_state device_state = priv_dev->gadget.state;
	u32 reg;
	u32 addr;

	addr = le16_to_cpu(ctrl_req->wValue);

	if (addr > USB_DEVICE_MAX_ADDRESS) {
		dev_err(priv_dev->dev,
			"Device address (%d) cannot be greater than %d\n",
			addr, USB_DEVICE_MAX_ADDRESS);
		return -EINVAL;
	}

	if (device_state == USB_STATE_CONFIGURED) {
		dev_err(priv_dev->dev,
			"can't set_address from configured state\n");
		return -EINVAL;
	}

	reg = readl(&priv_dev->regs->usb_cmd);

	writel(reg | USB_CMD_FADDR(addr) | USB_CMD_SET_ADDR,
	       &priv_dev->regs->usb_cmd);

	usb_gadget_set_state(&priv_dev->gadget,
			     (addr ? USB_STATE_ADDRESS : USB_STATE_DEFAULT));

	return 0;
}