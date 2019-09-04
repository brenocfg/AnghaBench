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
struct kvm_mmu {unsigned int last_nonleaf_level; } ;

/* Variables and functions */
 unsigned int PT_PAGE_SIZE_MASK ; 
 unsigned int PT_PAGE_TABLE_LEVEL ; 

__attribute__((used)) static inline bool is_last_gpte(struct kvm_mmu *mmu,
				unsigned level, unsigned gpte)
{
	/*
	 * The RHS has bit 7 set iff level < mmu->last_nonleaf_level.
	 * If it is clear, there are no large pages at this level, so clear
	 * PT_PAGE_SIZE_MASK in gpte if that is the case.
	 */
	gpte &= level - mmu->last_nonleaf_level;

	/*
	 * PT_PAGE_TABLE_LEVEL always terminates.  The RHS has bit 7 set
	 * iff level <= PT_PAGE_TABLE_LEVEL, which for our purpose means
	 * level == PT_PAGE_TABLE_LEVEL; set PT_PAGE_SIZE_MASK in gpte then.
	 */
	gpte |= level - PT_PAGE_TABLE_LEVEL - 1;

	return gpte & PT_PAGE_SIZE_MASK;
}