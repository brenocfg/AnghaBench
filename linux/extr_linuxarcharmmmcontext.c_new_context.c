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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASID_FIRST_VERSION ; 
 int ASID_MASK ; 
 int NUM_USER_ASIDS ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asid_generation ; 
 int /*<<< orphan*/  asid_map ; 
 int atomic64_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ check_update_reserved_asid (int,int) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  flush_context (unsigned int) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 

__attribute__((used)) static u64 new_context(struct mm_struct *mm, unsigned int cpu)
{
	static u32 cur_idx = 1;
	u64 asid = atomic64_read(&mm->context.id);
	u64 generation = atomic64_read(&asid_generation);

	if (asid != 0) {
		u64 newasid = generation | (asid & ~ASID_MASK);

		/*
		 * If our current ASID was active during a rollover, we
		 * can continue to use it and this was just a false alarm.
		 */
		if (check_update_reserved_asid(asid, newasid))
			return newasid;

		/*
		 * We had a valid ASID in a previous life, so try to re-use
		 * it if possible.,
		 */
		asid &= ~ASID_MASK;
		if (!__test_and_set_bit(asid, asid_map))
			return newasid;
	}

	/*
	 * Allocate a free ASID. If we can't find one, take a note of the
	 * currently active ASIDs and mark the TLBs as requiring flushes.
	 * We always count from ASID #1, as we reserve ASID #0 to switch
	 * via TTBR0 and to avoid speculative page table walks from hitting
	 * in any partial walk caches, which could be populated from
	 * overlapping level-1 descriptors used to map both the module
	 * area and the userspace stack.
	 */
	asid = find_next_zero_bit(asid_map, NUM_USER_ASIDS, cur_idx);
	if (asid == NUM_USER_ASIDS) {
		generation = atomic64_add_return(ASID_FIRST_VERSION,
						 &asid_generation);
		flush_context(cpu);
		asid = find_next_zero_bit(asid_map, NUM_USER_ASIDS, 1);
	}

	__set_bit(asid, asid_map);
	cur_idx = asid;
	cpumask_clear(mm_cpumask(mm));
	return asid | generation;
}