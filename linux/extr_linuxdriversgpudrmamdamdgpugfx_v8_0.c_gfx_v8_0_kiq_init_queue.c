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
struct vi_mqd_allocation {int dynamic_cu_mask; int dynamic_rb_mask; } ;
struct vi_mqd {int dummy; } ;
struct amdgpu_ring {int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; int /*<<< orphan*/  me; scalar_t__ wptr; struct vi_mqd* mqd_ptr; struct amdgpu_device* adev; } ;
struct TYPE_3__ {struct vi_mqd** mqd_backup; } ;
struct TYPE_4__ {TYPE_1__ mec; } ;
struct amdgpu_device {TYPE_2__ gfx; int /*<<< orphan*/  srbm_mutex; scalar_t__ in_gpu_reset; } ;

/* Variables and functions */
 int AMDGPU_MAX_COMPUTE_RINGS ; 
 int /*<<< orphan*/  amdgpu_ring_clear_ring (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  gfx_v8_0_kiq_setting (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  gfx_v8_0_mqd_commit (struct amdgpu_device*,struct vi_mqd*) ; 
 int /*<<< orphan*/  gfx_v8_0_mqd_init (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  memcpy (struct vi_mqd*,struct vi_mqd*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vi_srbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfx_v8_0_kiq_init_queue(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	struct vi_mqd *mqd = ring->mqd_ptr;
	int mqd_idx = AMDGPU_MAX_COMPUTE_RINGS;

	gfx_v8_0_kiq_setting(ring);

	if (adev->in_gpu_reset) { /* for GPU_RESET case */
		/* reset MQD to a clean status */
		if (adev->gfx.mec.mqd_backup[mqd_idx])
			memcpy(mqd, adev->gfx.mec.mqd_backup[mqd_idx], sizeof(struct vi_mqd_allocation));

		/* reset ring buffer */
		ring->wptr = 0;
		amdgpu_ring_clear_ring(ring);
		mutex_lock(&adev->srbm_mutex);
		vi_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);
		gfx_v8_0_mqd_commit(adev, mqd);
		vi_srbm_select(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);
	} else {
		memset((void *)mqd, 0, sizeof(struct vi_mqd_allocation));
		((struct vi_mqd_allocation *)mqd)->dynamic_cu_mask = 0xFFFFFFFF;
		((struct vi_mqd_allocation *)mqd)->dynamic_rb_mask = 0xFFFFFFFF;
		mutex_lock(&adev->srbm_mutex);
		vi_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);
		gfx_v8_0_mqd_init(ring);
		gfx_v8_0_mqd_commit(adev, mqd);
		vi_srbm_select(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);

		if (adev->gfx.mec.mqd_backup[mqd_idx])
			memcpy(adev->gfx.mec.mqd_backup[mqd_idx], mqd, sizeof(struct vi_mqd_allocation));
	}

	return 0;
}