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
struct pagevec {int dummy; } ;
struct page {int dummy; } ;
struct drm_gem_object {int size; int /*<<< orphan*/  filp; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_gem_check_release_pagevec (struct pagevec*) ; 
 TYPE_1__* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 int /*<<< orphan*/  mapping_clear_unevictable (struct address_space*) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 scalar_t__ pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void drm_gem_put_pages(struct drm_gem_object *obj, struct page **pages,
		bool dirty, bool accessed)
{
	int i, npages;
	struct address_space *mapping;
	struct pagevec pvec;

	mapping = file_inode(obj->filp)->i_mapping;
	mapping_clear_unevictable(mapping);

	/* We already BUG_ON() for non-page-aligned sizes in
	 * drm_gem_object_init(), so we should never hit this unless
	 * driver author is doing something really wrong:
	 */
	WARN_ON((obj->size & (PAGE_SIZE - 1)) != 0);

	npages = obj->size >> PAGE_SHIFT;

	pagevec_init(&pvec);
	for (i = 0; i < npages; i++) {
		if (!pages[i])
			continue;

		if (dirty)
			set_page_dirty(pages[i]);

		if (accessed)
			mark_page_accessed(pages[i]);

		/* Undo the reference we took when populating the table */
		if (!pagevec_add(&pvec, pages[i]))
			drm_gem_check_release_pagevec(&pvec);
	}
	if (pagevec_count(&pvec))
		drm_gem_check_release_pagevec(&pvec);

	kvfree(pages);
}