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
struct fw_sysfs {struct fw_priv* fw_priv; } ;
struct fw_priv {int page_array_size; int nr_pages; struct page** pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PAGE_ALIGN (int) ; 
 int PAGE_SHIFT ; 
 int __GFP_HIGHMEM ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  fw_load_abort (struct fw_sysfs*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (struct page**,struct page**,int) ; 
 int /*<<< orphan*/  memset (struct page**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfree (struct page**) ; 
 struct page** vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fw_realloc_pages(struct fw_sysfs *fw_sysfs, int min_size)
{
	struct fw_priv *fw_priv= fw_sysfs->fw_priv;
	int pages_needed = PAGE_ALIGN(min_size) >> PAGE_SHIFT;

	/* If the array of pages is too small, grow it... */
	if (fw_priv->page_array_size < pages_needed) {
		int new_array_size = max(pages_needed,
					 fw_priv->page_array_size * 2);
		struct page **new_pages;

		new_pages = vmalloc(array_size(new_array_size, sizeof(void *)));
		if (!new_pages) {
			fw_load_abort(fw_sysfs);
			return -ENOMEM;
		}
		memcpy(new_pages, fw_priv->pages,
		       fw_priv->page_array_size * sizeof(void *));
		memset(&new_pages[fw_priv->page_array_size], 0, sizeof(void *) *
		       (new_array_size - fw_priv->page_array_size));
		vfree(fw_priv->pages);
		fw_priv->pages = new_pages;
		fw_priv->page_array_size = new_array_size;
	}

	while (fw_priv->nr_pages < pages_needed) {
		fw_priv->pages[fw_priv->nr_pages] =
			alloc_page(GFP_KERNEL | __GFP_HIGHMEM);

		if (!fw_priv->pages[fw_priv->nr_pages]) {
			fw_load_abort(fw_sysfs);
			return -ENOMEM;
		}
		fw_priv->nr_pages++;
	}
	return 0;
}