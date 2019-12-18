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
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {int /*<<< orphan*/  hcpriv; TYPE_1__ desc; } ;
struct usb_hcd {int dummy; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hcd_endpoint_disable (struct dwc2_hsotg*,struct usb_host_endpoint*,int) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 

__attribute__((used)) static void _dwc2_hcd_endpoint_disable(struct usb_hcd *hcd,
				       struct usb_host_endpoint *ep)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	dev_dbg(hsotg->dev,
		"DWC OTG HCD EP DISABLE: bEndpointAddress=0x%02x, ep->hcpriv=%p\n",
		ep->desc.bEndpointAddress, ep->hcpriv);
	dwc2_hcd_endpoint_disable(hsotg, ep, 250);
}