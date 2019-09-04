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
typedef  int u32 ;

/* Variables and functions */
 int PFERR_FETCH_MASK ; 
 int PFERR_PRESENT_MASK ; 
 int PFERR_RSVD_MASK ; 
 int PFERR_WRITE_MASK ; 
 scalar_t__ shadow_acc_track_mask ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool page_fault_can_be_fast(u32 error_code)
{
	/*
	 * Do not fix the mmio spte with invalid generation number which
	 * need to be updated by slow page fault path.
	 */
	if (unlikely(error_code & PFERR_RSVD_MASK))
		return false;

	/* See if the page fault is due to an NX violation */
	if (unlikely(((error_code & (PFERR_FETCH_MASK | PFERR_PRESENT_MASK))
		      == (PFERR_FETCH_MASK | PFERR_PRESENT_MASK))))
		return false;

	/*
	 * #PF can be fast if:
	 * 1. The shadow page table entry is not present, which could mean that
	 *    the fault is potentially caused by access tracking (if enabled).
	 * 2. The shadow page table entry is present and the fault
	 *    is caused by write-protect, that means we just need change the W
	 *    bit of the spte which can be done out of mmu-lock.
	 *
	 * However, if access tracking is disabled we know that a non-present
	 * page must be a genuine page fault where we have to create a new SPTE.
	 * So, if access tracking is disabled, we return true only for write
	 * accesses to a present page.
	 */

	return shadow_acc_track_mask != 0 ||
	       ((error_code & (PFERR_WRITE_MASK | PFERR_PRESENT_MASK))
		== (PFERR_WRITE_MASK | PFERR_PRESENT_MASK));
}