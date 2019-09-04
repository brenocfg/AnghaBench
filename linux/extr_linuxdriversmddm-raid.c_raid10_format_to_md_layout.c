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
struct raid_set {int /*<<< orphan*/  ctr_flags; } ;

/* Variables and functions */
 unsigned int ALGORITHM_RAID10_DEFAULT ; 
 unsigned int ALGORITHM_RAID10_FAR ; 
 unsigned int ALGORITHM_RAID10_NEAR ; 
 unsigned int ALGORITHM_RAID10_OFFSET ; 
 int EINVAL ; 
 unsigned int RAID10_FAR_COPIES_SHIFT ; 
 unsigned int RAID10_OFFSET ; 
 unsigned int RAID10_USE_FAR_SETS ; 
 int /*<<< orphan*/  __CTR_FLAG_RAID10_USE_NEAR_SETS ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid10_format_to_md_layout(struct raid_set *rs,
				      unsigned int algorithm,
				      unsigned int copies)
{
	unsigned int n = 1, f = 1, r = 0;

	/*
	 * MD resilienece flaw:
	 *
	 * enabling use_far_sets for far/offset formats causes copies
	 * to be colocated on the same devs together with their origins!
	 *
	 * -> disable it for now in the definition above
	 */
	if (algorithm == ALGORITHM_RAID10_DEFAULT ||
	    algorithm == ALGORITHM_RAID10_NEAR)
		n = copies;

	else if (algorithm == ALGORITHM_RAID10_OFFSET) {
		f = copies;
		r = RAID10_OFFSET;
		if (!test_bit(__CTR_FLAG_RAID10_USE_NEAR_SETS, &rs->ctr_flags))
			r |= RAID10_USE_FAR_SETS;

	} else if (algorithm == ALGORITHM_RAID10_FAR) {
		f = copies;
		r = !RAID10_OFFSET;
		if (!test_bit(__CTR_FLAG_RAID10_USE_NEAR_SETS, &rs->ctr_flags))
			r |= RAID10_USE_FAR_SETS;

	} else
		return -EINVAL;

	return r | (f << RAID10_FAR_COPIES_SHIFT) | n;
}