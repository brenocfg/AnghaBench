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
 int /*<<< orphan*/  VCE_CMD_IB ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

void radeon_vce_ib_execute(struct radeon_device *rdev, struct radeon_ib *ib)
{
	struct radeon_ring *ring = &rdev->ring[ib->ring];
	radeon_ring_write(ring, cpu_to_le32(VCE_CMD_IB));
	radeon_ring_write(ring, cpu_to_le32(ib->gpu_addr));
	radeon_ring_write(ring, cpu_to_le32(upper_32_bits(ib->gpu_addr)));
	radeon_ring_write(ring, cpu_to_le32(ib->length_dw));
}