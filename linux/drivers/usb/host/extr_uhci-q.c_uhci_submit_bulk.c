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
struct urb {TYPE_1__* dev; } ;
struct uhci_qh {scalar_t__ state; int /*<<< orphan*/  skel; } ;
struct uhci_hcd {int dummy; } ;
struct TYPE_2__ {scalar_t__ speed; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ QH_STATE_ACTIVE ; 
 int /*<<< orphan*/  SKEL_BULK ; 
 scalar_t__ USB_SPEED_LOW ; 
 int /*<<< orphan*/  uhci_add_fsbr (struct uhci_hcd*,struct urb*) ; 
 int uhci_submit_common (struct uhci_hcd*,struct urb*,struct uhci_qh*) ; 

__attribute__((used)) static int uhci_submit_bulk(struct uhci_hcd *uhci, struct urb *urb,
		struct uhci_qh *qh)
{
	int ret;

	/* Can't have low-speed bulk transfers */
	if (urb->dev->speed == USB_SPEED_LOW)
		return -EINVAL;

	if (qh->state != QH_STATE_ACTIVE)
		qh->skel = SKEL_BULK;
	ret = uhci_submit_common(uhci, urb, qh);
	if (ret == 0)
		uhci_add_fsbr(uhci, urb);
	return ret;
}