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
struct usb_otg {int /*<<< orphan*/  gadget; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct usb_otg* otg; } ;
struct mv_otg {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  usb_gadget_vbus_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_gadget_vbus_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_otg_start_periphrals(struct mv_otg *mvotg, int on)
{
	struct usb_otg *otg = mvotg->phy.otg;

	if (!otg->gadget)
		return;

	dev_info(mvotg->phy.dev, "gadget %s\n", on ? "on" : "off");

	if (on)
		usb_gadget_vbus_connect(otg->gadget);
	else
		usb_gadget_vbus_disconnect(otg->gadget);
}