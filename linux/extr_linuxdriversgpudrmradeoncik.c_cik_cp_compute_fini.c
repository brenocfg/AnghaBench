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
struct radeon_device {TYPE_1__* ring; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mqd_obj; } ;

/* Variables and functions */
 int CAYMAN_RING_TYPE_CP1_INDEX ; 
 int CAYMAN_RING_TYPE_CP2_INDEX ; 
 int /*<<< orphan*/  cik_cp_compute_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cik_cp_compute_fini(struct radeon_device *rdev)
{
	int i, idx, r;

	cik_cp_compute_enable(rdev, false);

	for (i = 0; i < 2; i++) {
		if (i == 0)
			idx = CAYMAN_RING_TYPE_CP1_INDEX;
		else
			idx = CAYMAN_RING_TYPE_CP2_INDEX;

		if (rdev->ring[idx].mqd_obj) {
			r = radeon_bo_reserve(rdev->ring[idx].mqd_obj, false);
			if (unlikely(r != 0))
				dev_warn(rdev->dev, "(%d) reserve MQD bo failed\n", r);

			radeon_bo_unpin(rdev->ring[idx].mqd_obj);
			radeon_bo_unreserve(rdev->ring[idx].mqd_obj);

			radeon_bo_unref(&rdev->ring[idx].mqd_obj);
			rdev->ring[idx].mqd_obj = NULL;
		}
	}
}