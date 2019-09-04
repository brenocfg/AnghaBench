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
typedef  int /*<<< orphan*/  u64 ;
struct mm_struct {int dummy; } ;
struct amdgpu_amdkfd_fence {int /*<<< orphan*/  lock; int /*<<< orphan*/  base; int /*<<< orphan*/  timeline_name; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdkfd_fence_ops ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fence_seq ; 
 int /*<<< orphan*/  get_task_comm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdgpu_amdkfd_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmgrab (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct amdgpu_amdkfd_fence *amdgpu_amdkfd_fence_create(u64 context,
						       struct mm_struct *mm)
{
	struct amdgpu_amdkfd_fence *fence;

	fence = kzalloc(sizeof(*fence), GFP_KERNEL);
	if (fence == NULL)
		return NULL;

	/* This reference gets released in amdkfd_fence_release */
	mmgrab(mm);
	fence->mm = mm;
	get_task_comm(fence->timeline_name, current);
	spin_lock_init(&fence->lock);

	dma_fence_init(&fence->base, &amdkfd_fence_ops, &fence->lock,
		   context, atomic_inc_return(&fence_seq));

	return fence;
}