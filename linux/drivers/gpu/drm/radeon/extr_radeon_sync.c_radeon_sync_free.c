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
struct radeon_sync {int /*<<< orphan*/ * semaphores; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 unsigned int RADEON_NUM_SYNCS ; 
 int /*<<< orphan*/  radeon_semaphore_free (struct radeon_device*,int /*<<< orphan*/ *,struct radeon_fence*) ; 

void radeon_sync_free(struct radeon_device *rdev,
		      struct radeon_sync *sync,
		      struct radeon_fence *fence)
{
	unsigned i;

	for (i = 0; i < RADEON_NUM_SYNCS; ++i)
		radeon_semaphore_free(rdev, &sync->semaphores[i], fence);
}