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
struct drm_gem_object {int size; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void drm_gem_put_pages(struct drm_gem_object *obj, struct page **pages,
		bool dirty, bool accessed)
{
	int i, npages;

	/* We already BUG_ON() for non-page-aligned sizes in
	 * drm_gem_object_init(), so we should never hit this unless
	 * driver author is doing something really wrong:
	 */
	WARN_ON((obj->size & (PAGE_SIZE - 1)) != 0);

	npages = obj->size >> PAGE_SHIFT;

	for (i = 0; i < npages; i++) {
		if (dirty)
			set_page_dirty(pages[i]);

		if (accessed)
			mark_page_accessed(pages[i]);

		/* Undo the reference we took when populating the table */
		put_page(pages[i]);
	}

	kvfree(pages);
}