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
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct cdns3_device {TYPE_1__* regs; TYPE_2__ gadget; } ;
struct cdns3 {struct cdns3_device* gadget_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_ien; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  cdns3_disconnect_gadget (struct cdns3_device*) ; 
 int /*<<< orphan*/  cdns3_hw_reset_eps_config (struct cdns3_device*) ; 
 int /*<<< orphan*/  usb_gadget_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_gadget_suspend(struct cdns3 *cdns, bool do_wakeup)
{
	struct cdns3_device *priv_dev = cdns->gadget_dev;

	cdns3_disconnect_gadget(priv_dev);

	priv_dev->gadget.speed = USB_SPEED_UNKNOWN;
	usb_gadget_set_state(&priv_dev->gadget, USB_STATE_NOTATTACHED);
	cdns3_hw_reset_eps_config(priv_dev);

	/* disable interrupt for device */
	writel(0, &priv_dev->regs->usb_ien);

	return 0;
}