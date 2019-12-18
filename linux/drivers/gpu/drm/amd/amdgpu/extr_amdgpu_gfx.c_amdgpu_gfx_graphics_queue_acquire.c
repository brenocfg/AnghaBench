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
struct TYPE_3__ {int num_queue_per_pipe; int num_pipe_per_me; int num_me; int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_4__ {TYPE_1__ me; int /*<<< orphan*/  num_gfx_rings; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int AMDGPU_MAX_GFX_QUEUES ; 
 int /*<<< orphan*/  bitmap_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

void amdgpu_gfx_graphics_queue_acquire(struct amdgpu_device *adev)
{
	int i, queue, pipe, me;

	for (i = 0; i < AMDGPU_MAX_GFX_QUEUES; ++i) {
		queue = i % adev->gfx.me.num_queue_per_pipe;
		pipe = (i / adev->gfx.me.num_queue_per_pipe)
			% adev->gfx.me.num_pipe_per_me;
		me = (i / adev->gfx.me.num_queue_per_pipe)
		      / adev->gfx.me.num_pipe_per_me;

		if (me >= adev->gfx.me.num_me)
			break;
		/* policy: amdgpu owns the first queue per pipe at this stage
		 * will extend to mulitple queues per pipe later */
		if (me == 0 && queue < 1)
			set_bit(i, adev->gfx.me.queue_bitmap);
	}

	/* update the number of active graphics rings */
	adev->gfx.num_gfx_rings =
		bitmap_weight(adev->gfx.me.queue_bitmap, AMDGPU_MAX_GFX_QUEUES);
}