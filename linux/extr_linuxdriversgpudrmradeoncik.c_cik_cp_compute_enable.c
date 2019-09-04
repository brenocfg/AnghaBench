#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {TYPE_1__* ring; int /*<<< orphan*/  srbm_mutex; } ;
struct TYPE_2__ {int ready; } ;

/* Variables and functions */
 size_t CAYMAN_RING_TYPE_CP1_INDEX ; 
 size_t CAYMAN_RING_TYPE_CP2_INDEX ; 
 int /*<<< orphan*/  CP_MEC_CNTL ; 
 int MEC_ME1_HALT ; 
 int MEC_ME2_HALT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cik_compute_stop (struct radeon_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cik_cp_compute_enable(struct radeon_device *rdev, bool enable)
{
	if (enable)
		WREG32(CP_MEC_CNTL, 0);
	else {
		/*
		 * To make hibernation reliable we need to clear compute ring
		 * configuration before halting the compute ring.
		 */
		mutex_lock(&rdev->srbm_mutex);
		cik_compute_stop(rdev,&rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX]);
		cik_compute_stop(rdev,&rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX]);
		mutex_unlock(&rdev->srbm_mutex);

		WREG32(CP_MEC_CNTL, (MEC_ME1_HALT | MEC_ME2_HALT));
		rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX].ready = false;
		rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX].ready = false;
	}
	udelay(50);
}