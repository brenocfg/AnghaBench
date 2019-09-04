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
struct radeon_ring {int /*<<< orphan*/  last_activity; int /*<<< orphan*/  last_rptr; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies_64 ; 
 int /*<<< orphan*/  radeon_ring_get_rptr (struct radeon_device*,struct radeon_ring*) ; 

void radeon_ring_lockup_update(struct radeon_device *rdev,
			       struct radeon_ring *ring)
{
	atomic_set(&ring->last_rptr, radeon_ring_get_rptr(rdev, ring));
	atomic64_set(&ring->last_activity, jiffies_64);
}