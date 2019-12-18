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
struct TYPE_2__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_1__ generic; } ;
struct xhci_td {union xhci_trb* last_trb; union xhci_trb* first_trb; struct xhci_segment* start_seg; } ;
struct xhci_segment {int dummy; } ;
struct xhci_ring {int dummy; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRB_CYCLE ; 
 int /*<<< orphan*/  TRB_TR_NOOP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_trb (struct xhci_hcd*,struct xhci_ring*,struct xhci_segment**,union xhci_trb**) ; 
 int /*<<< orphan*/  trb_to_noop (union xhci_trb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void td_to_noop(struct xhci_hcd *xhci, struct xhci_ring *ep_ring,
		       struct xhci_td *td, bool flip_cycle)
{
	struct xhci_segment *seg	= td->start_seg;
	union xhci_trb *trb		= td->first_trb;

	while (1) {
		trb_to_noop(trb, TRB_TR_NOOP);

		/* flip cycle if asked to */
		if (flip_cycle && trb != td->first_trb && trb != td->last_trb)
			trb->generic.field[3] ^= cpu_to_le32(TRB_CYCLE);

		if (trb == td->last_trb)
			break;

		next_trb(xhci, ep_ring, &seg, &trb);
	}
}