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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_tt {int dummy; } ;
struct amdgpu_ttm_tt {scalar_t__ last_set_pages; int /*<<< orphan*/  mmu_invalidations; int /*<<< orphan*/  guptasks; int /*<<< orphan*/  guptasklock; scalar_t__ usertask; int /*<<< orphan*/  userflags; int /*<<< orphan*/  userptr; } ;
struct TYPE_2__ {scalar_t__ group_leader; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_task_struct (scalar_t__) ; 
 int /*<<< orphan*/  put_task_struct (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int amdgpu_ttm_tt_set_userptr(struct ttm_tt *ttm, uint64_t addr,
			      uint32_t flags)
{
	struct amdgpu_ttm_tt *gtt = (void *)ttm;

	if (gtt == NULL)
		return -EINVAL;

	gtt->userptr = addr;
	gtt->userflags = flags;

	if (gtt->usertask)
		put_task_struct(gtt->usertask);
	gtt->usertask = current->group_leader;
	get_task_struct(gtt->usertask);

	spin_lock_init(&gtt->guptasklock);
	INIT_LIST_HEAD(&gtt->guptasks);
	atomic_set(&gtt->mmu_invalidations, 0);
	gtt->last_set_pages = 0;

	return 0;
}