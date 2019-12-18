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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct radeon_sa_manager {unsigned int align; unsigned int size; TYPE_1__ wq; } ;
struct radeon_sa_bo {int /*<<< orphan*/  flist; int /*<<< orphan*/  olist; int /*<<< orphan*/ * fence; struct radeon_sa_manager* manager; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  kfree (struct radeon_sa_bo*) ; 
 struct radeon_sa_bo* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_fence_ref (struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_fence_unref (struct radeon_fence**) ; 
 int radeon_fence_wait_any (struct radeon_device*,struct radeon_fence**,int) ; 
 scalar_t__ radeon_sa_bo_next_hole (struct radeon_sa_manager*,struct radeon_fence**,unsigned int*) ; 
 scalar_t__ radeon_sa_bo_try_alloc (struct radeon_sa_manager*,struct radeon_sa_bo*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  radeon_sa_bo_try_free (struct radeon_sa_manager*) ; 
 int /*<<< orphan*/  radeon_sa_event (struct radeon_sa_manager*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_locked (TYPE_1__,int /*<<< orphan*/ ) ; 

int radeon_sa_bo_new(struct radeon_device *rdev,
		     struct radeon_sa_manager *sa_manager,
		     struct radeon_sa_bo **sa_bo,
		     unsigned size, unsigned align)
{
	struct radeon_fence *fences[RADEON_NUM_RINGS];
	unsigned tries[RADEON_NUM_RINGS];
	int i, r;

	BUG_ON(align > sa_manager->align);
	BUG_ON(size > sa_manager->size);

	*sa_bo = kmalloc(sizeof(struct radeon_sa_bo), GFP_KERNEL);
	if ((*sa_bo) == NULL) {
		return -ENOMEM;
	}
	(*sa_bo)->manager = sa_manager;
	(*sa_bo)->fence = NULL;
	INIT_LIST_HEAD(&(*sa_bo)->olist);
	INIT_LIST_HEAD(&(*sa_bo)->flist);

	spin_lock(&sa_manager->wq.lock);
	do {
		for (i = 0; i < RADEON_NUM_RINGS; ++i) {
			fences[i] = NULL;
			tries[i] = 0;
		}

		do {
			radeon_sa_bo_try_free(sa_manager);

			if (radeon_sa_bo_try_alloc(sa_manager, *sa_bo,
						   size, align)) {
				spin_unlock(&sa_manager->wq.lock);
				return 0;
			}

			/* see if we can skip over some allocations */
		} while (radeon_sa_bo_next_hole(sa_manager, fences, tries));

		for (i = 0; i < RADEON_NUM_RINGS; ++i)
			radeon_fence_ref(fences[i]);

		spin_unlock(&sa_manager->wq.lock);
		r = radeon_fence_wait_any(rdev, fences, false);
		for (i = 0; i < RADEON_NUM_RINGS; ++i)
			radeon_fence_unref(&fences[i]);
		spin_lock(&sa_manager->wq.lock);
		/* if we have nothing to wait for block */
		if (r == -ENOENT) {
			r = wait_event_interruptible_locked(
				sa_manager->wq, 
				radeon_sa_event(sa_manager, size, align)
			);
		}

	} while (!r);

	spin_unlock(&sa_manager->wq.lock);
	kfree(*sa_bo);
	*sa_bo = NULL;
	return r;
}