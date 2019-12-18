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
typedef  int uint64_t ;
struct radeon_device {TYPE_1__* fence_drv; } ;
struct TYPE_2__ {int* sync_seq; int /*<<< orphan*/  last_seq; } ;

/* Variables and functions */
 int atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_fence_process (struct radeon_device*,int) ; 

unsigned radeon_fence_count_emitted(struct radeon_device *rdev, int ring)
{
	uint64_t emitted;

	/* We are not protected by ring lock when reading the last sequence
	 * but it's ok to report slightly wrong fence count here.
	 */
	radeon_fence_process(rdev, ring);
	emitted = rdev->fence_drv[ring].sync_seq[ring]
		- atomic64_read(&rdev->fence_drv[ring].last_seq);
	/* to avoid 32bits warp around */
	if (emitted > 0x10000000) {
		emitted = 0x10000000;
	}
	return (unsigned)emitted;
}