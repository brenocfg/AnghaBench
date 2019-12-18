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
struct amdgpu_ring {int /*<<< orphan*/  pipe; int /*<<< orphan*/  me; } ;
struct TYPE_2__ {int num_gfx_rings; int num_compute_rings; int /*<<< orphan*/  pipe_reserve_mutex; int /*<<< orphan*/  pipe_reserve_bitmap; struct amdgpu_ring* compute_ring; struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_MAX_COMPUTE_QUEUES ; 
 int amdgpu_gfx_mec_queue_to_bit (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v9_0_ring_set_pipe_percent (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_v9_0_pipe_reserve_resources(struct amdgpu_device *adev,
					    struct amdgpu_ring *ring,
					    bool acquire)
{
	int i, pipe;
	bool reserve;
	struct amdgpu_ring *iring;

	mutex_lock(&adev->gfx.pipe_reserve_mutex);
	pipe = amdgpu_gfx_mec_queue_to_bit(adev, ring->me, ring->pipe, 0);
	if (acquire)
		set_bit(pipe, adev->gfx.pipe_reserve_bitmap);
	else
		clear_bit(pipe, adev->gfx.pipe_reserve_bitmap);

	if (!bitmap_weight(adev->gfx.pipe_reserve_bitmap, AMDGPU_MAX_COMPUTE_QUEUES)) {
		/* Clear all reservations - everyone reacquires all resources */
		for (i = 0; i < adev->gfx.num_gfx_rings; ++i)
			gfx_v9_0_ring_set_pipe_percent(&adev->gfx.gfx_ring[i],
						       true);

		for (i = 0; i < adev->gfx.num_compute_rings; ++i)
			gfx_v9_0_ring_set_pipe_percent(&adev->gfx.compute_ring[i],
						       true);
	} else {
		/* Lower all pipes without a current reservation */
		for (i = 0; i < adev->gfx.num_gfx_rings; ++i) {
			iring = &adev->gfx.gfx_ring[i];
			pipe = amdgpu_gfx_mec_queue_to_bit(adev,
							   iring->me,
							   iring->pipe,
							   0);
			reserve = test_bit(pipe, adev->gfx.pipe_reserve_bitmap);
			gfx_v9_0_ring_set_pipe_percent(iring, reserve);
		}

		for (i = 0; i < adev->gfx.num_compute_rings; ++i) {
			iring = &adev->gfx.compute_ring[i];
			pipe = amdgpu_gfx_mec_queue_to_bit(adev,
							   iring->me,
							   iring->pipe,
							   0);
			reserve = test_bit(pipe, adev->gfx.pipe_reserve_bitmap);
			gfx_v9_0_ring_set_pipe_percent(iring, reserve);
		}
	}

	mutex_unlock(&adev->gfx.pipe_reserve_mutex);
}