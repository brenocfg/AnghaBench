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
struct radeon_device {TYPE_2__* asic; } ;
struct TYPE_3__ {scalar_t__ blit; scalar_t__ dma; } ;
struct TYPE_4__ {TYPE_1__ copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_TEST_COPY_BLIT ; 
 int /*<<< orphan*/  RADEON_TEST_COPY_DMA ; 
 int /*<<< orphan*/  radeon_do_test_moves (struct radeon_device*,int /*<<< orphan*/ ) ; 

void radeon_test_moves(struct radeon_device *rdev)
{
	if (rdev->asic->copy.dma)
		radeon_do_test_moves(rdev, RADEON_TEST_COPY_DMA);
	if (rdev->asic->copy.blit)
		radeon_do_test_moves(rdev, RADEON_TEST_COPY_BLIT);
}