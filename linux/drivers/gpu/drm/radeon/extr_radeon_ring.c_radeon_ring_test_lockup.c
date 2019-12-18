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
typedef  scalar_t__ uint32_t ;
struct radeon_ring {int /*<<< orphan*/  idx; int /*<<< orphan*/  last_rptr; int /*<<< orphan*/  last_activity; } ;
struct radeon_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ jiffies_64 ; 
 scalar_t__ jiffies_to_msecs (scalar_t__) ; 
 scalar_t__ radeon_lockup_timeout ; 
 scalar_t__ radeon_ring_get_rptr (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_lockup_update (struct radeon_device*,struct radeon_ring*) ; 

bool radeon_ring_test_lockup(struct radeon_device *rdev, struct radeon_ring *ring)
{
	uint32_t rptr = radeon_ring_get_rptr(rdev, ring);
	uint64_t last = atomic64_read(&ring->last_activity);
	uint64_t elapsed;

	if (rptr != atomic_read(&ring->last_rptr)) {
		/* ring is still working, no lockup */
		radeon_ring_lockup_update(rdev, ring);
		return false;
	}

	elapsed = jiffies_to_msecs(jiffies_64 - last);
	if (radeon_lockup_timeout && elapsed >= radeon_lockup_timeout) {
		dev_err(rdev->dev, "ring %d stalled for more than %llumsec\n",
			ring->idx, elapsed);
		return true;
	}
	/* give a chance to the GPU ... */
	return false;
}