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
typedef  int /*<<< orphan*/  uint64_t ;
struct dma_resv {int dummy; } ;
struct dma_fence {int dummy; } ;
struct dma_fence_array {struct dma_fence base; } ;
struct amdgpu_pasid_cb {unsigned int pasid; int /*<<< orphan*/  cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  amdgpu_pasid_free (unsigned int) ; 
 int /*<<< orphan*/  amdgpu_pasid_free_cb (struct dma_fence*,int /*<<< orphan*/ *) ; 
 scalar_t__ dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct dma_fence*,int /*<<< orphan*/ *)) ; 
 struct dma_fence_array* dma_fence_array_create (unsigned int,struct dma_fence**,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_wait (struct dma_fence*,int) ; 
 int dma_resv_get_fences_rcu (struct dma_resv*,int /*<<< orphan*/ *,unsigned int*,struct dma_fence***) ; 
 int /*<<< orphan*/  dma_resv_wait_timeout_rcu (struct dma_resv*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 
 struct amdgpu_pasid_cb* kmalloc (int,int /*<<< orphan*/ ) ; 

void amdgpu_pasid_free_delayed(struct dma_resv *resv,
			       unsigned int pasid)
{
	struct dma_fence *fence, **fences;
	struct amdgpu_pasid_cb *cb;
	unsigned count;
	int r;

	r = dma_resv_get_fences_rcu(resv, NULL, &count, &fences);
	if (r)
		goto fallback;

	if (count == 0) {
		amdgpu_pasid_free(pasid);
		return;
	}

	if (count == 1) {
		fence = fences[0];
		kfree(fences);
	} else {
		uint64_t context = dma_fence_context_alloc(1);
		struct dma_fence_array *array;

		array = dma_fence_array_create(count, fences, context,
					       1, false);
		if (!array) {
			kfree(fences);
			goto fallback;
		}
		fence = &array->base;
	}

	cb = kmalloc(sizeof(*cb), GFP_KERNEL);
	if (!cb) {
		/* Last resort when we are OOM */
		dma_fence_wait(fence, false);
		dma_fence_put(fence);
		amdgpu_pasid_free(pasid);
	} else {
		cb->pasid = pasid;
		if (dma_fence_add_callback(fence, &cb->cb,
					   amdgpu_pasid_free_cb))
			amdgpu_pasid_free_cb(fence, &cb->cb);
	}

	return;

fallback:
	/* Not enough memory for the delayed delete, as last resort
	 * block for all the fences to complete.
	 */
	dma_resv_wait_timeout_rcu(resv, true, false,
					    MAX_SCHEDULE_TIMEOUT);
	amdgpu_pasid_free(pasid);
}