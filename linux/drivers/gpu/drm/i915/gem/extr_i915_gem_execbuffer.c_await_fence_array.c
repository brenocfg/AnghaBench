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
struct i915_execbuffer {int /*<<< orphan*/  request; TYPE_1__* args; } ;
struct drm_syncobj {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {unsigned int num_cliprects; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int I915_EXEC_FENCE_WAIT ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct dma_fence* drm_syncobj_fence_get (struct drm_syncobj*) ; 
 int i915_request_await_dma_fence (int /*<<< orphan*/ ,struct dma_fence*) ; 
 struct drm_syncobj* ptr_unpack_bits (struct drm_syncobj*,unsigned int*,int) ; 

__attribute__((used)) static int
await_fence_array(struct i915_execbuffer *eb,
		  struct drm_syncobj **fences)
{
	const unsigned int nfences = eb->args->num_cliprects;
	unsigned int n;
	int err;

	for (n = 0; n < nfences; n++) {
		struct drm_syncobj *syncobj;
		struct dma_fence *fence;
		unsigned int flags;

		syncobj = ptr_unpack_bits(fences[n], &flags, 2);
		if (!(flags & I915_EXEC_FENCE_WAIT))
			continue;

		fence = drm_syncobj_fence_get(syncobj);
		if (!fence)
			return -EINVAL;

		err = i915_request_await_dma_fence(eb->request, fence);
		dma_fence_put(fence);
		if (err < 0)
			return err;
	}

	return 0;
}