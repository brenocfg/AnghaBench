#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long long first; unsigned long long step; unsigned long long next; } ;
struct TYPE_4__ {TYPE_1__ dtlb; } ;

/* Variables and functions */
 unsigned long long DTLB_FIXED ; 
 int EINVAL ; 
 int /*<<< orphan*/  __flush_tlb_slot (unsigned long long) ; 
 TYPE_2__* cpu_data ; 

int sh64_put_wired_dtlb_entry(unsigned long long entry)
{
	__flush_tlb_slot(entry);

	/*
	 * We don't do any particularly useful tracking of wired entries,
	 * so this approach works like a stack .. last one to be allocated
	 * has to be the first one to be freed.
	 *
	 * We could potentially load wired entries into a list and work on
	 * rebalancing the list periodically (which also entails moving the
	 * contents of a TLB entry) .. though I have a feeling that this is
	 * more trouble than it's worth.
	 */

	/*
	 * Entry must be valid .. we don't want any ITLB addresses!
	 */
	if (entry <= DTLB_FIXED)
		return -EINVAL;

	/*
	 * Next, check if we're within range to be freed. (ie, must be the
	 * entry beneath the first 'free' entry!
	 */
	if (entry < (cpu_data->dtlb.first - cpu_data->dtlb.step))
		return -EINVAL;

	/* If we are, then bring this entry back into the list */
	cpu_data->dtlb.first	-= cpu_data->dtlb.step;
	cpu_data->dtlb.next	= entry;

	return 0;
}