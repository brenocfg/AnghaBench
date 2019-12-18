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
struct radeon_device {TYPE_1__* ring; int /*<<< orphan*/  dev; int /*<<< orphan*/  has_vce; } ;
struct TYPE_2__ {scalar_t__ ring_size; } ;

/* Variables and functions */
 size_t TN_RING_TYPE_VCE1_INDEX ; 
 size_t TN_RING_TYPE_VCE2_INDEX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_fence_driver_start_ring (struct radeon_device*,size_t) ; 
 int radeon_vce_resume (struct radeon_device*) ; 
 int vce_v1_0_resume (struct radeon_device*) ; 

__attribute__((used)) static void si_vce_start(struct radeon_device *rdev)
{
	int r;

	if (!rdev->has_vce)
		return;

	r = radeon_vce_resume(rdev);
	if (r) {
		dev_err(rdev->dev, "failed VCE resume (%d).\n", r);
		goto error;
	}
	r = vce_v1_0_resume(rdev);
	if (r) {
		dev_err(rdev->dev, "failed VCE resume (%d).\n", r);
		goto error;
	}
	r = radeon_fence_driver_start_ring(rdev, TN_RING_TYPE_VCE1_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing VCE1 fences (%d).\n", r);
		goto error;
	}
	r = radeon_fence_driver_start_ring(rdev, TN_RING_TYPE_VCE2_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing VCE2 fences (%d).\n", r);
		goto error;
	}
	return;

error:
	rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_size = 0;
	rdev->ring[TN_RING_TYPE_VCE2_INDEX].ring_size = 0;
}