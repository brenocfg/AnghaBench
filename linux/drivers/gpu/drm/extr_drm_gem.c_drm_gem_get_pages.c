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
struct drm_gem_object {int size; TYPE_1__* filp; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct page** ERR_CAST (struct page*) ; 
 struct page** ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __GFP_DMA32 ; 
 int /*<<< orphan*/  drm_gem_check_release_pagevec (struct pagevec*) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 struct page** kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_clear_unevictable (struct address_space*) ; 
 scalar_t__ mapping_gfp_constraint (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_unevictable (struct address_space*) ; 
 int page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 scalar_t__ pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 struct page* shmem_read_mapping_page (struct address_space*,int) ; 

struct page **drm_gem_get_pages(struct drm_gem_object *obj)
{
	struct address_space *mapping;
	struct page *p, **pages;
	struct pagevec pvec;
	int i, npages;

	/* This is the shared memory object that backs the GEM resource */
	mapping = obj->filp->f_mapping;

	/* We already BUG_ON() for non-page-aligned sizes in
	 * drm_gem_object_init(), so we should never hit this unless
	 * driver author is doing something really wrong:
	 */
	WARN_ON((obj->size & (PAGE_SIZE - 1)) != 0);

	npages = obj->size >> PAGE_SHIFT;

	pages = kvmalloc_array(npages, sizeof(struct page *), GFP_KERNEL);
	if (pages == NULL)
		return ERR_PTR(-ENOMEM);

	mapping_set_unevictable(mapping);

	for (i = 0; i < npages; i++) {
		p = shmem_read_mapping_page(mapping, i);
		if (IS_ERR(p))
			goto fail;
		pages[i] = p;

		/* Make sure shmem keeps __GFP_DMA32 allocated pages in the
		 * correct region during swapin. Note that this requires
		 * __GFP_DMA32 to be set in mapping_gfp_mask(inode->i_mapping)
		 * so shmem can relocate pages during swapin if required.
		 */
		BUG_ON(mapping_gfp_constraint(mapping, __GFP_DMA32) &&
				(page_to_pfn(p) >= 0x00100000UL));
	}

	return pages;

fail:
	mapping_clear_unevictable(mapping);
	pagevec_init(&pvec);
	while (i--) {
		if (!pagevec_add(&pvec, pages[i]))
			drm_gem_check_release_pagevec(&pvec);
	}
	if (pagevec_count(&pvec))
		drm_gem_check_release_pagevec(&pvec);

	kvfree(pages);
	return ERR_CAST(p);
}