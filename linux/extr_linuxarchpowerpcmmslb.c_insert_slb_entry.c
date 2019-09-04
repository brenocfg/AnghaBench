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
typedef  enum slb_index { ____Placeholder_slb_index } slb_index ;
struct TYPE_4__ {int stab_rr; int slb_cache_ptr; unsigned long* slb_cache; } ;
struct TYPE_3__ {unsigned long sllp; } ;

/* Variables and functions */
 int SLB_CACHE_ENTRIES ; 
 int SLB_NUM_BOLTED ; 
 unsigned long SLB_VSID_SSIZE_SHIFT ; 
 unsigned long SLB_VSID_USER ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 TYPE_2__* get_paca () ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 unsigned long mk_esid_data (unsigned long,int,int) ; 
 TYPE_1__* mmu_psize_defs ; 
 int mmu_slb_size ; 
 unsigned long slb_vsid_shift (int) ; 

__attribute__((used)) static void insert_slb_entry(unsigned long vsid, unsigned long ea,
			     int bpsize, int ssize)
{
	unsigned long flags, vsid_data, esid_data;
	enum slb_index index;
	int slb_cache_index;

	/*
	 * We are irq disabled, hence should be safe to access PACA.
	 */
	VM_WARN_ON(!irqs_disabled());

	/*
	 * We can't take a PMU exception in the following code, so hard
	 * disable interrupts.
	 */
	hard_irq_disable();

	index = get_paca()->stab_rr;

	/*
	 * simple round-robin replacement of slb starting at SLB_NUM_BOLTED.
	 */
	if (index < (mmu_slb_size - 1))
		index++;
	else
		index = SLB_NUM_BOLTED;

	get_paca()->stab_rr = index;

	flags = SLB_VSID_USER | mmu_psize_defs[bpsize].sllp;
	vsid_data = (vsid << slb_vsid_shift(ssize)) | flags |
		    ((unsigned long) ssize << SLB_VSID_SSIZE_SHIFT);
	esid_data = mk_esid_data(ea, ssize, index);

	/*
	 * No need for an isync before or after this slbmte. The exception
	 * we enter with and the rfid we exit with are context synchronizing.
	 * Also we only handle user segments here.
	 */
	asm volatile("slbmte %0, %1" : : "r" (vsid_data), "r" (esid_data)
		     : "memory");

	/*
	 * Now update slb cache entries
	 */
	slb_cache_index = get_paca()->slb_cache_ptr;
	if (slb_cache_index < SLB_CACHE_ENTRIES) {
		/*
		 * We have space in slb cache for optimized switch_slb().
		 * Top 36 bits from esid_data as per ISA
		 */
		get_paca()->slb_cache[slb_cache_index++] = esid_data >> 28;
		get_paca()->slb_cache_ptr++;
	} else {
		/*
		 * Our cache is full and the current cache content strictly
		 * doesn't indicate the active SLB conents. Bump the ptr
		 * so that switch_slb() will ignore the cache.
		 */
		get_paca()->slb_cache_ptr = SLB_CACHE_ENTRIES + 1;
	}
}