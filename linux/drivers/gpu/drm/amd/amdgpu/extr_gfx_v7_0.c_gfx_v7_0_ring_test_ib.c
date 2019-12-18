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
struct amdgpu_ib {int* ptr; int length_dw; } ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  ib ;

/* Variables and functions */
 long EINVAL ; 
 long ETIMEDOUT ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_UCONFIG_REG ; 
 int PACKET3_SET_UCONFIG_REG_START ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  amdgpu_gfx_scratch_free (struct amdgpu_device*,int) ; 
 long amdgpu_gfx_scratch_get (struct amdgpu_device*,int*) ; 
 int /*<<< orphan*/  amdgpu_ib_free (struct amdgpu_device*,struct amdgpu_ib*,int /*<<< orphan*/ *) ; 
 long amdgpu_ib_get (struct amdgpu_device*,int /*<<< orphan*/ *,int,struct amdgpu_ib*) ; 
 long amdgpu_ib_schedule (struct amdgpu_ring*,int,struct amdgpu_ib*,int /*<<< orphan*/ *,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,long) ; 
 int /*<<< orphan*/  memset (struct amdgpu_ib*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfx_v7_0_ring_test_ib(struct amdgpu_ring *ring, long timeout)
{
	struct amdgpu_device *adev = ring->adev;
	struct amdgpu_ib ib;
	struct dma_fence *f = NULL;
	uint32_t scratch;
	uint32_t tmp = 0;
	long r;

	r = amdgpu_gfx_scratch_get(adev, &scratch);
	if (r)
		return r;

	WREG32(scratch, 0xCAFEDEAD);
	memset(&ib, 0, sizeof(ib));
	r = amdgpu_ib_get(adev, NULL, 256, &ib);
	if (r)
		goto err1;

	ib.ptr[0] = PACKET3(PACKET3_SET_UCONFIG_REG, 1);
	ib.ptr[1] = ((scratch - PACKET3_SET_UCONFIG_REG_START));
	ib.ptr[2] = 0xDEADBEEF;
	ib.length_dw = 3;

	r = amdgpu_ib_schedule(ring, 1, &ib, NULL, &f);
	if (r)
		goto err2;

	r = dma_fence_wait_timeout(f, false, timeout);
	if (r == 0) {
		r = -ETIMEDOUT;
		goto err2;
	} else if (r < 0) {
		goto err2;
	}
	tmp = RREG32(scratch);
	if (tmp == 0xDEADBEEF)
		r = 0;
	else
		r = -EINVAL;

err2:
	amdgpu_ib_free(adev, &ib, NULL);
	dma_fence_put(f);
err1:
	amdgpu_gfx_scratch_free(adev, scratch);
	return r;
}