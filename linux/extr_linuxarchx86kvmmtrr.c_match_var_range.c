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
typedef  scalar_t__ u64 ;
struct mtrr_iter {scalar_t__ end; scalar_t__ start; int partial_map; scalar_t__ start_max; struct kvm_mtrr_range* range; } ;
struct kvm_mtrr_range {int dummy; } ;

/* Variables and functions */
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  var_mtrr_range (struct kvm_mtrr_range*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static bool match_var_range(struct mtrr_iter *iter,
			    struct kvm_mtrr_range *range)
{
	u64 start, end;

	var_mtrr_range(range, &start, &end);
	if (!(start >= iter->end || end <= iter->start)) {
		iter->range = range;

		/*
		 * the function is called when we do kvm_mtrr.head walking.
		 * Range has the minimum base address which interleaves
		 * [looker->start_max, looker->end).
		 */
		iter->partial_map |= iter->start_max < start;

		/* update the max address has been covered. */
		iter->start_max = max(iter->start_max, end);
		return true;
	}

	return false;
}