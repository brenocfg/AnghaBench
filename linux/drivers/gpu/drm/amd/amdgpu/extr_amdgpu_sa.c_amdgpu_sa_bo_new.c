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
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct amdgpu_sa_manager {unsigned int align; unsigned int size; TYPE_1__ wq; } ;
struct amdgpu_sa_bo {int /*<<< orphan*/  flist; int /*<<< orphan*/  olist; int /*<<< orphan*/ * fence; struct amdgpu_sa_manager* manager; } ;

/* Variables and functions */
 int AMDGPU_SA_NUM_FENCE_LISTS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ amdgpu_sa_bo_next_hole (struct amdgpu_sa_manager*,struct dma_fence**,unsigned int*) ; 
 scalar_t__ amdgpu_sa_bo_try_alloc (struct amdgpu_sa_manager*,struct amdgpu_sa_bo*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  amdgpu_sa_bo_try_free (struct amdgpu_sa_manager*) ; 
 int /*<<< orphan*/  amdgpu_sa_event (struct amdgpu_sa_manager*,unsigned int,unsigned int) ; 
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_any_timeout (struct dma_fence**,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_sa_bo*) ; 
 struct amdgpu_sa_bo* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_locked (TYPE_1__,int /*<<< orphan*/ ) ; 

int amdgpu_sa_bo_new(struct amdgpu_sa_manager *sa_manager,
		     struct amdgpu_sa_bo **sa_bo,
		     unsigned size, unsigned align)
{
	struct dma_fence *fences[AMDGPU_SA_NUM_FENCE_LISTS];
	unsigned tries[AMDGPU_SA_NUM_FENCE_LISTS];
	unsigned count;
	int i, r;
	signed long t;

	if (WARN_ON_ONCE(align > sa_manager->align))
		return -EINVAL;

	if (WARN_ON_ONCE(size > sa_manager->size))
		return -EINVAL;

	*sa_bo = kmalloc(sizeof(struct amdgpu_sa_bo), GFP_KERNEL);
	if (!(*sa_bo))
		return -ENOMEM;
	(*sa_bo)->manager = sa_manager;
	(*sa_bo)->fence = NULL;
	INIT_LIST_HEAD(&(*sa_bo)->olist);
	INIT_LIST_HEAD(&(*sa_bo)->flist);

	spin_lock(&sa_manager->wq.lock);
	do {
		for (i = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i)
			tries[i] = 0;

		do {
			amdgpu_sa_bo_try_free(sa_manager);

			if (amdgpu_sa_bo_try_alloc(sa_manager, *sa_bo,
						   size, align)) {
				spin_unlock(&sa_manager->wq.lock);
				return 0;
			}

			/* see if we can skip over some allocations */
		} while (amdgpu_sa_bo_next_hole(sa_manager, fences, tries));

		for (i = 0, count = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i)
			if (fences[i])
				fences[count++] = dma_fence_get(fences[i]);

		if (count) {
			spin_unlock(&sa_manager->wq.lock);
			t = dma_fence_wait_any_timeout(fences, count, false,
						       MAX_SCHEDULE_TIMEOUT,
						       NULL);
			for (i = 0; i < count; ++i)
				dma_fence_put(fences[i]);

			r = (t > 0) ? 0 : t;
			spin_lock(&sa_manager->wq.lock);
		} else {
			/* if we have nothing to wait for block */
			r = wait_event_interruptible_locked(
				sa_manager->wq,
				amdgpu_sa_event(sa_manager, size, align)
			);
		}

	} while (!r);

	spin_unlock(&sa_manager->wq.lock);
	kfree(*sa_bo);
	*sa_bo = NULL;
	return r;
}