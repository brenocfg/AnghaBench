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
typedef  int /*<<< orphan*/  u64 ;
struct cik_mqd {int dummy; } ;
struct amdgpu_ring {int /*<<< orphan*/  mqd_obj; int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; int /*<<< orphan*/  me; } ;
struct TYPE_2__ {struct amdgpu_ring* compute_ring; } ;
struct amdgpu_device {int /*<<< orphan*/  srbm_mutex; int /*<<< orphan*/  dev; TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cik_srbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_mqd_commit (struct amdgpu_device*,struct cik_mqd*) ; 
 int /*<<< orphan*/  gfx_v7_0_mqd_deactivate (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_mqd_init (struct amdgpu_device*,struct cik_mqd*,int /*<<< orphan*/ ,struct amdgpu_ring*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfx_v7_0_compute_queue_init(struct amdgpu_device *adev, int ring_id)
{
	int r;
	u64 mqd_gpu_addr;
	struct cik_mqd *mqd;
	struct amdgpu_ring *ring = &adev->gfx.compute_ring[ring_id];

	r = amdgpu_bo_create_reserved(adev, sizeof(struct cik_mqd), PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_GTT, &ring->mqd_obj,
				      &mqd_gpu_addr, (void **)&mqd);
	if (r) {
		dev_warn(adev->dev, "(%d) create MQD bo failed\n", r);
		return r;
	}

	mutex_lock(&adev->srbm_mutex);
	cik_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);

	gfx_v7_0_mqd_init(adev, mqd, mqd_gpu_addr, ring);
	gfx_v7_0_mqd_deactivate(adev);
	gfx_v7_0_mqd_commit(adev, mqd);

	cik_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	amdgpu_bo_kunmap(ring->mqd_obj);
	amdgpu_bo_unreserve(ring->mqd_obj);
	return 0;
}