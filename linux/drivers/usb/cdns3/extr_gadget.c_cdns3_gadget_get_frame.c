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
struct usb_gadget {int dummy; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  usb_itpn; } ;

/* Variables and functions */
 struct cdns3_device* gadget_to_cdns3_device (struct usb_gadget*) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_gadget_get_frame(struct usb_gadget *gadget)
{
	struct cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);

	return readl(&priv_dev->regs->usb_itpn);
}