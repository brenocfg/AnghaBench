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
struct TYPE_4__ {int status; } ;
struct TYPE_3__ {unsigned int fence_count; int /*<<< orphan*/  timeout_ns; } ;
union drm_amdgpu_wait_fences {TYPE_2__ out; TYPE_1__ in; } ;
typedef  unsigned int uint32_t ;
struct drm_file {int dummy; } ;
struct drm_amdgpu_fence {int dummy; } ;
struct dma_fence {int error; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 int PTR_ERR (struct dma_fence*) ; 
 struct dma_fence* amdgpu_cs_get_fence (struct amdgpu_device*,struct drm_file*,struct drm_amdgpu_fence*) ; 
 unsigned long amdgpu_gem_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,unsigned long) ; 
 int /*<<< orphan*/  memset (union drm_amdgpu_wait_fences*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amdgpu_cs_wait_all_fences(struct amdgpu_device *adev,
				     struct drm_file *filp,
				     union drm_amdgpu_wait_fences *wait,
				     struct drm_amdgpu_fence *fences)
{
	uint32_t fence_count = wait->in.fence_count;
	unsigned int i;
	long r = 1;

	for (i = 0; i < fence_count; i++) {
		struct dma_fence *fence;
		unsigned long timeout = amdgpu_gem_timeout(wait->in.timeout_ns);

		fence = amdgpu_cs_get_fence(adev, filp, &fences[i]);
		if (IS_ERR(fence))
			return PTR_ERR(fence);
		else if (!fence)
			continue;

		r = dma_fence_wait_timeout(fence, true, timeout);
		dma_fence_put(fence);
		if (r < 0)
			return r;

		if (r == 0)
			break;

		if (fence->error)
			return fence->error;
	}

	memset(wait, 0, sizeof(*wait));
	wait->out.status = (r > 0);

	return 0;
}