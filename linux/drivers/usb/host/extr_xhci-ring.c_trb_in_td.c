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
typedef  union xhci_trb {int dummy; } xhci_trb ;
struct xhci_segment {scalar_t__ dma; union xhci_trb* trbs; struct xhci_segment* next; } ;
struct xhci_hcd {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int TRBS_PER_SEGMENT ; 
 scalar_t__ xhci_trb_virt_to_dma (struct xhci_segment*,union xhci_trb*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long) ; 

struct xhci_segment *trb_in_td(struct xhci_hcd *xhci,
		struct xhci_segment *start_seg,
		union xhci_trb	*start_trb,
		union xhci_trb	*end_trb,
		dma_addr_t	suspect_dma,
		bool		debug)
{
	dma_addr_t start_dma;
	dma_addr_t end_seg_dma;
	dma_addr_t end_trb_dma;
	struct xhci_segment *cur_seg;

	start_dma = xhci_trb_virt_to_dma(start_seg, start_trb);
	cur_seg = start_seg;

	do {
		if (start_dma == 0)
			return NULL;
		/* We may get an event for a Link TRB in the middle of a TD */
		end_seg_dma = xhci_trb_virt_to_dma(cur_seg,
				&cur_seg->trbs[TRBS_PER_SEGMENT - 1]);
		/* If the end TRB isn't in this segment, this is set to 0 */
		end_trb_dma = xhci_trb_virt_to_dma(cur_seg, end_trb);

		if (debug)
			xhci_warn(xhci,
				"Looking for event-dma %016llx trb-start %016llx trb-end %016llx seg-start %016llx seg-end %016llx\n",
				(unsigned long long)suspect_dma,
				(unsigned long long)start_dma,
				(unsigned long long)end_trb_dma,
				(unsigned long long)cur_seg->dma,
				(unsigned long long)end_seg_dma);

		if (end_trb_dma > 0) {
			/* The end TRB is in this segment, so suspect should be here */
			if (start_dma <= end_trb_dma) {
				if (suspect_dma >= start_dma && suspect_dma <= end_trb_dma)
					return cur_seg;
			} else {
				/* Case for one segment with
				 * a TD wrapped around to the top
				 */
				if ((suspect_dma >= start_dma &&
							suspect_dma <= end_seg_dma) ||
						(suspect_dma >= cur_seg->dma &&
						 suspect_dma <= end_trb_dma))
					return cur_seg;
			}
			return NULL;
		} else {
			/* Might still be somewhere in this segment */
			if (suspect_dma >= start_dma && suspect_dma <= end_seg_dma)
				return cur_seg;
		}
		cur_seg = cur_seg->next;
		start_dma = xhci_trb_virt_to_dma(cur_seg, &cur_seg->trbs[0]);
	} while (cur_seg != start_seg);

	return NULL;
}