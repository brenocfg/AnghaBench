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
struct xhci_hcd {int dummy; } ;
struct xhci_ep_ctx {int /*<<< orphan*/  ep_info; } ;
struct urb {int interval; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ speed; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EP_INTERVAL_TO_UFRAMES (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_LOW ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ *,char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_interval(struct xhci_hcd *xhci, struct urb *urb,
						struct xhci_ep_ctx *ep_ctx)
{
	int xhci_interval;
	int ep_interval;

	xhci_interval = EP_INTERVAL_TO_UFRAMES(le32_to_cpu(ep_ctx->ep_info));
	ep_interval = urb->interval;

	/* Convert to microframes */
	if (urb->dev->speed == USB_SPEED_LOW ||
			urb->dev->speed == USB_SPEED_FULL)
		ep_interval *= 8;

	/* FIXME change this to a warning and a suggestion to use the new API
	 * to set the polling interval (once the API is added).
	 */
	if (xhci_interval != ep_interval) {
		dev_dbg_ratelimited(&urb->dev->dev,
				"Driver uses different interval (%d microframe%s) than xHCI (%d microframe%s)\n",
				ep_interval, ep_interval == 1 ? "" : "s",
				xhci_interval, xhci_interval == 1 ? "" : "s");
		urb->interval = xhci_interval;
		/* Convert back to frames for LS/FS devices */
		if (urb->dev->speed == USB_SPEED_LOW ||
				urb->dev->speed == USB_SPEED_FULL)
			urb->interval /= 8;
	}
}