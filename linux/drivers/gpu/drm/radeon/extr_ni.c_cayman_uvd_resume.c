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
struct radeon_device {int /*<<< orphan*/  dev; struct radeon_ring* ring; int /*<<< orphan*/  has_uvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t R600_RING_TYPE_UVD_INDEX ; 
 int /*<<< orphan*/  UVD_NO_OP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_ring_init (struct radeon_device*,struct radeon_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uvd_v1_0_init (struct radeon_device*) ; 

__attribute__((used)) static void cayman_uvd_resume(struct radeon_device *rdev)
{
	struct radeon_ring *ring;
	int r;

	if (!rdev->has_uvd || !rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_size)
		return;

	ring = &rdev->ring[R600_RING_TYPE_UVD_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, PACKET0(UVD_NO_OP, 0));
	if (r) {
		dev_err(rdev->dev, "failed initializing UVD ring (%d).\n", r);
		return;
	}
	r = uvd_v1_0_init(rdev);
	if (r) {
		dev_err(rdev->dev, "failed initializing UVD (%d).\n", r);
		return;
	}
}