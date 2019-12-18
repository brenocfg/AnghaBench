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
struct usb_hcd {int dummy; } ;
struct dwc2_hsotg {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_handle_hcd_intr (struct dwc2_hsotg*) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 

__attribute__((used)) static irqreturn_t _dwc2_hcd_irq(struct usb_hcd *hcd)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	return dwc2_handle_hcd_intr(hsotg);
}