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
typedef  scalar_t__ uint64_t ;
struct radeon_fence {scalar_t__ seq; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int RADEON_NUM_RINGS ; 
 long radeon_fence_wait_seq_timeout (struct radeon_device*,scalar_t__*,int,int /*<<< orphan*/ ) ; 

int radeon_fence_wait_any(struct radeon_device *rdev,
			  struct radeon_fence **fences,
			  bool intr)
{
	uint64_t seq[RADEON_NUM_RINGS];
	unsigned i, num_rings = 0;
	long r;

	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		seq[i] = 0;

		if (!fences[i]) {
			continue;
		}

		seq[i] = fences[i]->seq;
		++num_rings;
	}

	/* nothing to wait for ? */
	if (num_rings == 0)
		return -ENOENT;

	r = radeon_fence_wait_seq_timeout(rdev, seq, intr, MAX_SCHEDULE_TIMEOUT);
	if (r < 0) {
		return r;
	}
	return 0;
}