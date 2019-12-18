#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_otg {int /*<<< orphan*/  host; } ;
struct TYPE_6__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_3__ self; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {struct usb_otg* otg; } ;
struct mv_otg {TYPE_2__* pdev; TYPE_1__ phy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static void mv_otg_start_host(struct mv_otg *mvotg, int on)
{
#ifdef CONFIG_USB
	struct usb_otg *otg = mvotg->phy.otg;
	struct usb_hcd *hcd;

	if (!otg->host)
		return;

	dev_info(&mvotg->pdev->dev, "%s host\n", on ? "start" : "stop");

	hcd = bus_to_hcd(otg->host);

	if (on) {
		usb_add_hcd(hcd, hcd->irq, IRQF_SHARED);
		device_wakeup_enable(hcd->self.controller);
	} else {
		usb_remove_hcd(hcd);
	}
#endif /* CONFIG_USB */
}