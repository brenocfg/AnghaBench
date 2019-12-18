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
struct radeon_device {int /*<<< orphan*/  fence_queue; } ;

/* Variables and functions */
 scalar_t__ radeon_fence_activity (struct radeon_device*,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void radeon_fence_process(struct radeon_device *rdev, int ring)
{
	if (radeon_fence_activity(rdev, ring))
		wake_up_all(&rdev->fence_queue);
}