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
typedef  int u32 ;
struct usb_hcd {int /*<<< orphan*/  regs; } ;
struct oxu_hcd {scalar_t__ is_otg; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  OXU_CHIPIRQEN_CLR ; 
 int /*<<< orphan*/  OXU_CHIPIRQEN_SET ; 
 int /*<<< orphan*/  OXU_CHIPIRQSTATUS ; 
 int OXU_USBOTGI ; 
 int OXU_USBSPHI ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int /*<<< orphan*/  oxu210_hcd_irq (struct usb_hcd*) ; 
 int oxu_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxu_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t oxu_irq(struct usb_hcd *hcd)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	int ret = IRQ_HANDLED;

	u32 status = oxu_readl(hcd->regs, OXU_CHIPIRQSTATUS);
	u32 enable = oxu_readl(hcd->regs, OXU_CHIPIRQEN_SET);

	/* Disable all interrupt */
	oxu_writel(hcd->regs, OXU_CHIPIRQEN_CLR, enable);

	if ((oxu->is_otg && (status & OXU_USBOTGI)) ||
		(!oxu->is_otg && (status & OXU_USBSPHI)))
		oxu210_hcd_irq(hcd);
	else
		ret = IRQ_NONE;

	/* Enable all interrupt back */
	oxu_writel(hcd->regs, OXU_CHIPIRQEN_SET, enable);

	return ret;
}