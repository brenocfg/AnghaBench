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
struct radeon_ring {int dummy; } ;
struct radeon_ib {size_t ring; int /*<<< orphan*/  length_dw; int /*<<< orphan*/  gpu_addr; } ;
struct radeon_device {struct radeon_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD_RBC_IB_BASE ; 
 int /*<<< orphan*/  UVD_RBC_IB_SIZE ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 

void uvd_v1_0_ib_execute(struct radeon_device *rdev, struct radeon_ib *ib)
{
	struct radeon_ring *ring = &rdev->ring[ib->ring];

	radeon_ring_write(ring, PACKET0(UVD_RBC_IB_BASE, 0));
	radeon_ring_write(ring, ib->gpu_addr);
	radeon_ring_write(ring, PACKET0(UVD_RBC_IB_SIZE, 0));
	radeon_ring_write(ring, ib->length_dw);
}