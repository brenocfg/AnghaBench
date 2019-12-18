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
struct amdgpu_ring {int me; int pipe; int queue; } ;
struct TYPE_3__ {int num_mec; int num_pipe_per_mec; int num_queue_per_pipe; int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_4__ {TYPE_1__ mec; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_2__ gfx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_gfx_bit_to_mec_queue (struct amdgpu_device*,int,int*,int*,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_gfx_kiq_acquire(struct amdgpu_device *adev,
				  struct amdgpu_ring *ring)
{
	int queue_bit;
	int mec, pipe, queue;

	queue_bit = adev->gfx.mec.num_mec
		    * adev->gfx.mec.num_pipe_per_mec
		    * adev->gfx.mec.num_queue_per_pipe;

	while (queue_bit-- >= 0) {
		if (test_bit(queue_bit, adev->gfx.mec.queue_bitmap))
			continue;

		amdgpu_gfx_bit_to_mec_queue(adev, queue_bit, &mec, &pipe, &queue);

		/*
		 * 1. Using pipes 2/3 from MEC 2 seems cause problems.
		 * 2. It must use queue id 0, because CGPG_IDLE/SAVE/LOAD/RUN
		 * only can be issued on queue 0.
		 */
		if ((mec == 1 && pipe > 1) || queue != 0)
			continue;

		ring->me = mec + 1;
		ring->pipe = pipe;
		ring->queue = queue;

		return 0;
	}

	dev_err(adev->dev, "Failed to find a queue for KIQ\n");
	return -EINVAL;
}