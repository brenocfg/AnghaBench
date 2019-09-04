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
struct radeon_device {TYPE_1__* ring; int /*<<< orphan*/  dev; int /*<<< orphan*/  has_uvd; } ;
struct TYPE_2__ {scalar_t__ ring_size; } ;

/* Variables and functions */
 size_t R600_RING_TYPE_UVD_INDEX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_fence_driver_start_ring (struct radeon_device*,size_t) ; 
 int radeon_uvd_resume (struct radeon_device*) ; 
 int uvd_v4_2_resume (struct radeon_device*) ; 

__attribute__((used)) static void cik_uvd_start(struct radeon_device *rdev)
{
	int r;

	if (!rdev->has_uvd)
		return;

	r = radeon_uvd_resume(rdev);
	if (r) {
		dev_err(rdev->dev, "failed UVD resume (%d).\n", r);
		goto error;
	}
	r = uvd_v4_2_resume(rdev);
	if (r) {
		dev_err(rdev->dev, "failed UVD 4.2 resume (%d).\n", r);
		goto error;
	}
	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_UVD_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing UVD fences (%d).\n", r);
		goto error;
	}
	return;

error:
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_size = 0;
}