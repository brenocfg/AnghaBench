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
typedef  int uint32_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_bo**,int /*<<< orphan*/ *,void**) ; 
 int amdgpu_uvd_send_msg (struct amdgpu_ring*,struct amdgpu_bo*,int,struct dma_fence**) ; 
 int cpu_to_le32 (int) ; 

int amdgpu_uvd_get_destroy_msg(struct amdgpu_ring *ring, uint32_t handle,
			       bool direct, struct dma_fence **fence)
{
	struct amdgpu_device *adev = ring->adev;
	struct amdgpu_bo *bo = NULL;
	uint32_t *msg;
	int r, i;

	r = amdgpu_bo_create_reserved(adev, 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &bo, NULL, (void **)&msg);
	if (r)
		return r;

	/* stitch together an UVD destroy msg */
	msg[0] = cpu_to_le32(0x00000de4);
	msg[1] = cpu_to_le32(0x00000002);
	msg[2] = cpu_to_le32(handle);
	msg[3] = cpu_to_le32(0x00000000);
	for (i = 4; i < 1024; ++i)
		msg[i] = cpu_to_le32(0x0);

	return amdgpu_uvd_send_msg(ring, bo, direct, fence);
}