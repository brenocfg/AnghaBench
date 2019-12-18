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
struct xhci_hcd {int hci_version; } ;
struct urb {TYPE_3__* ep; TYPE_1__* dev; } ;
struct TYPE_5__ {unsigned int bMaxBurst; } ;
struct TYPE_6__ {TYPE_2__ ss_ep_comp; } ;
struct TYPE_4__ {scalar_t__ speed; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 scalar_t__ USB_SPEED_SUPER ; 

__attribute__((used)) static unsigned int xhci_get_burst_count(struct xhci_hcd *xhci,
		struct urb *urb, unsigned int total_packet_count)
{
	unsigned int max_burst;

	if (xhci->hci_version < 0x100 || urb->dev->speed < USB_SPEED_SUPER)
		return 0;

	max_burst = urb->ep->ss_ep_comp.bMaxBurst;
	return DIV_ROUND_UP(total_packet_count, max_burst + 1) - 1;
}