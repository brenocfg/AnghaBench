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
struct sg_table {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_ALIGN (size_t) ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 struct page** kvmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sg_alloc_table_from_pages (struct sg_table*,struct page**,unsigned int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (size_t) ; 
 struct page* vmalloc_to_page (void*) ; 

__attribute__((used)) static void *ffs_build_sg_list(struct sg_table *sgt, size_t sz)
{
	struct page **pages;
	void *vaddr, *ptr;
	unsigned int n_pages;
	int i;

	vaddr = vmalloc(sz);
	if (!vaddr)
		return NULL;

	n_pages = PAGE_ALIGN(sz) >> PAGE_SHIFT;
	pages = kvmalloc_array(n_pages, sizeof(struct page *), GFP_KERNEL);
	if (!pages) {
		vfree(vaddr);

		return NULL;
	}
	for (i = 0, ptr = vaddr; i < n_pages; ++i, ptr += PAGE_SIZE)
		pages[i] = vmalloc_to_page(ptr);

	if (sg_alloc_table_from_pages(sgt, pages, n_pages, 0, sz, GFP_KERNEL)) {
		kvfree(pages);
		vfree(vaddr);

		return NULL;
	}
	kvfree(pages);

	return vaddr;
}