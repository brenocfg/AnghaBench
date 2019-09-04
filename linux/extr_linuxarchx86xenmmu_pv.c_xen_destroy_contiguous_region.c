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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 unsigned int MAX_CONTIG_ORDER ; 
 unsigned int PAGE_SIZE ; 
 unsigned long* discontig_frames ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long virt_to_mfn (unsigned long) ; 
 int xen_exchange_memory (int,unsigned int,unsigned long*,unsigned long,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_remap_exchanged_ptes (unsigned long,unsigned int,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  xen_reservation_lock ; 
 int /*<<< orphan*/  xen_zap_pfn_range (unsigned long,unsigned int,int /*<<< orphan*/ *,unsigned long*) ; 

void xen_destroy_contiguous_region(phys_addr_t pstart, unsigned int order)
{
	unsigned long *out_frames = discontig_frames, in_frame;
	unsigned long  flags;
	int success;
	unsigned long vstart;

	if (unlikely(order > MAX_CONTIG_ORDER))
		return;

	vstart = (unsigned long)phys_to_virt(pstart);
	memset((void *) vstart, 0, PAGE_SIZE << order);

	spin_lock_irqsave(&xen_reservation_lock, flags);

	/* 1. Find start MFN of contiguous extent. */
	in_frame = virt_to_mfn(vstart);

	/* 2. Zap current PTEs. */
	xen_zap_pfn_range(vstart, order, NULL, out_frames);

	/* 3. Do the exchange for non-contiguous MFNs. */
	success = xen_exchange_memory(1, order, &in_frame, 1UL << order,
					0, out_frames, 0);

	/* 4. Map new pages in place of old pages. */
	if (success)
		xen_remap_exchanged_ptes(vstart, order, out_frames, 0);
	else
		xen_remap_exchanged_ptes(vstart, order, NULL, in_frame);

	spin_unlock_irqrestore(&xen_reservation_lock, flags);
}