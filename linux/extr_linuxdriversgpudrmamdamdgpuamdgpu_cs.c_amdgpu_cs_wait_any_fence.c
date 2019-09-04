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
struct TYPE_4__ {int status; unsigned int first_signaled; } ;
struct TYPE_3__ {unsigned int fence_count; int /*<<< orphan*/  timeout_ns; } ;
union drm_amdgpu_wait_fences {TYPE_2__ out; TYPE_1__ in; } ;
typedef  unsigned int uint32_t ;
struct drm_file {int dummy; } ;
struct drm_amdgpu_fence {int dummy; } ;
struct dma_fence {long error; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 long PTR_ERR (struct dma_fence*) ; 
 struct dma_fence* amdgpu_cs_get_fence (struct amdgpu_device*,struct drm_file*,struct drm_amdgpu_fence*) ; 
 unsigned long amdgpu_gem_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_any_timeout (struct dma_fence**,unsigned int,int,unsigned long,unsigned int*) ; 
 struct dma_fence** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 
 int /*<<< orphan*/  memset (union drm_amdgpu_wait_fences*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amdgpu_cs_wait_any_fence(struct amdgpu_device *adev,
				    struct drm_file *filp,
				    union drm_amdgpu_wait_fences *wait,
				    struct drm_amdgpu_fence *fences)
{
	unsigned long timeout = amdgpu_gem_timeout(wait->in.timeout_ns);
	uint32_t fence_count = wait->in.fence_count;
	uint32_t first = ~0;
	struct dma_fence **array;
	unsigned int i;
	long r;

	/* Prepare the fence array */
	array = kcalloc(fence_count, sizeof(struct dma_fence *), GFP_KERNEL);

	if (array == NULL)
		return -ENOMEM;

	for (i = 0; i < fence_count; i++) {
		struct dma_fence *fence;

		fence = amdgpu_cs_get_fence(adev, filp, &fences[i]);
		if (IS_ERR(fence)) {
			r = PTR_ERR(fence);
			goto err_free_fence_array;
		} else if (fence) {
			array[i] = fence;
		} else { /* NULL, the fence has been already signaled */
			r = 1;
			first = i;
			goto out;
		}
	}

	r = dma_fence_wait_any_timeout(array, fence_count, true, timeout,
				       &first);
	if (r < 0)
		goto err_free_fence_array;

out:
	memset(wait, 0, sizeof(*wait));
	wait->out.status = (r > 0);
	wait->out.first_signaled = first;

	if (first < fence_count && array[first])
		r = array[first]->error;
	else
		r = 0;

err_free_fence_array:
	for (i = 0; i < fence_count; i++)
		dma_fence_put(array[i]);
	kfree(array);

	return r;
}