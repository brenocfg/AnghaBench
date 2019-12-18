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
typedef  unsigned int u32 ;
struct xhci_hcd {int hci_version; int quirks; } ;
struct urb {TYPE_1__* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int XHCI_MTK_HOST ; 
 unsigned int usb_endpoint_maxp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 xhci_td_remainder(struct xhci_hcd *xhci, int transferred,
			      int trb_buff_len, unsigned int td_total_len,
			      struct urb *urb, bool more_trbs_coming)
{
	u32 maxp, total_packet_count;

	/* MTK xHCI 0.96 contains some features from 1.0 */
	if (xhci->hci_version < 0x100 && !(xhci->quirks & XHCI_MTK_HOST))
		return ((td_total_len - transferred) >> 10);

	/* One TRB with a zero-length data packet. */
	if (!more_trbs_coming || (transferred == 0 && trb_buff_len == 0) ||
	    trb_buff_len == td_total_len)
		return 0;

	/* for MTK xHCI 0.96, TD size include this TRB, but not in 1.x */
	if ((xhci->quirks & XHCI_MTK_HOST) && (xhci->hci_version < 0x100))
		trb_buff_len = 0;

	maxp = usb_endpoint_maxp(&urb->ep->desc);
	total_packet_count = DIV_ROUND_UP(td_total_len, maxp);

	/* Queueing functions don't count the current TRB into transferred */
	return (total_packet_count - ((transferred + trb_buff_len) / maxp));
}