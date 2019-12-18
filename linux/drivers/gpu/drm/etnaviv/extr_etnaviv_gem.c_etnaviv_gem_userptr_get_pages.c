#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct page {int dummy; } ;
struct etnaviv_gem_userptr {int /*<<< orphan*/  ro; scalar_t__ ptr; TYPE_2__* mm; } ;
struct TYPE_4__ {int size; } ;
struct etnaviv_gem_object {struct page** pages; TYPE_1__ base; struct etnaviv_gem_userptr userptr; } ;
struct TYPE_6__ {TYPE_2__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 TYPE_3__* current ; 
 int get_user_pages_fast (scalar_t__,unsigned int,int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 struct page** kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_lock_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_pages (struct page**,int) ; 

__attribute__((used)) static int etnaviv_gem_userptr_get_pages(struct etnaviv_gem_object *etnaviv_obj)
{
	struct page **pvec = NULL;
	struct etnaviv_gem_userptr *userptr = &etnaviv_obj->userptr;
	int ret, pinned = 0, npages = etnaviv_obj->base.size >> PAGE_SHIFT;

	might_lock_read(&current->mm->mmap_sem);

	if (userptr->mm != current->mm)
		return -EPERM;

	pvec = kvmalloc_array(npages, sizeof(struct page *), GFP_KERNEL);
	if (!pvec)
		return -ENOMEM;

	do {
		unsigned num_pages = npages - pinned;
		uint64_t ptr = userptr->ptr + pinned * PAGE_SIZE;
		struct page **pages = pvec + pinned;

		ret = get_user_pages_fast(ptr, num_pages,
					  !userptr->ro ? FOLL_WRITE : 0, pages);
		if (ret < 0) {
			release_pages(pvec, pinned);
			kvfree(pvec);
			return ret;
		}

		pinned += ret;

	} while (pinned < npages);

	etnaviv_obj->pages = pvec;

	return 0;
}