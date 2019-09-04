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
typedef  unsigned int uint64_t ;
struct vm_area_struct {unsigned long vm_end; scalar_t__ vm_file; } ;
struct ttm_tt {unsigned int num_pages; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct amdgpu_ttm_tt {int userflags; unsigned int userptr; int /*<<< orphan*/  guptasklock; TYPE_1__* usertask; int /*<<< orphan*/  guptasks; } ;
struct amdgpu_ttm_gup_task_list {int /*<<< orphan*/  list; TYPE_2__* task; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;
struct TYPE_3__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int AMDGPU_GEM_USERPTR_ANONONLY ; 
 int AMDGPU_GEM_USERPTR_READONLY ; 
 int EPERM ; 
 int ESRCH ; 
 unsigned int FOLL_WRITE ; 
 unsigned int PAGE_SIZE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned int) ; 
 int get_user_pages (unsigned int,unsigned int,unsigned int,struct page**,int /*<<< orphan*/ *) ; 
 int get_user_pages_remote (TYPE_1__*,struct mm_struct*,unsigned int,unsigned int,unsigned int,struct page**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_pages (struct page**,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int amdgpu_ttm_tt_get_user_pages(struct ttm_tt *ttm, struct page **pages)
{
	struct amdgpu_ttm_tt *gtt = (void *)ttm;
	struct mm_struct *mm = gtt->usertask->mm;
	unsigned int flags = 0;
	unsigned pinned = 0;
	int r;

	if (!mm) /* Happens during process shutdown */
		return -ESRCH;

	if (!(gtt->userflags & AMDGPU_GEM_USERPTR_READONLY))
		flags |= FOLL_WRITE;

	down_read(&mm->mmap_sem);

	if (gtt->userflags & AMDGPU_GEM_USERPTR_ANONONLY) {
		/*
		 * check that we only use anonymous memory to prevent problems
		 * with writeback
		 */
		unsigned long end = gtt->userptr + ttm->num_pages * PAGE_SIZE;
		struct vm_area_struct *vma;

		vma = find_vma(mm, gtt->userptr);
		if (!vma || vma->vm_file || vma->vm_end < end) {
			up_read(&mm->mmap_sem);
			return -EPERM;
		}
	}

	/* loop enough times using contiguous pages of memory */
	do {
		unsigned num_pages = ttm->num_pages - pinned;
		uint64_t userptr = gtt->userptr + pinned * PAGE_SIZE;
		struct page **p = pages + pinned;
		struct amdgpu_ttm_gup_task_list guptask;

		guptask.task = current;
		spin_lock(&gtt->guptasklock);
		list_add(&guptask.list, &gtt->guptasks);
		spin_unlock(&gtt->guptasklock);

		if (mm == current->mm)
			r = get_user_pages(userptr, num_pages, flags, p, NULL);
		else
			r = get_user_pages_remote(gtt->usertask,
					mm, userptr, num_pages,
					flags, p, NULL, NULL);

		spin_lock(&gtt->guptasklock);
		list_del(&guptask.list);
		spin_unlock(&gtt->guptasklock);

		if (r < 0)
			goto release_pages;

		pinned += r;

	} while (pinned < ttm->num_pages);

	up_read(&mm->mmap_sem);
	return 0;

release_pages:
	release_pages(pages, pinned);
	up_read(&mm->mmap_sem);
	return r;
}