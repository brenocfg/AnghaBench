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
struct vmballoon {int /*<<< orphan*/  shrink_timeout; scalar_t__ reset_required; int /*<<< orphan*/  target; int /*<<< orphan*/  size; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMW_BALLOON_2M_PAGE ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vmballoon_page_in_frames (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t vmballoon_change(struct vmballoon *b)
{
	int64_t size, target;

	size = atomic64_read(&b->size);
	target = READ_ONCE(b->target);

	/*
	 * We must cast first because of int sizes
	 * Otherwise we might get huge positives instead of negatives
	 */

	if (b->reset_required)
		return 0;

	/* consider a 2MB slack on deflate, unless the balloon is emptied */
	if (target < size && target != 0 &&
	    size - target < vmballoon_page_in_frames(VMW_BALLOON_2M_PAGE))
		return 0;

	/* If an out-of-memory recently occurred, inflation is disallowed. */
	if (target > size && time_before(jiffies, READ_ONCE(b->shrink_timeout)))
		return 0;

	return target - size;
}