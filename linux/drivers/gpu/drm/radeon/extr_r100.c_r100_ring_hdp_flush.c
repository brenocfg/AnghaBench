#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_ring {int dummy; } ;
struct TYPE_3__ {int hdp_cntl; } ;
struct TYPE_4__ {TYPE_1__ r100; } ;
struct radeon_device {TYPE_2__ config; } ;

/* Variables and functions */
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RADEON_HDP_READ_BUFFER_INVALIDATE ; 
 int /*<<< orphan*/  RADEON_HOST_PATH_CNTL ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

__attribute__((used)) static void r100_ring_hdp_flush(struct radeon_device *rdev, struct radeon_ring *ring)
{
	radeon_ring_write(ring, PACKET0(RADEON_HOST_PATH_CNTL, 0));
	radeon_ring_write(ring, rdev->config.r100.hdp_cntl |
				RADEON_HDP_READ_BUFFER_INVALIDATE);
	radeon_ring_write(ring, PACKET0(RADEON_HOST_PATH_CNTL, 0));
	radeon_ring_write(ring, rdev->config.r100.hdp_cntl);
}