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
struct radeon_semaphore {int dummy; } ;
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */

bool uvd_v1_0_semaphore_emit(struct radeon_device *rdev,
			     struct radeon_ring *ring,
			     struct radeon_semaphore *semaphore,
			     bool emit_wait)
{
	/* disable semaphores for UVD V1 hardware */
	return false;
}