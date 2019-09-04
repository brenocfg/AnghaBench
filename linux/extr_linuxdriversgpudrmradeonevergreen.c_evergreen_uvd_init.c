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
struct radeon_device {TYPE_1__* ring; scalar_t__ has_uvd; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ring_obj; } ;

/* Variables and functions */
 size_t R600_RING_TYPE_UVD_INDEX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r600_ring_init (struct radeon_device*,TYPE_1__*,int) ; 
 int radeon_uvd_init (struct radeon_device*) ; 

__attribute__((used)) static void evergreen_uvd_init(struct radeon_device *rdev)
{
	int r;

	if (!rdev->has_uvd)
		return;

	r = radeon_uvd_init(rdev);
	if (r) {
		dev_err(rdev->dev, "failed UVD (%d) init.\n", r);
		/*
		 * At this point rdev->uvd.vcpu_bo is NULL which trickles down
		 * to early fails uvd_v2_2_resume() and thus nothing happens
		 * there. So it is pointless to try to go through that code
		 * hence why we disable uvd here.
		 */
		rdev->has_uvd = 0;
		return;
	}
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_obj = NULL;
	r600_ring_init(rdev, &rdev->ring[R600_RING_TYPE_UVD_INDEX], 4096);
}