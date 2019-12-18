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
struct page {int dummy; } ;
struct nouveau_drm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int nouveau_dmem_pages_alloc (struct nouveau_drm*,int,unsigned long*) ; 
 struct page* pfn_to_page (unsigned long) ; 

__attribute__((used)) static struct page *
nouveau_dmem_page_alloc_locked(struct nouveau_drm *drm)
{
	unsigned long pfns[1];
	struct page *page;
	int ret;

	/* FIXME stop all the miss-match API ... */
	ret = nouveau_dmem_pages_alloc(drm, 1, pfns);
	if (ret)
		return NULL;

	page = pfn_to_page(pfns[0]);
	get_page(page);
	lock_page(page);
	return page;
}