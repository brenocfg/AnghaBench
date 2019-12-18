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
struct xhci_hcd {int /*<<< orphan*/  hcc_params; } ;

/* Variables and functions */
 unsigned int HCC_MAX_PSA (int /*<<< orphan*/ ) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,unsigned int) ; 

__attribute__((used)) static void xhci_calculate_streams_entries(struct xhci_hcd *xhci,
		unsigned int *num_streams, unsigned int *num_stream_ctxs)
{
	unsigned int max_streams;

	/* The stream context array size must be a power of two */
	*num_stream_ctxs = roundup_pow_of_two(*num_streams);
	/*
	 * Find out how many primary stream array entries the host controller
	 * supports.  Later we may use secondary stream arrays (similar to 2nd
	 * level page entries), but that's an optional feature for xHCI host
	 * controllers. xHCs must support at least 4 stream IDs.
	 */
	max_streams = HCC_MAX_PSA(xhci->hcc_params);
	if (*num_stream_ctxs > max_streams) {
		xhci_dbg(xhci, "xHCI HW only supports %u stream ctx entries.\n",
				max_streams);
		*num_stream_ctxs = max_streams;
		*num_streams = max_streams;
	}
}