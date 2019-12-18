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
struct radeon_ring {int /*<<< orphan*/  ring_size; } ;
struct radeon_device {int /*<<< orphan*/  dev; struct radeon_ring* ring; int /*<<< orphan*/  has_vce; } ;

/* Variables and functions */
 size_t TN_RING_TYPE_VCE1_INDEX ; 
 size_t TN_RING_TYPE_VCE2_INDEX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_ring_init (struct radeon_device*,struct radeon_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vce_v1_0_init (struct radeon_device*) ; 

__attribute__((used)) static void cayman_vce_resume(struct radeon_device *rdev)
{
	struct radeon_ring *ring;
	int r;

	if (!rdev->has_vce || !rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_size)
		return;

	ring = &rdev->ring[TN_RING_TYPE_VCE1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, 0x0);
	if (r) {
		dev_err(rdev->dev, "failed initializing VCE1 ring (%d).\n", r);
		return;
	}
	ring = &rdev->ring[TN_RING_TYPE_VCE2_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, 0x0);
	if (r) {
		dev_err(rdev->dev, "failed initializing VCE1 ring (%d).\n", r);
		return;
	}
	r = vce_v1_0_init(rdev);
	if (r) {
		dev_err(rdev->dev, "failed initializing VCE (%d).\n", r);
		return;
	}
}